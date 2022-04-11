#include "Connection.h"
#include <boost/bind.hpp>
//#include "Serialization.h"


Connection::Connection(boost::asio::io_context& io_context, Game* game, int id) : socket_(io_context), game_(game), connection_id_(id) {}

//socket creation
tcp::socket& Connection::socket()
{
    return socket_;
}

void Connection::on_connect()
{
    is_connected = true;

    write(std::to_string(connection_id_));
    game_->PlayerConnected();

    read();
}

void Connection::read()
{
    socket_.async_read_some(
        boost::asio::buffer(receive_data_, max_length),
        boost::bind(&Connection::handle_read,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Connection::write(std::string data)
{
    send_data_ = data;

    socket_.async_write_some(
        boost::asio::buffer(send_data_, max_length),
        boost::bind(&Connection::handle_write,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Connection::handle_read(const boost::system::error_code& err, size_t bytes_transferred)
{
    if (!err)
    {
        receive_str_ = std::string(receive_data_);

        std::cout << "Server received: " + receive_str_ << std::endl;

        if (!receive_str_.empty())
        {
            game_->SetPlayerChoice(connection_id_, std::stoi(receive_str_));
            //if (game_->HasReceivedBoth())
            //{
            //    GameResultData res = game_->GetWinner(connection_id_);
            //
            //    write(res.ToText());
            //}
        }
        read();
    }
    else
    {
        close(err.message());
    }
}

void Connection::handle_write(const boost::system::error_code& err, size_t bytes_transferred)
{
    if (!err)
    {
        std::cout << "Server sent: " + send_data_ << std::endl;
    }
    else
    {
        close(err.message());
    }
}

void Connection::close(std::string errMsg)
{
    std::cerr << "error: " << errMsg << std::endl;
    socket_.close();
    game_->PlayerDisconnected();
}