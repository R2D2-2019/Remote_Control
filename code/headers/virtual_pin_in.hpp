#pragma once

#include <iostream>
#include <hwlib.hpp>

class VirtualPinIn: public hwlib::pin_in {
public:   
    enum buttons: uint16_t{
        square = 0,
        cross,
        circle,
        triangle,
        r1,
        l1,
        r2,
        l2,
        left,
        down,
        right,
        up,
        start,
        r3,
        l3,
        select
    };
    VirtualPinIn(const VirtualPinIn &copy);
    VirtualPinIn(uint16_t& target, buttons position, hwlib::port_in* port);
    
    bool read() override;
    void refresh() override;
private:
    uint16_t* _target;
    buttons _position;
    hwlib::port_in* const _port;
};