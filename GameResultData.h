#pragma once
#include <string>

class GameResultData
{
public:
    int WinnerID;
    int OtherPlayerChoice;

    GameResultData(int winner, int choice) : WinnerID(winner), OtherPlayerChoice(choice) {}

    std::string ToText()
    {
        std::string text = "";
        text += std::to_string(WinnerID);
        text += std::to_string(OtherPlayerChoice);
        return std::string(text);
    }

    static GameResultData FromText(std::string text)
    {
        int winner = text[0] - '0';
        int choice = text[1] - '0';
        return GameResultData(winner, choice);
    }
};
