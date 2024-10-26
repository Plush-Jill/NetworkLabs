//
// Created by plushjill on 09.10.2024.
//

#ifndef LAB_2_SERVER_HPP
#define LAB_2_SERVER_HPP


#include <iostream>
#include <algorithm>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include "ClientInfo.hpp"


class Server {
public:
    Server(int server_port);
    void start();

private:
    std::string get_local_ip();
    void handle_connection(boost::asio::ip::tcp::socket socket);
    size_t handle_reading(boost::system::error_code& ec, size_t bytes_transferred);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::filesystem::path uploads_dir_;
};



#endif //LAB_2_SERVER_HPP
