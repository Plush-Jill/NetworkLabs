////
//// Created by plushjill on 18.11.2024.
////
//
//#include "announcement_sender.hpp"
//#include <iostream>
//#include "util/protobuf_manager.hpp"
//
//const boost::asio::ip::address AnnouncementSender::m_multicast_address
//        = boost::asio::ip::address::from_string("239.192.0.4");
//
//void AnnouncementSender::start_sending() {
//    boost::asio::ip::udp::endpoint multicast_endpoint(
//            m_multicast_address,
//            m_multicast_port);
//
//    boost::asio::steady_timer timer(m_io_context, m_announcement_delay);
//
//    timer.async_wait([&timer, multicast_endpoint](const boost::system::error_code& error_code) {
//        if (!error_code) {
//            send_announcement();
//            start_sending(); // Повторная отправка через 1 секунду
//        }
//    });
//}
//
//void AnnouncementSender::send_announcement() {
//    std::string message = ProtobufManager::create_announcement(GameAnnouncement()).SerializeAsString();
//    boost::asio::ip::udp::endpoint endpoint(m_multicast_address, m_multicast_port);
//    m_socket.send_to(boost::asio::buffer(message), endpoint);
//    std::cout << "Announcement sent: " << message << std::endl;
//}