#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <set>
#include <string>
#include <chrono>
#include <thread>
#include <unordered_map>

class MulticastApp {
public:
    MulticastApp(boost::asio::io_context& io_context, const std::string& multicast_address, short multicast_port);

private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    boost::asio::ip::udp::endpoint multicast_endpoint_;
    boost::asio::steady_timer timer_;
    std::string multicast_address_;
    std::array<char, 1024> receive_buffer_;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> alive_peers_;
    int alive_peers_print_count = 0;
    int sent_messages_count = 0;


    void start_receive();
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
    void start_send();
    void handle_send(const boost::system::error_code& error, std::size_t /*bytes_transferred*/);
    void check_alive();
    void display_alive_peers();
};
