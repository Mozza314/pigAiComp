#pragma once

#include <cmath>
#include <random>

#include "ITurnActions.hpp"

class Die
:
    public ITurnActions
{
private:
    std::default_random_engine mEngine;
    std::uniform_int_distribution<int> mDist;

    std::vector<int> mRolls;
    bool mActive = true;
    
    static unsigned int GenerateSeed()
    {
        // Seed with a real random value, if available
        std::random_device rd;
        return rd();
    }

    int RawRoll()
    {
        return mDist(mEngine);
    }

public:
    static int GetClearingNumber() { return 6; }
    
    Die()
    :
        mEngine(GenerateSeed()),
        mDist(1, 6)
    {
    }
    
    boost::optional<int> Roll()
    {
        if (!mActive)
        {
            return boost::none;
        }
        
        int roll = RawRoll();
        mRolls.push_back(roll);

        if (roll == GetClearingNumber())
        {
            mActive = false;
        }

        return roll;
    }

    std::vector<int> GetRollsAndReset()
    {
        std::vector<int> rolls;
        std::swap(rolls, mRolls);
        mActive = true;
        
        return rolls;
    }
};
