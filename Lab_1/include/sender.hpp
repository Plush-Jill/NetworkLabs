//
// Created by plushjill on 01.10.2024.
//

#ifndef LAB_1_SENDER_HPP
#define LAB_1_SENDER_HPP
#include <boost/asio.hpp>
#include "known_instances_storage.hpp"

class Sender {
private:
    std::shared_ptr<boost::asio::io_context> m_io_context;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_endpoint;
    boost::asio::steady_timer m_timer;
    static constexpr boost::asio::ip::port_type m_multicast_port {30001};
    static constexpr std::chrono::seconds m_timeout {10};
    unsigned int m_sent_messages_count;
    std::string m_message;
public:
    /**
     * @brief запускает асинхронную периодическую отправку сообщений на мультикаст адрес
     */
    void send();
    Sender(const std::shared_ptr<boost::asio::io_context>& io_context,
           const boost::asio::ip::address& multicast_address);
};


#endif //LAB_1_SENDER_HPP
