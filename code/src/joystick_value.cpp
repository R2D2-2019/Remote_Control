#include <joystick_value.hpp>

bool joystick_value_s::operator!=(const joystick_value_s &rhs) {
    return ((this->x != rhs.x) || (this->y != rhs.y));
}

joystick_value_s joystick_value_s::operator-(const joystick_value_s &rhs) {
    return {this->x - rhs.x, this->y - rhs.y};
}

joystick_value_s joystick_value_s::operator-(const int &rhs) {
    return {this->x - rhs, this->y - rhs};
}

joystick_value_s joystick_value_s::operator+(const joystick_value_s &rhs) {
    return {this->x + rhs.x, this->y + rhs.y};
}

joystick_value_s joystick_value_s::operator+(const int &rhs) {
    return {this->x + rhs, this->y + rhs};
}

bool joystick_value_s::operator>=(const int &rhs) {
    return (this->x >= rhs || this->y >= rhs);
}

bool joystick_value_s::operator>(const joystick_value_s &rhs) {
    return (this->x > rhs.x || this->y > rhs.y);
}

bool joystick_value_s::operator<(const joystick_value_s &rhs) {
    return (this->x < rhs.x || this->y < rhs.y);
}

bool joystick_value_s::operator<=(const int &rhs) {
    return (this->x <= rhs || this->y <= rhs);
}