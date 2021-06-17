#pragma once

#include "Reversi/Board.h"
#include "Reversi/utils.h"

#include <functional>

#define CALC(a, b, w) ((w) == 0 || ((a) + (b)) == 0) ? 0 : ((w) * double((a) - (b)) / double((a) + (b)))

namespace Heuristic {
using Heuristic = std::function<double(const Board &, Color)>;

static Heuristic bind_pmec(double wp, double wm, double we, double wc) {
    auto pmec = [=](const Board &board, Color color) {
        Color c1 = color;
        Color c2 = get_opponent_color(c1);
        double sp = CALC(board.count_pieces(c1), board.count_pieces(c2), wp);
        double sm = CALC(board.num_valid_moves(c1), board.num_valid_moves(c2), wm);
        double se = CALC(board.count_edge(c1), board.count_edge(c2), we);
        double sc = CALC(board.count_corner(c1), board.count_corner(c2), wc);
        return sp + sm + se + sc;
    };
    return pmec;
}
}
