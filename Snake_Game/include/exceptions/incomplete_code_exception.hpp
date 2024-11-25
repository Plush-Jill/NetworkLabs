//
// Created by plushjill on 26.11.2024.
//

#ifndef SNAKE_GAME_INCOMPLETE_CODE_EXCEPTION_HPP
#define SNAKE_GAME_INCOMPLETE_CODE_EXCEPTION_HPP
#include <exception>
#include <boost/stacktrace.hpp>
#include <utility>

class IncompleteCodeException : public std::exception {
private:
    std::string m_message;
    boost::stacktrace::stacktrace m_stacktrace;

public:
    explicit IncompleteCodeException(std::string  msg) :
        m_message(std::move(msg)),
        m_stacktrace(boost::stacktrace::stacktrace()) {}

    explicit IncompleteCodeException() :
            m_message("no message"),
            m_stacktrace(boost::stacktrace::stacktrace()) {}

    [[nodiscard]] const char* what() const noexcept override {
        return m_message.c_str();
    }

    [[nodiscard]] const boost::stacktrace::stacktrace& get_stacktrace() const noexcept {
        return m_stacktrace;
    }
};

#endif //SNAKE_GAME_INCOMPLETE_CODE_EXCEPTION_HPP
