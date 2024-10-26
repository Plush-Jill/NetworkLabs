#include <iostream>
#include <string>
#include "proxy_server.hpp"
#include <boost/format.hpp>



Socks5Proxy::Socks5Proxy(boost::asio::ip::port_type proxy_port)
        : io_context_(),
          client_acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), proxy_port)),
          connection_pool_(io_context_) {}

void Socks5Proxy::start() {
    accept_connection();
    io_context_.run();
}

void Socks5Proxy::accept_connection() {
    auto connection = connection_pool_.getConnection();
    client_acceptor_.async_accept(connection->get_socket(),
                                  [this, connection](const boost::system::error_code& error_code) {
                                     if (!error_code) {
                                         std::cout << boost::format("New client connection: %1%") % connection->get_socket().remote_endpoint() << std::endl;
                                         handle_greeting(connection);
                                     }
                                     accept_connection();
                                 });
}

void Socks5Proxy::handle_greeting(const std::shared_ptr<Connection>& connection) {
    async_read(connection->get_socket(),
               boost::asio::buffer(connection->to_server_buffer(), 2),
               bind(
                       &Socks5Proxy::read_auth_methods,
                       this,
                       boost::placeholders::_1,
                       boost::placeholders::_2,
                       connection
                       )
               );
}

void Socks5Proxy::read_auth_methods(const boost::system::error_code& error_code,
                                    std::size_t length,
                                    std::shared_ptr<Connection> connection) {
    if (!error_code && length == 2 && connection->to_server_buffer()[0] == SOCKS5) {
        size_t count_of_methods = connection->to_server_buffer()[1];
        async_read(connection->get_socket(),
                   boost::asio::buffer(connection->to_server_buffer(), count_of_methods),
                   bind(&Socks5Proxy::send_server_choice,
                        this,
                        boost::placeholders::_1,
                        boost::placeholders::_2,
                        count_of_methods,
                        connection));
    }
    else {
        std::cerr << boost::format("Auth methods receiving error: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

void Socks5Proxy::send_server_choice(const boost::system::error_code& error_code,
                                     std::size_t length,
                                     std::size_t count_of_methods,
                                     std::shared_ptr<Connection> connection) {
    if (!error_code && length == count_of_methods) {
        connection->to_server_buffer()[0] = SOCKS5;
        connection->to_server_buffer()[1] = NO_AUTH;
        async_write(connection->get_socket(),
                    boost::asio::buffer(connection->to_server_buffer(), 2),
                    bind(&Socks5Proxy::handle_connection_request,
                         this,
                         boost::placeholders::_1,
                         boost::placeholders::_2,
                         connection));
    }
    else {
        std::cerr << boost::format("Server choice sending error: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

void Socks5Proxy::handle_connection_request(const boost::system::error_code& error_code,
                                            std::size_t length,
                                            std::shared_ptr<Connection> connection) {
    if (!error_code) {
        async_read(connection->get_socket(),
                   boost::asio::buffer(connection->to_server_buffer(), 3),
                   bind(&Socks5Proxy::read_address_type,
                        this,
                        boost::placeholders::_1,
                        boost::placeholders::_2,
                        connection));
    }
    else {
        std::cerr << boost::format("Client connection request is failed: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

void Socks5Proxy::read_address_type(const boost::system::error_code& error_code,
                                    std::size_t length,
                                    std::shared_ptr<Connection> connection) {
    if (!error_code && length == 3 && connection->to_server_buffer()[0] == SOCKS5 &&
            connection->to_server_buffer()[1] == CONNECT &&
            connection->to_server_buffer()[2] == RESERVED) {
        async_read(connection->get_socket(),
                   boost::asio::buffer(connection->to_server_buffer(), 1),
                   bind(&Socks5Proxy::handle_address,
                        this,
                        boost::placeholders::_1,
                        boost::placeholders::_2,
                        connection));
    }
    else {
        std::cerr << boost::format("Address type reading error: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

void Socks5Proxy::handle_address(const boost::system::error_code& error_code,
                                 std::size_t length,
                                 std::shared_ptr<Connection> connection) {
    if (!error_code && length == 1) {
        uint8_t address_type = connection->to_server_buffer()[0];
        if (address_type == IPv4) {
            async_read(connection->get_socket(),
                       boost::asio::buffer(connection->to_server_buffer(), 6),
                       bind(&Socks5Proxy::read_IPv4_address,
                            this,
                            boost::placeholders::_1,
                            boost::placeholders::_2,
                            connection));
        }
        else if (address_type == DOMAIN_NAME) {
            async_read(connection->get_socket(),
                       boost::asio::buffer(connection->to_server_buffer(), 1),
                       bind(&Socks5Proxy::get_domain_length,
                            this,
                            boost::placeholders::_1,
                            boost::placeholders::_2,
                            connection));
        }
        else {
            connection_pool_.addConnection(connection);
        }
    }
    else {
        std::cerr << boost::format("Address handling error: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

void Socks5Proxy::read_IPv4_address(const boost::system::error_code& error_code,
                                    std::size_t length,
                                    std::shared_ptr<Connection> connection) {
    if (!error_code && length == 6) {
        boost::asio::ip::address_v4::bytes_type ip_address_bytes;
        memcpy(ip_address_bytes.data(), &connection->to_server_buffer()[0], 4);
        boost::asio::ip::address_v4 ip(ip_address_bytes);

        uint16_t port;
        memcpy(&port, &connection->to_server_buffer()[4], 2);
        port = ntohs(port);

        auto remote_socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);

        remote_socket->async_connect(boost::asio::ip::tcp::endpoint(ip, port),
                                     bind(&Socks5Proxy::send_server_response,
                                          this,
                                          boost::placeholders::_1,
                                          connection,
                                          remote_socket,
                                          boost::asio::ip::tcp::endpoint(ip, port)));
    }
    else {
        std::cerr << boost::format("IPv4 address reading error: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

void Socks5Proxy::get_domain_length(const boost::system::error_code& error_code,
                                    std::size_t length,
                                    std::shared_ptr<Connection> connection) {
    if (!error_code && length == 1) {
        uint16_t name_length;
        memcpy(&name_length, &connection->to_server_buffer()[0], 1);
        std::cout << boost::format("Domain name length: %1%") % name_length << std::endl;

        async_read(connection->get_socket(),
                   boost::asio::buffer(connection->to_server_buffer(), name_length + 2),
                   bind(&Socks5Proxy::get_domain_name,
                        this,
                        boost::placeholders::_1,
                        boost::placeholders::_2,
                        connection));
    }
    else {
        std::cerr << boost::format("Get domain length error: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

void Socks5Proxy::get_domain_name(const boost::system::error_code& error_code,
                                  std::size_t length,
                                  std::shared_ptr<Connection> connection) {
    if (!error_code) {
        std::cout << boost::format("Domain name and port length: %1%") % length << std::endl;

        std::vector<char> host_name(length - 2);
        for (size_t i = 0; i < length - 2; ++i) {
            host_name[i] = static_cast<char>(connection->to_server_buffer()[i]);
        }

        uint16_t dest_port;
        memcpy(&dest_port, &connection->to_server_buffer()[length - 2], 2);
        dest_port = ntohs(dest_port);

        if (resolved_hosts_[std::string(host_name.data(), length - 2)] !=
        boost::asio::ip::make_address_v4("0.0.0.0")) {
            boost::asio::ip::tcp::endpoint(this->resolved_hosts_[std::string(host_name.data(), length - 2)], dest_port);
        }
        boost::asio::ip::tcp::resolver resolver(io_context_);
        boost::asio::ip::tcp::resolver::query query{std::string(host_name.data(), length - 2),
                                                    std::to_string(dest_port)};
        // std::cout << std::string(host_name.data(), length - 2) << ' ' << dest_port << std::endl;
        // resolver.async_resolve(tcp::v4() ,query, );
        //     tcp::endpoint endpoint = *it;
        //     resolved_hosts_[std::string(host_name.data(), length - 2)] = endpoint.address().to_v4();
        std::cout << "Coming soon" << std::endl;
    }
    else {
        std::cerr << boost::format("Domain resolve error: %1%") % error_code.message() << std::endl;
        connection_pool_.addConnection(connection);
    }
}

unsigned char Socks5Proxy::get_connection_error(const boost::system::error_code& error_code) {
    if (!error_code) {
        return SUCCESS;
    }
    if (error_code == boost::asio::error::network_unreachable) {
        return NETWORK_UNREACHABLE;
    } if (error_code == boost::asio::error::host_unreachable) {
        return HOST_UNREACHABLE;
    } if (error_code == boost::asio::error::connection_refused) {
        return CONNECTION_REFUSED;
    } if (error_code == boost::asio::error::timed_out) {
        return TTL_EXPIRED;
    } if (error_code == boost::asio::error::address_family_not_supported) {
        return ADDRESS_TYPE_NOT_SUPPORTED;
    }
    return SUCCESS;
}

void Socks5Proxy::send_server_response(const boost::system::error_code& error_code,
                                       const std::shared_ptr<Connection>& connection,
                                       const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket,
                                       boost::asio::ip::tcp::endpoint remote_endpoint) {
    connection->to_server_buffer()[0] = SOCKS5;
    connection->to_server_buffer()[1] = get_connection_error(error_code);
    connection->to_server_buffer()[2] = RESERVED;
    connection->to_server_buffer()[3] = IPv4;

    boost::asio::ip::address address = remote_endpoint.address();
    uint16_t port = htons(remote_endpoint.port());

    boost::asio::ip::address_v4::bytes_type address_bytes = address.to_v4().to_bytes();

    for (size_t i = 0; i < address_bytes.size(); ++i) {
        connection->to_server_buffer()[i + 4] = address_bytes[i];
    }

    memcpy(&connection->to_server_buffer()[address_bytes.size() + 4], &port, 2);

    if (!error_code) {
        std::cout << boost::format("Connected to remote server %1%") % remote_socket->remote_endpoint() << std::endl;
        async_write(connection->get_socket(),
                    boost::asio::buffer(connection->to_server_buffer(),
                                        address_bytes.size() + 6),
                    bind(&Socks5Proxy::start_data_transfer,
                         this,
                         boost::placeholders::_1,
                         boost::placeholders::_2,
                         connection,
                         remote_socket));
    }
    else {
        std::cout << boost::format("Connection to server has been failed. Reason: %1%") % error_code.message() << std::endl;
        async_write(connection->get_socket(),
                    boost::asio::buffer(connection->to_server_buffer(), address_bytes.size() + 6),
                    bind(&ConnectionPool::addConnection, &this->connection_pool_, connection));
    }
}

void Socks5Proxy::start_data_transfer(const boost::system::error_code& error_code,
                                      std::size_t,
                                      std::shared_ptr<Connection> connection,
                                      std::shared_ptr<boost::asio::ip::tcp::socket> remote_socket) {
    try {
        if (!error_code) {
            connection->get_socket().async_read_some(boost::asio::buffer(connection->to_server_buffer(), max_length_),
                                                     bind(&Socks5Proxy::send_data_to_server,
                                                          this,
                                                          boost::placeholders::_1,
                                                          boost::placeholders::_2,
                                                          connection,
                                                          remote_socket));
            remote_socket->async_read_some(boost::asio::buffer(connection->to_client_buffer(),
                                                               max_length_),
                                           bind(&Socks5Proxy::send_data_to_client,
                                                this,
                                                boost::placeholders::_1,
                                                boost::placeholders::_2,
                                                connection,
                                                remote_socket));
        }
        else {
            connection_pool_.addConnection(connection);
            if (remote_socket->is_open()) {
                remote_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                remote_socket->close();
            }
        }
    }
    catch (boost::system::system_error& e) {
        std::cerr << boost::format("start_data_transfer: %1%") % e.what() << std::endl;
    }
}

void Socks5Proxy::send_data_to_server(const boost::system::error_code& error_code,
                                      std::size_t length, std::shared_ptr<Connection> connection,
                                      std::shared_ptr<boost::asio::ip::tcp::socket> remote_socket) {
    try {
        if (!error_code) {
            async_write(*remote_socket,
                        boost::asio::buffer(connection->to_server_buffer(), length),
                        bind(&Socks5Proxy::receive_data_from_client,
                             this,
                             boost::placeholders::_1,
                             boost::placeholders::_2,
                             connection, remote_socket));
        }
        else {
            connection_pool_.addConnection(connection);
            if (remote_socket->is_open()) {
                remote_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                remote_socket->close();
            }
        }
    }
    catch (boost::system::system_error& e) {}
}

void Socks5Proxy::send_data_to_client(const boost::system::error_code& error_code,
                                      std::size_t length,
                                      std::shared_ptr<Connection> connection,
                                      std::shared_ptr<boost::asio::ip::tcp::socket> remote_socket) {
    try {
        if (!error_code) {
            async_write(connection->get_socket(),
                        boost::asio::buffer(connection->to_client_buffer(), length),
                        bind(&Socks5Proxy::receive_data_from_server,
                             this,
                             boost::placeholders::_1,
                             boost::placeholders::_2,
                             connection, remote_socket));
        }
        else {
            connection_pool_.addConnection(connection);
            if (remote_socket->is_open()) {
                remote_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                remote_socket->close();
            }
        }
    }
    catch (boost::system::system_error& e) {}
}

void Socks5Proxy::receive_data_from_client(const boost::system::error_code& error_code,
                                           std::size_t length,
                                           std::shared_ptr<Connection> connection,
                                           std::shared_ptr<boost::asio::ip::tcp::socket> remote_socket) {
    try {
        if (!error_code) {
            connection->get_socket().async_read_some(boost::asio::buffer(connection->to_server_buffer(),
                                                                         max_length_),
                                                     bind(&Socks5Proxy::send_data_to_server,
                                                          this,
                                                          boost::placeholders::_1,
                                                          boost::placeholders::_2,
                                                          connection,
                                                          remote_socket));
        }
        else {
            connection_pool_.addConnection(connection);
            if (remote_socket->is_open()) {
                remote_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                remote_socket->close();
            }
        }
    }
    catch(boost::system::system_error& e) {}
}

void Socks5Proxy::receive_data_from_server(const boost::system::error_code& error_code,
                                           std::size_t length,
                                           const std::shared_ptr<Connection>& connection,
                                           const std::shared_ptr<boost::asio::ip::tcp::socket>& remote_socket) {
    try {
        if (!error_code) {
            remote_socket->async_read_some(boost::asio::buffer(connection->to_client_buffer(),
                                                               max_length_),
                                           bind(&Socks5Proxy::send_data_to_client,
                                                this,
                                                boost::placeholders::_1,
                                                boost::placeholders::_2,
                                                connection,
                                                remote_socket));
        }
        else {
            connection_pool_.addConnection(connection);
            if (remote_socket->is_open()) {
                remote_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                remote_socket->close();
            }
        }
    }
    catch(boost::system::system_error& e) {}
}