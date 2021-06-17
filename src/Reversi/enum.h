#pragma once

enum Color {
    Dark = 1,
    Light = 2
};

enum Direction {
    Up,
    UpRight,
    Right,
    DownRight,
    Down,
    DownLeft,
    Left,
    UpLeft
};

namespace Symbol {
const char Empty = '+';
const char Dark = 'X';
const char Light = 'O';
}

enum GameState {
    Win, // Player1
    Loss,
    Draw,
    Running
};
