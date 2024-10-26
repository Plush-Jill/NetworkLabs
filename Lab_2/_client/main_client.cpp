#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <boost/format.hpp>

int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            std::cerr << boost::format("Usage: %1% <path_to_file> <server_address> <server_port>") % argv[0] << std::endl;
            return 1;
        }

        boost::filesystem::path file_path = argv[1];
        std::string filename = file_path.filename().string();
        if (filename.length() >= 4096) {
            std::cerr << "Filename is too long" << std::endl;
            return 1;
        }

        std::ifstream input_file(argv[1], std::ios::binary);
        if (!input_file.is_open()) {
            std::cerr << "File opening failed" << std::endl;
            return 1;
        }

        input_file.seekg(0, std::ios::end);
        uint64_t file_size = static_cast<uint64_t>(input_file.tellg());
        input_file.seekg(0, std::ios::beg);
        if (file_size >= 1024LL * 1024 * 1024 * 1024) {
            std::cerr << "File size is too big" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);

        boost::asio::ip::tcp::endpoint server_endpoint(boost::asio::ip::make_address(argv[2]), std::stoi(argv[3]));
        socket.connect(server_endpoint);

        std::cout << boost::format("Connected to %1%") % server_endpoint << std::endl;
        std::cout << boost::format("File name: %1%") % filename << std::endl;
        std::cout << boost::format("File size: %1% bytes") % file_size << std::endl;

        write(socket, boost::asio::buffer(filename + '\n'));
        write(socket, boost::asio::buffer(std::to_string(file_size) + '\n'));

        boost::asio::streambuf response_buffer;
        std::istream response_stream(&response_buffer);
        std::string response;

        read_until(socket, response_buffer, '\n');
        getline(response_stream, response);

        if (response != "Ready") {
            std::cerr << "Error: the server is not ready to receive data." << std::endl;
            return 1;
        }

        char data[8192];
        while (input_file) {
            input_file.read(data, sizeof(data));
            write(socket, boost::asio::buffer(data, input_file.gcount()));
        }

        read_until(socket, response_buffer, '\n');
        getline(response_stream, response);

        if (response == "Success") {
            std::cout << "The file has been successfully transferred to the server." << std::endl;
        } else {
            std::cerr << "Error: the file was not transferred to the server." << std::endl;
        }

        socket.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}




















/*
#include <iostream>
#include <boost/asio.hpp>
//#include <fstream>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/mapped_file.hpp>




int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            std::cerr << boost::format("Usage: %1% <path_to_file> <server_address> <server_port>") % argv[0] << std::endl;
            return 1;
        }

        boost::filesystem::path file_path = argv[1];
        std::string filename = file_path.filename().string();
        if (filename.length() >= 4096) {
            std::cerr << "Filename is too long" << std::endl;
            return 1;
        }

//        std::ifstream input_file(argv[1], std::ios::binary);
        boost::iostreams::mapped_file_source input_file;
        input_file.open(argv[1], boost::iostreams::mapped_file::mapmode::readonly);
        if (!input_file.is_open()) {
            std::cerr << "File opening failed" << std::endl;
            return 1;
        }

//        input_file.seekg(0, std::ios::end);
//        uint64_t file_size = static_cast<uint64_t>(input_file.tellg());
//        input_file.seekg(0, std::ios::beg);
        uint64_t file_size = input_file.size();  // Получаем размер файла
        if (file_size >= 1024LL * 1024 * 1024 * 1024) {
            std::cerr << "File size is too big" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);

        boost::asio::ip::tcp::endpoint server_endpoint(boost::asio::ip::make_address(argv[2]), std::stoi(argv[3]));
        socket.connect(server_endpoint);

        std::cout << boost::format("Connected to %1%") % server_endpoint << std::endl;
        std::cout << boost::format("File name: %1%") % filename << std::endl;
        std::cout << boost::format("File size: %1% bytes") % file_size << std::endl;

        write(socket, boost::asio::buffer(filename + '\n'));
        write(socket, boost::asio::buffer(std::to_string(file_size) + '\n'));

        boost::asio::streambuf response_buffer;
        std::istream response_stream(&response_buffer);
        std::string response;

        read_until(socket, response_buffer, '\n');
        getline(response_stream, response);

        if (response != "Ready") {
            std::cerr << "Error: the _server is not ready to receive data." << std::endl;
            return 1;
        }

//        char data[8192];
//        while (input_file) {
//            input_file.read(data, sizeof(data));
//            write(socket, boost::asio::buffer(data, input_file.gcount()));
//        }
//
//        read_until(socket, response_buffer, '\n');
//        getline(response_stream, response);


        const std::size_t chunk_size = 8192;  // Оптимальный размер чанка
        const char* data = input_file.data();
        uint64_t bytes_sent = 0;

        while (bytes_sent < file_size) {
            std::size_t bytes_to_send = std::min(chunk_size, file_size - bytes_sent);
            boost::asio::write(socket, boost::asio::buffer(data + bytes_sent, bytes_to_send));
            bytes_sent += bytes_to_send;
        }

        // Проверяем ответ от сервера после передачи файла
        boost::asio::read_until(socket, response_buffer, '\n');
        std::getline(response_stream, response);

        if (response == "Success") {
            std::cout << "The file has been successfully transferred to the _server." << std::endl;
        } else {
            std::cerr << "Error: the file was not transferred to the _server." << std::endl;
        }

        socket.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
*/