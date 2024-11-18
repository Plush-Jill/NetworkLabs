//
// Created by plushjill on 18.11.2024.
//

#include "announcement_sender.hpp"
#include <iostream>

const boost::asio::ip::address AnnouncementSender::m_multicast_address
        = boost::asio::ip::address::from_string("239.192.0.4");


void AnnouncementSender::start_sending() {
    this->m_socket.async_send_to(
            boost::asio::buffer(this->m_message),
            this->m_remote_endpoint,
            [this](
                    boost::system::error_code error_code,
                    std::size_t sent_size) {
                if (!error_code) {
                    m_timer.expires_after(m_announcement_delay);
                    m_timer.async_wait([this](boost::system::error_code error_code) {
                        if (!error_code) {
                            start_sending();
                        }
                    });
                }
            });
}

AnnouncementSender::AnnouncementSender(
        const std::shared_ptr<boost::asio::io_context> &io_context
        ) :
        m_io_context(io_context),
        m_remote_endpoint(m_multicast_address, m_multicast_port),
        m_socket(*io_context, m_remote_endpoint),
        m_timer(*io_context)
        {
}
