#pragma once
#include <hwlib.hpp>

class joystick_value_c {
public:
    int x;
    int y;

    bool operator!=(const joystick_value_c &rhs) {
        return ((this->x != rhs.x) || (this->y != rhs.y));
    }
    
    joystick_value_c operator-(const joystick_value_c &rhs) {
        return {this->x - rhs.x, this->y - rhs.y};
    }
    
    joystick_value_c operator-(const int &rhs) {
        return {this->x - rhs, this->y - rhs};
    }
    
    joystick_value_c operator+(const joystick_value_c &rhs) {
        return {this->x + rhs.x, this->y + rhs.y};
    }
    
    joystick_value_c operator+(const int &rhs) {
        return {this->x + rhs, this->y + rhs};
    }
    
    bool operator>=(const int &rhs) {
        return (this->x >= rhs || this->y >= rhs);
    }
    
    bool operator>(const joystick_value_c &rhs) {
        return (this->x > rhs.x || this->y > rhs.y);
    }
    
    bool operator<(const joystick_value_c &rhs) {
        return (this->x < rhs.x || this->y < rhs.y);
    }
    
    bool operator<=(const int &rhs) {
        return (this->x <= rhs || this->y <= rhs);
    }
};