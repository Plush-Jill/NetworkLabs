//
// Created by plushjill on 02.10.2024.
//

#include "KnownInstancesStorage.hpp"

#include <utility>
#include <iostream>

KeyType::KeyType(boost::asio::ip::address address, boost::asio::ip::port_type port) :
                address_(std::move(address)), port_(port){

}

KeyType::KeyType(const std::string& address, boost::asio::ip::port_type port) :
                address_(boost::asio::ip::address::from_string(address)), port_(port){

}

const boost::asio::ip::address &KeyType::getAddress() const {
    return this->address_;
}

boost::asio::ip::port_type KeyType::getPort() const {
    return this->port_;
}

void KnownInstancesStorage::add(const KeyType& key) {
    std::lock_guard<std::mutex> lock_guard {this->mutex_};
    if (!this->storage_.contains(key)) {
        this->storage_.insert(std::pair<KeyType, boost::chrono::seconds>(key, timeout_));
        set_changed("added new entry");
    } else {
        this->storage_[key] = KnownInstancesStorage::timeout_;
    }

}

void KnownInstancesStorage::print_storage() {
    std::lock_guard<std::mutex> lock_guard {this->mutex_};
    std::cout << "Alive instances:\n";
    for (std::pair<KeyType, boost::chrono::seconds> map_entry : this->storage_){
        std::cout << std::format("{}:{} - {} sec\n",
                                 map_entry.first.getAddress().to_string(),
                                 map_entry.first.getPort(),
                                 map_entry.second.count());
    }
    std::cout << std::endl;
    this->changed_ = false;

}

std::map<KeyType, boost::chrono::seconds>& KnownInstancesStorage::getStorage() {
    return this->storage_;
}

bool KnownInstancesStorage::is_changed() {
    return this->changed_;
}

KnownInstancesStorage::KnownInstancesStorage() : changed_(false) {}

void KnownInstancesStorage::set_changed() {
    this->changed_ = true;
}
void KnownInstancesStorage::set_changed(std::string reason) {
    this->changed_ = true;
//    std::cout << std::format("Storage was changed by reason: {}\n", reason);
}
