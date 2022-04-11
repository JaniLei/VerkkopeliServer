#include "Server.h"
#include <boost/bind.hpp>


Server::Server(boost::asio::io_context& io_context, Connection::pointer* connections) :
    acceptor_(io_context, tcp::endpoint(tcp::v4(), port_)),
    io_context_(io_context)
{
    for (int i = 0; i < max_connections_; i++)
    {
        connections_[i] = connections[i];
        start_accept(connections_[i]);
    }
}

void Server::start_accept(Connection::pointer connection)
{
    // asynchronous accept operation and wait for a new connection.
    acceptor_.async_accept(connection->socket(),
        boost::bind(&Server::handle_accept, this, connection,
            boost::asio::placeholders::error));
}

void Server::handle_accept(Connection::pointer connection, const boost::system::error_code& err)
{
    if (!err)
    {
        connection->on_connect();
    }
}

void Server::SendResult(int connection_id, GameResultData result)
{
    if (connections_[connection_id]->socket().is_open())
        connections_[connection_id]->write(result.ToText());
}
