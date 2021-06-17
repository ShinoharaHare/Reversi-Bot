#include "MinimaxPruningAgent.h"

#include <random>

static const double infinity = std::numeric_limits<double>::infinity();
static std::random_device rd;
static std::default_random_engine gen = std::default_random_engine(rd());
static std::uniform_int_distribution<int> dis(0, 1);

Result MinimaxPruningAgent::alphabeta_impl(const Board &board, Color color, uint8_t depth, double alpha, double beta, bool max_node) const {
    if (depth == 0) {
        return {-1, _heuristic(board, color)};
    }
    Color cc = max_node ? color : get_opponent_color(color);
    auto moves = board.get_moves(cc);
    if (moves.empty()) {
        if (board.get_moves(get_opponent_color(cc)).empty()) {
            return {-1, _heuristic(board, color)};
        }
        return alphabeta_impl(board, color, depth, alpha, beta, !max_node);
    }

    Result result;
    result.score = max_node ? -infinity : infinity;
    for (auto p : moves) {
        Board b = board.flip_pieces(cc, p);
        Result r = alphabeta_impl(b, color, depth - 1, alpha, beta, !max_node);

        bool better = max_node ? r.score > result.score : r.score < result.score;
        bool random = _randomized && dis(gen) && r.score == result.score;

        if (better || random) {
            result.score = r.score;
            result.position = p;
        }

        alpha = max_node ? std::max(alpha, result.score) : alpha;
        beta = max_node ? beta : std::min(beta, result.score);

        if (beta <= alpha) {
            break;
        }
    }

    return result;
}

Position MinimaxPruningAgent::alphabeta(const Board &board, Color color, uint8_t depth) const {
    Result r = alphabeta_impl(board, color, depth, -infinity, infinity);
    return r.position;
}

Position MinimaxPruningAgent::next_move(const Board &board, Color color) {
    return alphabeta(board, color, _depth);
}

void MinimaxPruningAgent::set_heuristic(Heuristic heuristic) {
    _heuristic = heuristic;
}

void MinimaxPruningAgent::set_depth(uint8_t depth) {
    _depth = depth;
}

void MinimaxPruningAgent::set_randomized(bool rand) {
    _randomized = rand;
}
