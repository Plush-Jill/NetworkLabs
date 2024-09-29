//
// Created by plushjill on 29.09.2024.
//

#include "MulticastApp.h"


MulticastApp::MulticastApp(boost::asio::io_context& io_context, const std::string& multicast_address, short multicast_port)
                            : io_context_(io_context),
                            socket_(io_context),
                            timer_(io_context, std::chrono::seconds(1)),
                            multicast_endpoint_(boost::asio::ip::make_address(multicast_address), multicast_port),
                            multicast_address_(multicast_address)
                            {

    // Открываем сокет с автоматическим выбором IPv4 или IPv6
    if (multicast_endpoint_.address().is_v4()) {
        socket_.open(boost::asio::ip::udp::v4());
    } else {
        socket_.open(boost::asio::ip::udp::v6());
    }

    // Присоединение к multicast-группе
    if (multicast_endpoint_.address().is_v4()) {
        socket_.set_option(boost::asio::ip::multicast::join_group(multicast_endpoint_.address().to_v4()));
    } else {
        socket_.set_option(boost::asio::ip::multicast::join_group(multicast_endpoint_.address().to_v6()));
    }

    // Привязываем сокет к локальному адресу
    socket_.bind(boost::asio::ip::udp::endpoint(multicast_endpoint_.protocol(), multicast_port));

    // Запускаем цикл отправки и получения сообщений
    start_receive();
    start_send();
    timer_.async_wait(boost::bind(&MulticastApp::check_alive, this));
}
void MulticastApp::start_receive() {
    socket_.async_receive_from(
            boost::asio::buffer(receive_buffer_),
            sender_endpoint_,
            boost::bind(&MulticastApp::handle_receive,
                            this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
}
void MulticastApp::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::string received_message(receive_buffer_.data(), bytes_transferred);
        std::string sender_ip = sender_endpoint_.address().to_string();
        std::cout << std::format("new received message: \"{}\" from {}\n", received_message, sender_ip);
        auto now = std::chrono::steady_clock::now();

        // Обновляем информацию о "живых" копиях
        alive_peers_[sender_ip] = now;

        // Выводим обновленный список "живых" копий
        display_alive_peers();

        start_receive(); // Ожидаем следующее сообщение
    }
}
void MulticastApp::start_send() {
//    std::string message = "Hello from " + boost::asio::ip::host_name() + std::to_string(sent_messages_count++);
    std::string message = std::format("Hello from {} ({})", boost::asio::ip::host_name(), std::to_string(sent_messages_count++));

    socket_.async_send_to(
            boost::asio::buffer(message),
            multicast_endpoint_,
            boost::bind(&MulticastApp::handle_send,
                            this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    std::cout << std::format("Sent message \"{}\" to {}\n", message, multicast_endpoint_.address().to_string());
    // Отправляем сообщение каждые 2 секунды
    io_context_.post([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        start_send();
    });
}
void MulticastApp::handle_send(const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
    if (!error) {
        std::cout << "message was sent successfully\n";
    }
}
void MulticastApp::check_alive() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::seconds timeout(5);

    // Удаляем копии, которые не отправляли сообщения больше 5 секунд
    for (auto it = alive_peers_.begin(); it != alive_peers_.end(); ) {
        if (now - it->second > timeout) {
            it = alive_peers_.erase(it);
        } else {
            ++it;
        }
    }

    // Выводим обновленный список "живых" копий
    display_alive_peers();

    // Планируем следующую проверку через 1 секунду
    timer_.expires_after(std::chrono::seconds(1));
    timer_.async_wait(boost::bind(&MulticastApp::check_alive, this));
}
void MulticastApp::display_alive_peers() {
    std::cout << std::format("Alive peers {}:\n", this->alive_peers_print_count++);
    for (const auto& peer : alive_peers_) {
        std::cout << peer.first << std::endl;
    }
    std::cout << std::endl;
}