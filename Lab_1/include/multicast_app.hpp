#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <set>
#include <string>
#include <chrono>
#include <thread>
#include <unordered_map>
#include "known_instances_storage.hpp"
#include "sender.hpp"
#include "receiver.hpp"

class MulticastApp {
public:
    MulticastApp(const std::string& listen_address,
                 const std::string& multicast_address);
    /**
     * @brief starting app
     */
    void start();
    void close();

private:
    std::shared_ptr<boost::asio::io_context> io_context_;
    boost::asio::steady_timer timer_;
    std::mutex observing_storage_mutex_;

    std::unique_ptr<Sender> sender_;
    std::unique_ptr<Receiver> receiver_;
    std::shared_ptr<KnownInstancesStorage> storage_;
    void observe_storage();
    bool running_;
    std::thread observing_storage_thread_;
    std::thread periodic_printing_storage_thread_;
    std::thread running_io_context_thread_;

};
