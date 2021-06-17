#include "GameBoard.h"
#include "utils.h"

GameBoard::GameBoard() {
    reset();
}

GameBoard::GameBoard(const char *state) {
    operator=(state);
}

void GameBoard::reset() {
    for (uint8_t i = 0; i < 36; i++) {
        _data[i] = Symbol::Empty;
    }

    _data[14] = Symbol::Light;
    _data[15] = Symbol::Dark;
    _data[20] = Symbol::Dark;
    _data[21] = Symbol::Light;
}

const char *GameBoard::get_data() const {
    return _data;
}

uint8_t GameBoard::count_flipable_pieces(Color color, const Position &pos, Direction dir) const {
    auto symbols = get_color_symbols(color);
    bool valid = false;
    uint8_t count = 0;
    Position p = pos;
    do {
        p.move(dir);
        if (!p.is_valid()) {
            break;
        }
        char piece = _data[p.get_index()];
        if (piece == symbols[1]) {
            count++;
        } else if (piece == symbols[0]) {
            valid = true;
            break;
        } else if (piece == Symbol::Empty) {
            break;
        }
    } while (pos.is_valid());

    return valid ? count : 0;
}

std::vector<Position> GameBoard::get_moves(Color color) const {
    std::vector<Position> v;
    for (uint8_t i = 0; i < 36; i++) {
        if (is_valid_move(color, i)) {
            v.push_back(i);
        }
    }
    return v;
}

uint8_t GameBoard::count_pieces(Color color) const {
    const char *symbols = get_color_symbols(color);
    uint8_t count = 0;
    for (uint8_t i = 0; i < 36; i++) {
        if (_data[i] == symbols[0]) {
            count++;
        }
    }
    return count;
}

uint8_t GameBoard::count_corner(Color color) const {
    static uint8_t corners[] = {0, 5, 30, 35};

    const char *symbols = get_color_symbols(color);
    uint8_t count = 0;
    for (uint8_t i = 0; i < 4; i++) {
        if (_data[corners[i]] == symbols[0]) {
            count++;
        }
    }
    return count;
}

uint8_t GameBoard::count_edge(Color color) const {
    const char *symbols = get_color_symbols(color);
    uint8_t count = 0;

    // 上
    for (uint8_t i = 0; i < 6; i++) {
        if (_data[i] == symbols[0]) {
            count++;
        }
    }
    // 下
    for (uint8_t i = 30; i < 36; i++) {
        if (_data[i] == symbols[0]) {
            count++;
        }
    }
    // 左
    for (uint8_t i = 6; i <= 24; i += 6) {
        if (_data[i] == symbols[0]) {
            count++;
        }
    }
    // 右
    for (uint8_t i = 11; i <= 29; i++) {
        if (_data[i] == symbols[0]) {
            count++;
        }
    }

    return count;
}

uint8_t GameBoard::count_stable(Color color) const {
    static uint8_t corners[] = {0, 5, 30, 35};
    static Direction valid_dirs[] = {Right, Down, Up, Left};

    const char *symbols = get_color_symbols(color);
    bool mask[36] = {false};
    uint8_t count = 0;

    for (uint8_t i = 0; i < 4; i++) {
        if (_data[corners[i]] == symbols[0]) {
            for (uint8_t j = 0; j < 3; j++) {
                Direction d = static_cast<Direction>((valid_dirs[i] + j) % 8);
                Position p = corners[i];
                while (p.is_valid()) {
                    if (_data[p.get_index()] == symbols[0]) {
                        // mask[p.get_index()] = true;
                        count++;
                    } else {
                        break;
                    }
                    p.move(d);
                }
            }

        }
    }

    for (uint8_t i = 0; i < 36; i++) {
        count += mask[i];
    }

    return count;
}



GameBoard &GameBoard::flip_pieces(Color color, const Position &pos) {
    const char *symbols = get_color_symbols(color);
    for (uint8_t d = 0; d <= 7; d++) {
        Direction dir = static_cast<Direction>(d);
        uint8_t count = count_flipable_pieces(color, pos, dir);
        Position p = pos;
        for (uint8_t i = 0; i <= count; i++) {
            operator[](p) = symbols[0];
            p.move(dir);
        }
    }
    return *this;
}

GameBoard GameBoard::flip_pieces(Color color, const Position &pos) const {
    GameBoard board = *this;
    board.flip_pieces(color, pos);
    return board;
}


bool GameBoard::is_valid_move(Color color, const Position &pos) const {
    if (operator[](pos) != Symbol::Empty) {
        return false;
    }
    for (uint8_t i = 0; i < 8; i++) {
        Direction d = (Direction)i;
        auto c = count_flipable_pieces(color, pos, d);
        if (c > 0) {
            return true;
        }
    }
    return false;
}

bool GameBoard::has_valid_move(Color color) const {
    for (uint8_t i = 0; i < 36; i++) {
        if (is_valid_move(color, i)) {
            return true;
        }
    }
    return false;
}

uint8_t GameBoard::num_valid_moves(Color color) const {
    uint8_t count = 0;
    for (uint8_t i = 0; i < 36; i++) {
        count += is_valid_move(color, i);
    }
    return count;
}

bool GameBoard::is_over() const {
    return !has_valid_move(Dark) && !has_valid_move(Light);
}

char &GameBoard::operator[](const Position &pos) {
    return _data[pos.get_index()];
}

char GameBoard::operator[](const Position &pos) const {
    return _data[pos.get_index()];
}

GameBoard &GameBoard::operator=(const char *state) {
    for (uint8_t i = 0; i < 36; i++) {
        _data[i] = state[i];
    }
    return *this;
}

// std::istream &operator>>(std::istream &is, GameBoard &gb) {
//     char state[36];
//     is >> state;
//     gb.set_state(state);
// }

std::ostream &operator<<(std::ostream &os, const GameBoard &gb) {
    auto state = gb.get_data();

    os << "  ";
    for (int i = 0; i < 6; i++) {
        os << char('a' + i);
    }
    os << std::endl << std::endl;
    for (int r = 0; r < 6; r++) {
        os << char('A' + r) << ' ';
        for (int c = 0; c < 6; c++) {
            os << state[r * 6 + c];
        }
        os << std::endl;
    }

    return os;
}
