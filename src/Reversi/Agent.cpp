#include "Agent.h"

const char *Agent::get_name() const {
    return _name.c_str();
}

void Agent::set_name(const char *name) {
    _name = name;
}
