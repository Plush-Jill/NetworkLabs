#include "connection_pool.hpp"


ConnectionPool::ConnectionPool(boost::asio::io_context &io) : io_context_(io) {}

void ConnectionPool::addConnection(std::shared_ptr<Connection> connection) {
    // std::cout << "Connection " << connection->get_socket().remote_endpoint() << " closed" << std::endl;
    if (connection->get_socket().is_open()) {
        connection->close();
        connections_.push_back(connection);
        ++pool_size_;
    }
}

std::shared_ptr<Connection> ConnectionPool::getConnection() {
    if (connections_.empty()) {
        return std::make_shared<Connection>(io_context_);
    } else {
        auto connection = connections_.back();
        connections_.pop_back();
        --pool_size_;
        return connection;
    }
}

size_t ConnectionPool::size() {
    return pool_size_;
}
