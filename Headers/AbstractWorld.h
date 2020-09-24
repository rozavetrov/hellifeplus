#ifndef ABSTRACT_WORLD_H
#define ABSTRACT_WORLD_H

#include <vector>


class AbstractWorld 
{
public:
    virtual void updateState() = 0;
    virtual bool** getCurrentState() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
};

#endif