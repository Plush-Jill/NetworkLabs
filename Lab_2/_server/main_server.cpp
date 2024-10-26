#include "Server.hpp"


int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
            return 1;
        }
        Server server(std::stoi(argv[1]));
        server.start();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}