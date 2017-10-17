#include "controllers.h"

int RegisterControl::getNext()
{
    for(unsigned int i = 0; i < SIZE_FLAGS; ++i)
    {
        if(!flags[i])
        {
            flags[i] = true;
            return i;
        }
    }

    return -1;
}

void RegisterControl::freePlace(int place)
{
    flags[place] = false;
}
