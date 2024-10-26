#include "Server.hpp"
#include <boost/format.hpp>
Server::Server(int server_port)
        : io_context_(),
          acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), server_port)),
          uploads_dir_("uploads") {
}

void Server::start() {
    std::cout << boost::format("Server started listening connections on port %1%")
                 % acceptor_.local_endpoint().port()
              << std::endl;

    try {
        while (true) {
            boost::asio::ip::tcp::socket socket(io_context_);
            acceptor_.accept(socket);

            std::thread(&Server::handle_connection, this, std::move(socket)).detach();
        }

    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
    }
}

void Server::handle_connection(boost::asio::ip::tcp::socket socket) {
    try {
        boost::asio::ip::tcp::endpoint remote_endpoint = socket.remote_endpoint();
        std::cout << boost::format("New connection: %1%") % remote_endpoint << std::endl;

        boost::filesystem::create_directory(uploads_dir_);

        boost::asio::streambuf buffer_stream;
        std::string filename;

        ClientInfo* client_info = new ClientInfo(remote_endpoint);
        std::thread speed_check_thread(&ClientInfo::speed_check, client_info);


        read_until(socket, buffer_stream, '\n');

        std::istream filenameStream(&buffer_stream);
        getline(filenameStream, filename);

        std::cout << boost::format("%1% | Filename: %2%") % remote_endpoint % filename << std::endl;

        boost::filesystem::path file_path = uploads_dir_ / boost::filesystem::path(filename);
        std::ofstream output_file(file_path.string(), std::ios::binary);

        if (!output_file.is_open()) {
            std::cerr << boost::format("File opening failed: ") % file_path << std::endl;
            socket.close();
            return;
        }

        read_until(socket, buffer_stream, '\n');

        std::istream string_stream(&buffer_stream);
        std::string file_size_str;
        getline(string_stream, file_size_str);

        size_t file_size = stoull(file_size_str);
        std::cout << boost::format("%1% | File size: %2% bytes") % remote_endpoint % file_size << std::endl;


        std::string ready_status = "Ready";
        write(socket, boost::asio::buffer(ready_status + '\n'));

        char data[8192];
        size_t bytes_received = 0;
        size_t total_bytes_received = 0;
        size_t remaining_bytes = file_size;
        boost::system::error_code ec;

        while (remaining_bytes > 0) {
            size_t buffer_size = (remaining_bytes < sizeof(data)) ? remaining_bytes : sizeof(data);
            bytes_received = read(socket, boost::asio::buffer(data, buffer_size), ec);
            if (ec) {
                break;
            }

            output_file.write(data, static_cast<std::streamsize>(bytes_received));

            total_bytes_received += bytes_received;
            client_info->add_bytes_received(bytes_received);

            remaining_bytes -= bytes_received;
        }
        output_file.close();
        io_context_.run();

        total_bytes_received = client_info->get_total_bytes_received();

        std::cout << boost::format("%1% | File saved to %2%") % remote_endpoint % file_path << std::endl;
        std::cout << boost::format("%1% | Bytes received: %2%") % remote_endpoint % total_bytes_received << std::endl;


        std::string read_status;
        if (total_bytes_received == file_size) {
            read_status = "Success";
        } else {
            read_status = "Failure";
            boost::filesystem::remove(uploads_dir_.string() + '/' + filename);
        }
        std::cout << boost::format("%1% | File transferring status: %2%") % remote_endpoint % read_status << std::endl;
        write(socket, boost::asio::buffer(read_status + '\n'));
        client_info->stop_timing();
        speed_check_thread.join();
        delete client_info;

        std::cout << boost::format("Connection %1% is closed") % remote_endpoint << std::endl << std::endl;

        socket.close();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}

size_t Server::handle_reading(boost::system::error_code& ec, size_t bytes_transferred) {
    if (ec) {
        std::cout << bytes_transferred << std::endl;
        return 0;
    }
    return -1;
}