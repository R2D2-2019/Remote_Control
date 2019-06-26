#pragma once
#include <hwlib.hpp>

class joystick_value_c {
public:
    int x;
    int y;

    bool operator!=(const joystick_value_c &rhs) {
        return ((this->x != rhs.x) || (this->y != rhs.y));
    }
};