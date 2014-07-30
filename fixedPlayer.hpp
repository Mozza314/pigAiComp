#pragma once

#include "IPigBot.hpp"
#include "ITurnActions.hpp"

#include "boost/lexical_cast.hpp"

class FixedPlayer
:
    public IPigBot
{
private:
    int mStoppingNumber;
    std::string mName;

public:
    FixedPlayer(int stoppingNumber)
    :
        mStoppingNumber(stoppingNumber),
        mName("FixedPlayer:" + boost::lexical_cast<std::string>(stoppingNumber))
    {
    }
    
    void HandleGameStart(int players, int myPosition) { }
    void HandleGameEnd(int winningPosition) { }
    
    void PlayTurn(ITurnActions& ita)
    {
        int sum = 0;

        while (true)
        {
            boost::optional<int> roll = ita.Roll();
            assert(roll);
            sum += *roll;
            std::cout << GetName() << ": sum: " << sum << ", roll: " << *roll << std::endl;

            if (*roll == 6 || sum >= mStoppingNumber)
            {
                std::cout << std::endl;
                return;
            }
        }
    }
    
    void HandlePlayerTurn(int position, const std::vector<int>& rolls) { }
    const std::string& GetName() { return mName; }
};
