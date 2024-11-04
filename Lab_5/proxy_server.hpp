#ifndef PROXY_SERVER_H
#define PROXY_SERVER_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <map>
#include "connection_pool.hpp"
#include "proxy_const.hpp"


class Socks5Proxy {
public:
    Socks5Proxy(unsigned short proxy_port);
    void start();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor client_acceptor_;
    ConnectionPool connection_pool_;
    std::map<std::string, boost::asio::ip::address_v4> resolved_hosts_;

    constexpr static const int max_length_ = 8192;

    void accept_connection();
    void handle_greeting(const std::shared_ptr<Connection>& connection);
    void read_auth_methods(const boost::system::error_code& error_code,
                           std::size_t length,
                           const std::shared_ptr<Connection>& connection);
    void send_server_choice(const boost::system::error_code& error_code,
                            std::size_t length,
                            std::size_t count_of_methods,
                            const std::shared_ptr<Connection>& connection);
    void handle_connection_request(const boost::system::error_code& error_code,
                                   std::size_t length,
                                   const std::shared_ptr<Connection>& connection);

    void read_address_type(const boost::system::error_code& error_code,
                           std::size_t length,
                           const std::shared_ptr<Connection>& connection);
    void handle_address(const boost::system::error_code& error_code,
                        std::size_t length,
                        std::shared_ptr<Connection> connection);

    void read_IPv4_address(const boost::system::error_code& error_code,
                           std::size_t length,
                           const std::shared_ptr<Connection>& connection);
    void get_domain_length(const boost::system::error_code& error_code,
                           std::size_t length,
                           const std::shared_ptr<Connection>& connection);
    void get_domain_name(const boost::system::error_code& error_code,
                         std::size_t length,
                         std::shared_ptr<Connection> connection);

    unsigned char get_connection_error(const boost::system::error_code& error_code);
    void send_server_response(const boost::system::error_code& error_code,
                              const std::shared_ptr<Connection>& connection,
                              const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket,
                              const boost::asio::ip::tcp::endpoint& remote_endpoint);

    void start_data_transfer(const boost::system::error_code& error_code,
                             std::size_t,
                             const std::shared_ptr<Connection>& connection,
                             const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket);
    void send_data_to_server(const boost::system::error_code& error_code,
                             std::size_t length,
                             const std::shared_ptr<Connection>& connection,
                             const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket);
    void send_data_to_client(const boost::system::error_code& error_code,
                             std::size_t length,
                             const std::shared_ptr<Connection>& connection,
                             const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket);
    void receive_data_from_client(const boost::system::error_code& error_code,
                                  std::size_t length,
                                  const std::shared_ptr<Connection>& connection,
                                  const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket);
    void receive_data_from_server(const boost::system::error_code& error_code,
                                  std::size_t length,
                                  const std::shared_ptr<Connection>& connection,
                                  const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket);
};

#endif // PROXY_SERVER_H