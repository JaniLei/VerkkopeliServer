#pragma once


//enum GameChoice
//{
//	None = 0,
//	Rock = 1,
//	Paper = 2,
//	Scissors = 3
//};

constexpr unsigned int RPS_NONE{ 0 };
constexpr unsigned int RPS_ROCK{ 1 };
constexpr unsigned int RPS_PAPER{ 2 };
constexpr unsigned int RPS_SCISSORS{ 3 };

class Player
{
public:
	int ID;
	int Choice;
};

