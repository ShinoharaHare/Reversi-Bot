#pragma once

#include <iostream>
#include <vector>

#include "Position.h"

class GameBoard
{
public:
    GameBoard();
    GameBoard(const char *state);

    const char *get_data() const;

    void reset();

    uint8_t count_flipable_pieces(Color color, const Position &pos, Direction dir) const;
    GameBoard &flip_pieces(Color color, const Position &pos);
    GameBoard flip_pieces(Color color, const Position &pos) const;

    uint8_t count_corner(Color color) const;
    uint8_t count_pieces(Color color) const;
    uint8_t count_edge(Color color) const;
    uint8_t count_stable(Color color) const;

    bool is_valid_move(Color color, const Position &pos) const;
    bool has_valid_move(Color color) const;
    uint8_t num_valid_moves(Color color) const;

    std::vector<Position> get_moves(Color color) const;

    bool is_over() const;

    char &operator[](const Position &pos);
    char operator[](const Position &pos) const;
    GameBoard &operator=(const char *state);

private:
    char _data[36];
};


// std::istream &operator>>(std::istream &is, GameBoard &gb);
std::ostream &operator<<(std::ostream &os, const GameBoard &gb);
