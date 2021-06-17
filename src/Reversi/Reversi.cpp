#include "Reversi.h"
#include "utils.h"

#include <iostream>

float Reversi::compete(Agent *a1, Agent *a2, uint16_t n_games, bool verbose) {
    Board board;
    float total = n_games;
    float a1_wins = 0;
    bool passed = false;
    for (uint16_t g = 1; g <= n_games; g++) {
        board.reset();
        passed = false;
        for (uint8_t turn = 0; ; turn++) {
            if (board.has_valid_move(Dark)) {
                passed = false;
                Position move = a1->next_move(board, Dark);
                board.flip_pieces(Dark, move);
            } else if (passed) {
                break;
            } else {
                passed = true;
            }

            if (board.has_valid_move(Light)) {
                passed = false;
                Position move = a2->next_move(board, Light);
                board.flip_pieces(Light, move);
            } else if (passed) {
                break;
            } else {
                passed = true;
            }
        }

        int result = board.count_pieces(Dark) - board.count_pieces(Light);
        if (result > 0) {
            a1_wins++;
            if (verbose) {
                // std::cout << board << std::endl;
                printf("[第%u場] %s 獲勝\n", g, a1->get_name());
            }
        } else if (result == 0) {
            total--;
            if (verbose) {
                // std::cout << board << std::endl;
                printf("[第%u場] 平手\n", g);
            }
        } else {
            if (verbose) {
                // std::cout << board << std::endl;
                printf("[第%u場] %s 獲勝\n", g, a2->get_name());
            }
        }
    }

    return a1_wins / total;
}
