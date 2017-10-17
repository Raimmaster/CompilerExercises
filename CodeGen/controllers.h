#ifndef _CONTROLLERS_H
#define _CONTROLLERS_H

#define SIZE_FLAGS 10

class RegisterControl
{
public:
    RegisterControl()
    {
        for (unsigned int i = 0; i < SIZE_FLAGS; i++)
        {
            flags[i] = false;
        }
    }
    int getNext();
    void freePlace(int);

    bool flags[SIZE_FLAGS];
};
#endif
