#include <algorithm>
#include <iostream>

#include "fixedPlayer.hpp"
#include "gameController.hpp"
#include "IPigBot.hpp"

int main()
{
    GameController gc;

    for (int stopNumber = 1; stopNumber <= 30; ++stopNumber)
    {
        std::unique_ptr<IPigBot> bot(new FixedPlayer(stopNumber));
        gc.AddBot(std::move(bot));
    }

    for (int i = 0; i != 10; ++i)
    {
        std::cout << gc.RunGame() << std::endl;
    }
    
    return 0;
}
