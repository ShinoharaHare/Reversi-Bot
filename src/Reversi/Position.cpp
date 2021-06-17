#include "Position.h"

Position::Position(const char *pos) {
    operator=(pos);
}

Position::Position(uint8_t index) {
    operator=(index);
}

Position::Position(std::initializer_list<uint8_t> idx2d) {
    operator=(idx2d);
}

void Position::set(uint8_t row, uint8_t col) {
    _row = row;
    _col = col;
}

void Position::move(Direction dir, uint8_t step) {
    uint8_t off_r;
    uint8_t off_c;
    switch (dir) {
    case Up:
        off_r = -1;
        off_c = 0;
        break;
    case UpRight:
        off_r = -1;
        off_c = 1;
        break;
    case Right:
        off_r = 0;
        off_c = 1;
        break;
    case DownRight:
        off_r = 1;
        off_c = 1;
        break;
    case Down:
        off_r = 1;
        off_c = 0;
        break;
    case DownLeft:
        off_r = 1;
        off_c = -1;
        break;
    case Left:
        off_r = 0;
        off_c = -1;
        break;
    case UpLeft:
        off_r = -1;
        off_c = -1;
        break;
    }
    off_r *= step;
    off_c *= step;
    _row += off_r;
    _col += off_c;
}

bool Position::is_valid() const {
    return _row >= 0 && _row <= 5 && _col >= 0 && _col <= 5;
}

uint8_t Position::get_index() const {
    return _row * 6 + _col;
}

std::string Position::get_text() const {
    std::string s = "Aa";
    s[0] += _row;
    s[1] += _col;
    return s;
}

Position &Position::operator=(const Position &pos) {
    _row = pos._row;
    _col = pos._col;
    return *this;
}

Position &Position::operator=(const char *pos) {
    // if (std::isdigit(pos[0]) && std::isdigit(pos[1])) {
    //     _row = pos[0] - '0';
    //     _col = pos[1] - '0';
    // } else 
    if (std::isalpha(pos[0]) && std::isalpha(pos[1])) {
        _row = pos[0] - 'A';
        _col = pos[1] - 'a';
    }
    return *this;
}

Position &Position::operator=(uint8_t idx) {
    _row = idx / 6;
    _col = idx % 6;
    return *this;
}

Position &Position::operator=(std::initializer_list<uint8_t> idx2d) {
    auto p = idx2d.begin();
    _row = p[0];
    _col = p[1];
    return *this;
}
