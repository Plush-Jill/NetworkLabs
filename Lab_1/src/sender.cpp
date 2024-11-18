//
// Created by plushjill on 01.10.2024.
//

#include "../include/sender.hpp"
#include <iostream>

Sender::Sender(const std::shared_ptr<boost::asio::io_context>& io_context,
               const boost::asio::ip::address& multicast_address) :
        m_io_context(io_context),
        m_endpoint(multicast_address, m_multicast_port),
        m_socket(*io_context, m_endpoint.protocol()),
        m_timer(*io_context),
        m_sent_messages_count(0){

}

void Sender::send() {
    this->m_socket.async_send_to(boost::asio::buffer(this->m_message),
                                 this->m_endpoint,
                                 [this](boost::system::error_code error_code, std::size_t sent_size){
        if (!error_code) {
            m_timer.expires_after(m_timeout);
            m_timer.async_wait([this](boost::system::error_code error_code){
                if (!error_code) {
                    send();
                }
            });
        }
    });
}
