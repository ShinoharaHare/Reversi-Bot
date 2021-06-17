#pragma once

#include <string>
#include "GameBoard.h"

class Agent
{
public:
    Agent() = default;

    void set_name(const char *name);
    const char *get_name() const;

    virtual Position next_move(const GameBoard &board, Color color) = 0;
    
protected:
    std::string _name;
};
