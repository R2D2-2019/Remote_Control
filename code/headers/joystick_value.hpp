#pragma once
#include <hwlib.hpp>

struct joystick_value_s {
public:
    int x;
    int y;

    bool operator!=(const joystick_value_s &rhs);

    joystick_value_s operator-(const joystick_value_s &rhs);

    joystick_value_s operator-(const int &rhs);

    joystick_value_s operator+(const joystick_value_s &rhs);

    joystick_value_s operator+(const int &rhs);

    bool operator>=(const int &rhs);

    bool operator>(const joystick_value_s &rhs);

    bool operator<(const joystick_value_s &rhs);

    bool operator<=(const int &rhs);
};