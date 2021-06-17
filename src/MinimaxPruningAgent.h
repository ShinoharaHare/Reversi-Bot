#pragma once

#include "Reversi/Agent.h"
#include "Reversi/utils.h"

#include <vector>
#include <algorithm>
#include <functional>


struct Result {
    Position position;
    double score;
};

class MinimaxPruningAgent : public Agent {
public:
    using Heuristic = std::function<double(const Board &, Color)>;

    Position next_move(const Board &board, Color color);
    void set_heuristic(Heuristic heuristic);
    void set_depth(uint8_t depth);
    void set_randomized(bool rand);

private:
    uint8_t _depth = 4;
    Heuristic _heuristic;
    bool _randomized = true;

    Result alphabeta_impl(const Board &board, Color color, uint8_t depth, double alpha, double beta, bool max_node = true) const;
    Position alphabeta(const Board &board, Color color, uint8_t depth) const;
};
