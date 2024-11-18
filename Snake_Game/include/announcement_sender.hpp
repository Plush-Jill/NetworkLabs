////
//// Created by plushjill on 18.11.2024.
////
//
//#ifndef SNAKE_GAME_ANNOUNCEMENT_SENDER_HPP
//#define SNAKE_GAME_ANNOUNCEMENT_SENDER_HPP
//#include <chrono>
//#include <boost/asio.hpp>
//
//
//class AnnouncementSender {
//private:
//    constexpr static std::chrono::seconds m_announcement_delay {1};
//    static const boost::asio::ip::address m_multicast_address;
//    constexpr static boost::asio::ip::port_type m_multicast_port {9192};
//
//    static boost::asio::io_context& m_io_context;
//    static boost::asio::ip::udp::socket m_socket;
//    static boost::asio::ip::udp::endpoint m_remote_endpoint;
//
//    static void send_announcement();
//public:
//    static void start_sending();
//};
//
//
//#endif //SNAKE_GAME_ANNOUNCEMENT_SENDER_HPP
