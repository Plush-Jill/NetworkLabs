//
// Created by plushjill on 01.10.2024.
//

#ifndef LAB_1_SENDER_HPP
#define LAB_1_SENDER_HPP
#include <boost/asio.hpp>
#include "KnownInstancesStorage.hpp"

class Sender {
private:
    std::shared_ptr<boost::asio::io_context> io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::steady_timer timer_;
    static constexpr boost::asio::ip::port_type multicast_port_ {30001};
    static constexpr std::chrono::seconds timeout_ {10};
    unsigned int sent_messages_count_;
    std::string message_;
public:
    /**
     * @brief запускает асинхронную периодическую отправку сообщений на мультикаст адрес
     */
    void send();
    Sender(const std::shared_ptr<boost::asio::io_context>& io_context,
           const boost::asio::ip::address& multicast_address);
};


#endif //LAB_1_SENDER_HPP
