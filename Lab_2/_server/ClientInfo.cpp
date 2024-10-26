//
// Created by plushjill on 09.10.2024.
//

#include "ClientInfo.hpp"


ClientInfo::ClientInfo(boost::asio::ip::tcp::endpoint endpoint)
        : io_context_(),
          timer_(io_context_),
          total_bytes_received_(0),
          second_timer_(),
          is_data_ended_(false),
          remote_endpoint_(endpoint) {}

uint64_t ClientInfo::get_total_bytes_received() const {
    return total_bytes_received_;
}

void ClientInfo::add_bytes_received(size_t bytesRead) {
    current_bytes_received_ += bytesRead;
    total_bytes_received_ += bytesRead;
}

void ClientInfo::speed_check() {
    start_speed_checking();
    io_context_.run();
}

void ClientInfo::start_speed_checking() {
    if (!is_data_ended_) {
        timer_.expires_from_now(boost::posix_time::seconds(3));
        timer_.async_wait(boost::bind(&ClientInfo::print_speed_info, this));
    }
}

void ClientInfo::print_speed_info() {
    if (current_bytes_received_ == 0) {
        start_speed_checking();
        return;
    }
    std::pair<double, std::string> speed;
    double instantaneous_speed = static_cast<double>(current_bytes_received_) / 3.0;
    speed = convert_speed(instantaneous_speed);
    std::cout << remote_endpoint_ << " | Instantaneous speed: " << speed.first << " " << speed.second << std::endl;
    current_bytes_received_ = 0;

    boost::timer::cpu_times elapsedTimes = second_timer_.elapsed();
    boost::timer::nanosecond_type elapsedNanoseconds = elapsedTimes.wall;
    double elapsed_seconds = static_cast<double>(elapsedNanoseconds) / 1e9;
    double average_speed = static_cast<double>(total_bytes_received_) / elapsed_seconds;
    speed = convert_speed(average_speed);
    std::cout << remote_endpoint_ << " | Average speed: " << speed.first << " " << speed.second << std::endl;

    start_speed_checking();
}

std::pair<double, std::string> ClientInfo::convert_speed(double speed_in_bytes_per_second) {
    std::pair<double, std::string> speed;
    const double bytes_in_megabyte = 1024 * 1024;
    const double bytes_in_gigabyte = 1024 * 1024 * 1024;

    if (speed_in_bytes_per_second >= bytes_in_gigabyte) {
        double speed_in_gigabytes_per_second = speed_in_bytes_per_second / bytes_in_gigabyte;
        speed.first = speed_in_gigabytes_per_second;
        speed.second = "GB/s";
    } else if (speed_in_bytes_per_second >= bytes_in_megabyte) {
        double speed_in_megabytes_per_second = speed_in_bytes_per_second / bytes_in_megabyte;
        speed.first = speed_in_megabytes_per_second;
        speed.second = "MB/s";
    } else {
        speed.first = speed_in_bytes_per_second;
        speed.second = "B/s";
    }
    return speed;
}

void ClientInfo::stop_timing() {
    is_data_ended_ = true;
}

ClientInfo::~ClientInfo() {
    second_timer_.stop();
}