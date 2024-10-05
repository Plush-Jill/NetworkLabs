//
// Created by plushjill on 01.10.2024.
//

#include "Receiver.hpp"
#include <iostream>

Receiver::Receiver(const std::shared_ptr<boost::asio::io_context>& io_context,
                   const boost::asio::ip::address& listen_address,
                   const boost::asio::ip::address& multicast_address,
                   const std::shared_ptr<KnownInstancesStorage>& storage) :
                   io_context_(io_context),
                   socket_(*io_context_),
                   listen_endpoint_(listen_address, multicast_port_),
                   storage_(storage){
    socket_.open(listen_endpoint_.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint_);
    socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address));

}

void Receiver::receive() {
    this->socket_.async_receive_from(boost::asio::buffer(this->data_),
                                     this->sender_endpoint_,
                                     [this](boost::system::error_code error_code, std::size_t received_size) {
        if (!error_code) {
            storage_->add({sender_endpoint_.address(), sender_endpoint_.port()});
            receive();
        }
    });
}
