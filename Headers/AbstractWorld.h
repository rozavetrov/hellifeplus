#ifndef ABSTRACT_WORLD_H
#define ABSTRACT_WORLD_H

#include <vector>

// Interface to interact with graphic widget
class AbstractWorld 
{
public:
    virtual void initializeState(int) = 0;
    virtual void updateState() = 0;
    virtual bool** getCurrentState() = 0;
    virtual void setRule(bool**) = 0;

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
};

#endif