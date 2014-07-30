#pragma once

#include "boost/optional.hpp"

struct ITurnActions
{
    virtual ~ITurnActions() { }
 
    virtual boost::optional<int> Roll() = 0;
};
