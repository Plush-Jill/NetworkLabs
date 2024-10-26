//
// Created by plushjill on 09.10.2024.
//

#ifndef LAB_2_CLIENTINFO_HPP
#define LAB_2_CLIENTINFO_HPP


#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/timer/timer.hpp>



class ClientInfo {
public:
    ClientInfo(boost::asio::ip::tcp::endpoint endpoint);

    size_t get_total_bytes_received() const;
    void add_bytes_received(size_t bytesRead);
    void speed_check();
    void start_speed_checking();
    void print_speed_info();
    std::pair<double, std::string> convert_speed(double speed_in_bytes_per_second);
    void stop_timing();

    ~ClientInfo();
private:
    boost::asio::io_context io_context_;
    boost::asio::deadline_timer timer_;
    size_t current_bytes_received_;
    size_t total_bytes_received_;
    boost::timer::auto_cpu_timer second_timer_;
    bool is_data_ended_;
    boost::asio::ip::tcp::endpoint remote_endpoint_;
};



#endif //LAB_2_CLIENTINFO_HPP
