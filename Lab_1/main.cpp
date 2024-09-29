#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include <string>
#include "MulticastApp.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <multicast_address> <multicast_port>\n";
        return 1;
    }

    std::string multicast_address = argv[1];
    short multicast_port = static_cast<short>(std::stoi(argv[2]));

    try {
        boost::asio::io_context io_context;
        MulticastApp app(io_context, multicast_address, multicast_port);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}