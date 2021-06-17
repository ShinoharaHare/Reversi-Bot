#include <iostream>

#include "Reversi/Reversi.h"
#include "MinimaxPruningAgent.h"
#include "RandomAgent.h"
#include "heuristic.h"

using namespace std;

void test(Agent *a, Agent *b, uint16_t n_games, bool verbose) {
    float winrate = Reversi::compete(a, b, n_games, verbose);
    printf("Win rate of %s: %f\n", a->get_name(), winrate);
    printf("Win rate of %s: %f\n", b->get_name(), 1.0 - winrate);
}

int main(int argc, char *argv[]) {
    MinimaxPruningAgent a1;
    MinimaxPruningAgent a2;
    RandomAgent a3, a4;

    a3.set_name("佛系Agent1");
    a4.set_name("佛系Agent2");

    a1.set_heuristic(Heuristic::bind_pmec(0.1, 0.1, 0.2, 0.6));
    a2.set_heuristic(Heuristic::bind_pmec(0.1, 0.1, 0.1, 0.7));
    a1.set_name("Agent1");
    a2.set_name("Agent2");
    a1.set_depth(6);
    a2.set_depth(6);

    test(&a1, &a2, 100, true);

    return 0;
}
