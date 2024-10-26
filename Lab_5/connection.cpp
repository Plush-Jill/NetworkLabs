//
// Created by plushjill on 26.10.2024.
//
#include "connection.hpp"


Connection::Connection(boost::asio::io_context &io_context) : socket_(io_context) {}

boost::asio::ip::tcp::socket &Connection::get_socket() {
    return socket_;
}

char *Connection::to_server_buffer() {
    return to_server_buffer_;
}

char *Connection::to_client_buffer() {
    return to_client_buffer_;
}

void Connection::close() {
    boost::system::error_code error_code;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
    if (socket_.is_open()) {
        socket_.close(error_code);
    }
}
