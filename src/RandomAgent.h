#include "Reversi/Agent.h"

#include <random>

class RandomAgent : public Agent
{
public:
    RandomAgent() {
        _random_engine = std::default_random_engine(_random_device());
    }

    Position next_move(const GameBoard &board, Color color) {
        auto moves = board.get_moves(color);
        std::uniform_int_distribution<> dist(0, moves.size() - 1);
        auto idx = dist(_random_engine);
        return moves[idx];
    }

private:
    std::random_device _random_device;
    std::default_random_engine _random_engine;
};
