#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

size_t max_attempts;

class session {
public:
    session(boost::asio::io_service& io_service)
            : socket_(io_service) {}

    tcp::socket& socket() {
        return socket_;
    }

    void start() {
        auto ans = world.get_ans();
        socket_.write_some(boost::asio::buffer(ans, ans.size()));

        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&session::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            std::string ans;

            if (bytes_transferred != 1) {
                ans = "Error! Need only one char";
            } else if (num_attempts >= max_attempts) {
                ans = "Error! Only " + std::to_string(max_attempts) + " attempts";
            } else {
                world.open_char(data_[0]);
                ans = world.get_ans();
                num_attempts++;
            }

            boost::asio::async_write(socket_,
                                     boost::asio::buffer(ans, ans.size()),
                                     boost::bind(&session::handle_write, this,
                                                 boost::asio::placeholders::error));
        } else {
            delete this;
        }
    }

    void handle_write(const boost::system::error_code& error) {
        if (!error) {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                    boost::bind(&session::handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        } else {
            delete this;
        }
    }

private:
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];

    size_t num_attempts{0};
};

class server {
public:
    server(boost::asio::io_service& io_service, short port)
            : io_service_(io_service),
              acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
        session* new_session = new session(io_service_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(session* new_session,
                       const boost::system::error_code& error) {
        if (!error) {
            new_session->start();
            new_session = new session(io_service_);
            acceptor_.async_accept(new_session->socket(),
                                   boost::bind(&server::handle_accept, this, new_session,
                                               boost::asio::placeholders::error));
        } else {
            delete new_session;
        }
    }

private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
};
