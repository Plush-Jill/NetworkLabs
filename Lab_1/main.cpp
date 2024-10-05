#include <iostream>
#include "MulticastApp.hpp"
/// 0.0.0.0 230.255.0.1
int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: receiver <listen_address> <multicast_address>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 239.255.0.1\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 ff31::8000:1234\n";
            return 1;
        }

        std::string listen_address = argv[1];
        std::string multicast_address = argv[2];
        MulticastApp multicast_app {listen_address, multicast_address};
        multicast_app.start();
        std::cout << "App started\n";
        sleep(60 * 30);

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }




    return 0;
}


