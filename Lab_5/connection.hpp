#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <array>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>


class Connection {
private:
    constexpr static const int buffer_size_ {8192};
    boost::asio::ip::tcp::socket socket_;
    char to_server_buffer_[buffer_size_];
    char to_client_buffer_[buffer_size_];

public:
    explicit Connection(boost::asio::io_context& io_context);

    boost::asio::ip::tcp::socket& get_socket();
    char* to_server_buffer();
    char* to_client_buffer();
    void close();

};

#endif // CONNECTION_H