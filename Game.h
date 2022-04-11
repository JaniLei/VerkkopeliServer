#pragma once
#include "Player.h"
#include "GameResultData.h"


enum GameState
{
	Connecting = 0,
	Ready = 1,
	End = 2
};

enum GameResult
{
	Draw = 0,
	Win = 1,
	Lose = 2,
};

class Game
{
private:
	int playerCount;
public:
	Player Players[2];
	GameState ConnectionState;
	void (*SendFunc)(int, GameResultData);

	Game();
	void SetPlayerChoice(int playerID, int choice);
	bool HasReceivedBoth();
	GameResultData GetWinner(int playerID);
	void PlayerConnected();
	void PlayerDisconnected();
};
