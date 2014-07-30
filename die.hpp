#pragma once

#include <cmath>
#include <random>

#include "discreteDistributions.hpp"
#include "ITurnActions.hpp"

class Die
:
    public ITurnActions
{
private:
    std::default_random_engine mEngine;
    std::uniform_real_distribution<> mRand;
    std::vector<double> mDist;

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
        return 1 + SampleDiscreteDistribution(mDist, mRand(mEngine));
    }

public:
    static int GetClearingNumber() { return 6; }
    
    Die()
    :
        mEngine(GenerateSeed()),
        mRand(0.0, 1.0),
        mDist(CreateRandomDiscreteDistribution(6, [&](){ return mRand(mEngine); }))
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
