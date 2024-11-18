//
// Created by plushjill on 01.10.2024.
//

#include "../include/receiver.hpp"
#include <iostream>

Receiver::Receiver(const std::shared_ptr<boost::asio::io_context>& io_context,
                   const boost::asio::ip::address& listen_address,
                   const boost::asio::ip::address& multicast_address,
                   const std::shared_ptr<KnownInstancesStorage>& storage) :
        m_io_context(io_context),
        m_socket(*m_io_context),
        m_listen_endpoint(listen_address, m_multicast_port),
        m_storage(storage){
    m_socket.open(m_listen_endpoint.protocol());
    m_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    m_socket.bind(m_listen_endpoint);
    m_socket.set_option(boost::asio::ip::multicast::join_group(multicast_address));

}

void Receiver::receive() {
    this->m_socket.async_receive_from(boost::asio::buffer(this->m_data),
                                      this->m_sender_endpoint,
                                      [this](boost::system::error_code error_code, std::size_t received_size) {
        if (!error_code) {
            m_storage->add({m_sender_endpoint.address(), m_sender_endpoint.port()});
            receive();
        }
    });
}
