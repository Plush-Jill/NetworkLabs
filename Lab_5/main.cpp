#include "proxy_server.hpp"
#include <boost/format.hpp>
#include <boost/asio.hpp>

void check_proxy_port(int port) {
    if (port < 0 || port > std::numeric_limits<unsigned short>::max()) {
        throw std::out_of_range("port doesn't exist");
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << boost::format("Usage: %1% <port>") % argv[0] << std::endl;
            return 1;
        }
        check_proxy_port(std::stoi(argv[1]));

        boost::asio::ip::port_type port = static_cast<boost::asio::ip::port_type>(std::stoi(argv[1]));
        Socks5Proxy proxy(port);
        proxy.start();
    }
    catch (std::out_of_range& exception) {
        std::cerr << exception.what() << std::endl;
    }
    catch (std::exception& exception) {
        std::cerr << exception.what() << std::endl;
    }

    return 0;
}