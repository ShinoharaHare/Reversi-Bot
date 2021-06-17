#include "utils.h"

const char *get_color_symbols(Color color) {
    static const char *XO = "XO";
    static const char *OX = "OX";

    switch (color) {
    case Color::Dark:
        return XO;
    case Color::Light:
        return OX;
    default:
        return XO;
    }
}

Color get_opponent_color(Color color) {
    return color == Dark ? Light : Dark;
}
