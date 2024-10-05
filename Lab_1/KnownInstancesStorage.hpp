//
// Created by plushjill on 02.10.2024.
//

#ifndef LAB_1_KNOWNINSTANCESSTORAGE_HPP
#define LAB_1_KNOWNINSTANCESSTORAGE_HPP
#include <mutex>
#include <boost/unordered_map.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <map>

class KeyType {
private:
    boost::asio::ip::address address_;
    boost::asio::ip::port_type port_;

public:
    KeyType(const std::string &address,
            boost::asio::ip::port_type port);

    KeyType(boost::asio::ip::address address,
            boost::asio::ip::port_type port);

    bool operator<(const KeyType &other) const {
        return std::tie(address_, port_) < std::tie(other.address_, other.port_);
    }
    [[nodiscard]] std::string to_string() const {
        return "[" + address_.to_string() + ':' + std::to_string(port_) + "]";
    }

    [[nodiscard]] const boost::asio::ip::address &getAddress() const;
    [[nodiscard]] boost::asio::ip::port_type getPort() const;
};



class KnownInstancesStorage {
private:
    std::mutex mutex_;
    static constexpr int timeout_ {30};
    std::map<KeyType, int> storage_;
    bool changed_;
public:

    KnownInstancesStorage();
    /**
     * @brief Проверяет менялось ли хранилище.
     *
     * Используется, когда нужно узнать изменялось ли с момента последнего
     * вызова print_storage()
     * @return true если изменялось
     * @return false если не изменялось
     */
    bool is_changed();
    /**
     * @brief устанавливает значение changed_ в true
     */
    void set_changed();
    /**
    * @brief устанавливает значение changed_ в true
     * и выводит причину этого изменения в std::cout.
    */
    void set_changed(std::string reason);
    /**
    * @brief Возвращает ссылку на хранилище.
     * @return std::map<KeyType, int>&
    */
    [[nodiscard]] std::map<KeyType, int>& getStorage();
    /**
    * @brief выводит хранилище в std::cout и ставит changed_ в true
    */
    void print_storage();
    /**
     * @brief добавляет значение в хранилище, если уже есть, обновляет таймер
     * @param key ключ для мапы,
     * в ключе адрес boost::asio::ip::address и boost::asio::ip::port_type
     */
    void add(const KeyType& key);
};


#endif //LAB_1_KNOWNINSTANCESSTORAGE_HPP