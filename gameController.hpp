#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "IPigBot.hpp"
#include "die.hpp"

class GameController
{
private:
    struct BotData
    {
        std::unique_ptr<IPigBot> bot;
        int score;
        int gameScore;
    };
    
    std::vector<BotData> mBots;
    Die mDie;

public:
    GameController() { }
    
    static int GetWinningScore() { return 100; }
    
    void AddBot(std::unique_ptr<IPigBot> bot)
    {
        mBots.push_back(BotData{std::move(bot), 0, 0});
    }
    
    const std::string& RunGame()
    {
        std::random_shuffle(mBots.begin(), mBots.end());
        
        for (int pos = 0; pos != mBots.size(); ++pos)
        {
            mBots[pos].bot->HandleGameStart(mBots.size(), pos);
        }
        
        boost::optional<int> winningPosition;
        
        while (!winningPosition)
        {
            for (int pos = 0; pos != mBots.size(); ++pos)
            {
                BotData& currBotData = mBots[pos];
                currBotData.bot->PlayTurn(mDie);
                std::vector<int> rolls = mDie.GetRollsAndReset();
                
                for (BotData& bd : mBots)
                {
                    bd.bot->HandlePlayerTurn(pos, rolls);
                }
                
                int turnScore = 0;
                if (!rolls.empty() && rolls.back() != Die::GetClearingNumber())
                {
                    turnScore = std::accumulate(rolls.begin(), rolls.end(), 0);
                }
                
                currBotData.score += turnScore;
                
                if (currBotData.score >= GetWinningScore())
                {
                    winningPosition = pos;
                    ++currBotData.gameScore;
                    
                    break;
                }
            }
        }
        
        for (BotData& bd : mBots)
        {
            bd.bot->HandleGameEnd(*winningPosition);
            bd.score = 0;
        }

        return mBots[*winningPosition].bot->GetName();
    }
};
