//
// Created by plushjill on 01.10.2024.
//

#include "Sender.hpp"
#include <iostream>

Sender::Sender(const std::shared_ptr<boost::asio::io_context>& io_context,
               const boost::asio::ip::address& multicast_address) :
        io_context_(io_context),
        endpoint_(multicast_address, multicast_port_),
        socket_(*io_context, endpoint_.protocol()),
        timer_(*io_context),
        sent_messages_count_(0){

}

void Sender::send() {
    this->socket_.async_send_to(boost::asio::buffer(this->message_),
                                this->endpoint_,
                                [this](boost::system::error_code error_code, std::size_t sent_size){
        if (!error_code) {
            timer_.expires_after(timeout_);
            timer_.async_wait([this](boost::system::error_code error_code){
                if (!error_code) {
                    send();
                }
            });
        }
    });
}
