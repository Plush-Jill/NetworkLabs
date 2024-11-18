#include <boost/asio.hpp>
#include "../include/sender.hpp"
#include "../include/receiver.hpp"
#include "../include/multicast_app.hpp"
#include <boost/thread.hpp>

MulticastApp::MulticastApp(const std::string &listen_address,
                           const std::string &multicast_address) :
                           io_context_(std::make_shared<boost::asio::io_context>()),
                           timer_(*(this->io_context_)){

    this->sender_ = std::make_unique<Sender>(this->io_context_,
                                             boost::asio::ip::address::from_string(
                                                     multicast_address));
    this->storage_ = std::make_shared<KnownInstancesStorage>();
    this->receiver_ = std::make_unique<Receiver>(this->io_context_,
                                                 boost::asio::ip::address::from_string(listen_address),
                                                 boost::asio::ip::address::from_string(multicast_address),
                                                 storage_);
}

void MulticastApp::observe_storage() {
    this->observing_storage_thread_ = std::thread([this](){
        while (this->running_) {
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::lock_guard<std::mutex> lock_guard(this->observing_storage_mutex_);

                auto& map = this->storage_->getStorage();
                for (auto it = map.begin(); it != map.end();) {
                    it->second -= boost::chrono::seconds {1};
                    if (it->second <= boost::chrono::seconds::zero()) {
                        this->storage_->set_changed("erased " + it->first.to_string());
                        it = map.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            if (storage_->is_changed()) {
                this->storage_->print_storage();
            }
        }
    });
    this->periodic_printing_storage_thread_ = std::thread([this](){
        boost::asio::io_context local_io_context;
        boost::asio::steady_timer timer(local_io_context);
        while (running_) {
            timer.expires_after(std::chrono::seconds(2));
            timer.async_wait([this](const boost::system::error_code& error_code) {
                if (!error_code && running_) {
                    this->storage_->print_storage();
                }
            });

            local_io_context.run();
            local_io_context.reset();
        }
    });

}

void MulticastApp::start() {
    this->running_ = true;
    this->sender_->send();
    this->receiver_->receive();
    this->observe_storage();
    this->running_io_context_thread_ = std::thread([this](){
        io_context_->run();
    });
}

void MulticastApp::close() {
    io_context_->stop();
    this->running_ = false;
}

