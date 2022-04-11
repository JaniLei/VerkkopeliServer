#include "Game.h"

Game::Game() {}

void Game::SetPlayerChoice(int playerID, int choice)
{
	Players[playerID].Choice = choice;

	if (HasReceivedBoth())
	{
		for (auto player : Players)
		{
			SendFunc(player.ID, GetWinner(player.ID));
		}

		Players[0].Choice = RPS_NONE;
		Players[1].Choice = RPS_NONE;
	}
}

bool Game::HasReceivedBoth()
{
	return (Players[0].Choice != RPS_NONE && Players[1].Choice != RPS_NONE);
}

GameResultData Game::GetWinner(int playerID)
{
	int winner = 3;

	Player thisPlayer = Players[playerID];
	Player otherPlayer = (playerID == 0) ? Players[1] : Players[0];

	if (thisPlayer.Choice != otherPlayer.Choice)
	{
		switch (thisPlayer.Choice)
		{
		case RPS_ROCK:
			winner = (otherPlayer.Choice == RPS_SCISSORS) ? thisPlayer.ID : otherPlayer.ID;
		case RPS_PAPER:
			winner = (otherPlayer.Choice == RPS_ROCK) ? thisPlayer.ID : otherPlayer.ID;
		case RPS_SCISSORS:
			winner = (otherPlayer.Choice == RPS_PAPER) ? thisPlayer.ID : otherPlayer.ID;
		default:
			break;
		}
	}

	GameResultData result = GameResultData(winner, otherPlayer.Choice);

	return result;
}

void Game::PlayerConnected()
{
	if (++playerCount >= 2)
		ConnectionState = GameState::Ready;
}

void Game::PlayerDisconnected()
{
	ConnectionState = GameState::End;
}
