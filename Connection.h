#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include "Game.h"

using boost::asio::ip::tcp;


class Connection : public boost::enable_shared_from_this<Connection>
{
private:
    tcp::socket socket_;
    enum { max_length = 1024 };
    char receive_data_[max_length];
    std::string receive_str_;
    std::string send_data_;
    Game* game_;
    int connection_id_;

public:
    typedef boost::shared_ptr<Connection> pointer;

    bool is_connected;

    Connection(boost::asio::io_context& io_context, Game* game, int id);

    // creating the pointer
    static pointer create(boost::asio::io_context& io_context, Game* game, int id)
    {
        return pointer(new Connection(io_context, game, id));
    }
    //socket creation
    tcp::socket& socket();

    void on_connect();

    void read();
    void write(std::string data);

    void handle_read(const boost::system::error_code& err, size_t bytes_transferred);
    void handle_write(const boost::system::error_code& err, size_t bytes_transferred);
    void close(std::string errMsg = "");
};
