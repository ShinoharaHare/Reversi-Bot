#pragma once

#include "Reversi/GameBoard.h"
#include "Reversi/utils.h"

namespace Heuristic {
static double naive(const GameBoard &board, Color color) {
    Color c1 = color;
    Color c2 = get_opponent_color(c1);
    return board.count_pieces(c1) - board.count_pieces(c2);
}

static double calculate(double a, double b) {
    double sum = a + b;
    return sum == 0 ? 0 : (a - b) / sum;
}

static double mc(const GameBoard &board, Color color) {
    Color c1 = color;
    Color c2 = get_opponent_color(c1);

    double mobility = calculate(board.num_valid_moves(c1), board.num_valid_moves(c2));
    double corner = calculate(board.count_corner(c1), board.count_corner(c2));

    return 0.3 * mobility + 0.7 * corner;
}

static double pmc(const GameBoard &board, Color color) {
    Color c1 = color;
    Color c2 = get_opponent_color(c1);

    double pieces = calculate(board.count_pieces(c1), board.count_pieces(c2));
    double mobility = calculate(board.num_valid_moves(c1), board.num_valid_moves(c2));
    double corner = calculate(board.count_corner(c1), board.count_corner(c2));

    return 0.15 * pieces + 0.15 * mobility + 0.7 * corner;
}

static double pmce(const GameBoard &board, Color color) {
    Color c1 = color;
    Color c2 = get_opponent_color(c1);

    double pieces = calculate(board.count_pieces(c1), board.count_pieces(c2));
    double mobility = calculate(board.num_valid_moves(c1), board.num_valid_moves(c2));
    double corner = calculate(board.count_corner(c1), board.count_corner(c2));
    double edge = calculate(board.count_edge(c1), board.count_edge(c2));

    return 0.1 * pieces + 0.1 * mobility + 0.1 * edge + 0.7 * corner;
}

static double pmces(const GameBoard &board, Color color) {
    Color c1 = color;
    Color c2 = get_opponent_color(c1);

    double pieces = calculate(board.count_pieces(c1), board.count_pieces(c2));
    double mobility = calculate(board.num_valid_moves(c1), board.num_valid_moves(c2));
    double corner = calculate(board.count_corner(c1), board.count_corner(c2));
    double edge = calculate(board.count_edge(c1), board.count_edge(c2));
    double stable = calculate(board.count_stable(c1), board.count_stable(c2));

    return 0.1 * pieces + 0.1 * mobility + 0.1 * edge + 0.1 * stable + 0.6 * corner;
}

}
