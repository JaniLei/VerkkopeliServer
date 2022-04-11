#pragma once
#include "Connection.h"

class Server
{
private:
    static const unsigned int port_ = 4400;
    static const unsigned int max_connections_ = 2;
    tcp::acceptor acceptor_;
    boost::asio::io_context& io_context_;
    Connection::pointer connections_[max_connections_];

    void start_accept(Connection::pointer connection);

public:
    Server(boost::asio::io_context& io_context, Connection::pointer* connections);

    void handle_accept(Connection::pointer connection, const boost::system::error_code& err);

    void SendResult(int connection_id, GameResultData result);
};

