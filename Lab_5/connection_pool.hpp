#ifndef SOCKET_POOL_H
#define SOCKET_POOL_H

#include <boost/asio.hpp>
#include "connection.hpp"


class ConnectionPool {
private:
    boost::asio::io_context& io_context_;
    std::vector<std::shared_ptr<Connection>> connections_;
    std::size_t pool_size_ = 0;

public:
    explicit ConnectionPool(boost::asio::io_context& io);
    void addConnection(std::shared_ptr<Connection> connection);
    std::shared_ptr<Connection> getConnection();
    size_t size();
};

#endif // SOCKET_POOL_H