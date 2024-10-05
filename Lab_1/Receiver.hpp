//
// Created by plushjill on 01.10.2024.
//

#ifndef LAB_1_RECEIVER_HPP
#define LAB_1_RECEIVER_HPP
#include <boost/asio.hpp>
#include "KnownInstancesStorage.hpp"


class Receiver {
private:
    std::shared_ptr<boost::asio::io_context> io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    boost::asio::ip::udp::endpoint listen_endpoint_;
    static constexpr boost::asio::ip::port_type multicast_port_ {30001};
    static constexpr size_t buffer_size_ {1024};
    std::array<std::byte, buffer_size_> data_;
    std::shared_ptr<KnownInstancesStorage> storage_;
public:
    /**
     * @brief запускает асинхронное принятие сообщений
     */
    void receive();
    Receiver(const std::shared_ptr<boost::asio::io_context>& io_context,
             const boost::asio::ip::address& listen_address,
             const boost::asio::ip::address& multicast_address,
             const std::shared_ptr<KnownInstancesStorage>& storage);

};


#endif //LAB_1_RECEIVER_HPP
