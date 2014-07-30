#pragma once

#include <string>
#include <vector>

#include "ITurnActions.hpp"
 
struct IPigBot
{
    virtual ~IPigBot() { }
 
    virtual void HandleGameStart(int players, int myPosition) = 0;
    virtual void HandleGameEnd(int winningPosition) = 0;
    virtual void PlayTurn(ITurnActions& ita) = 0;
    virtual void HandlePlayerTurn(int position, const std::vector<int>& rolls) = 0;
    virtual const std::string& GetName() = 0;
};
