#pragma once

#include <string>
#include <stdint.h>
#include "enum.h"

class Position {
public:
    Position() = default;
    Position(const char *pos);
    Position(uint8_t index);
    Position(std::initializer_list<uint8_t> idx2d);

    void set(uint8_t row, uint8_t col);
    void move(Direction dir, uint8_t step = 1);
    bool is_valid() const;
    uint8_t get_index() const;
    std::string get_text() const;

    Position &operator=(const Position &pos);
    Position &operator=(const char *pos);
    Position &operator=(uint8_t index);
    Position &operator=(std::initializer_list<uint8_t> idx2d);

private:
    uint8_t _row = 0;
    uint8_t _col = 0;
};
