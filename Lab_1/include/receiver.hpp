//
// Created by plushjill on 01.10.2024.
//

#ifndef LAB_1_RECEIVER_HPP
#define LAB_1_RECEIVER_HPP
#include <boost/asio.hpp>
#include "known_instances_storage.hpp"


class Receiver {
private:
    std::shared_ptr<boost::asio::io_context> m_io_context;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_sender_endpoint;
    boost::asio::ip::udp::endpoint m_listen_endpoint;
    static constexpr boost::asio::ip::port_type m_multicast_port {30001};
    static constexpr size_t m_buffer_size {1024};
    std::array<std::byte, m_buffer_size> m_data;
    std::shared_ptr<KnownInstancesStorage> m_storage;
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
