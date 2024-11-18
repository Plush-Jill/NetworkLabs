//
// Created by plushjill on 02.10.2024.
//

#include "../include/known_instances_storage.hpp"

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
    std::lock_guard<std::mutex> lock_guard {this->m_mutex};
    if (!this->m_storage.contains(key)) {
        this->m_storage.insert(std::pair<KeyType, boost::chrono::seconds>(key, m_timeout));
        set_changed("added new entry");
    } else {
        this->m_storage[key] = KnownInstancesStorage::m_timeout;
    }

}

void KnownInstancesStorage::print_storage() {
    std::lock_guard<std::mutex> lock_guard {this->m_mutex};
    std::cout << "Alive instances:\n";
    for (std::pair<KeyType, boost::chrono::seconds> map_entry : this->m_storage){
        std::cout << std::format("{}:{} - {} sec\n",
                                 map_entry.first.getAddress().to_string(),
                                 map_entry.first.getPort(),
                                 map_entry.second.count());
    }
    std::cout << std::endl;
    this->m_is_changed = false;

}

std::map<KeyType, boost::chrono::seconds>& KnownInstancesStorage::getStorage() {
    return this->m_storage;
}

bool KnownInstancesStorage::is_changed() {
    return this->m_is_changed;
}

KnownInstancesStorage::KnownInstancesStorage() : m_is_changed(false) {}

void KnownInstancesStorage::set_changed() {
    this->m_is_changed = true;
}
void KnownInstancesStorage::set_changed(std::string reason) {
    this->m_is_changed = true;
//    std::cout << std::format("Storage was changed by reason: {}\n", reason);
}
