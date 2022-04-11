#include "Server.h"

const unsigned int MAX_CONNECTIONS = 2;

Server* server;

void SendResult(int id, GameResultData result)
{
    server->SendResult(id, result);
}

int main()
{
    Game Verkkopeli;

    boost::asio::io_context io_context;

    // Start server
    Connection::pointer connections[MAX_CONNECTIONS];
    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        connections[i] = (Connection::create(io_context, &Verkkopeli, i));
        Verkkopeli.Players[i].ID = i;
    }

    server = new Server(io_context, connections);
    Verkkopeli.SendFunc = &SendResult;

    io_context.run();

	return 0;
}