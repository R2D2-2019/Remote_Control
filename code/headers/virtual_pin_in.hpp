#pragma once

#include <hwlib.hpp>

class virtual_pin_in_c: public hwlib::pin_in {
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
    virtual_pin_in_c(const virtual_pin_in_c &copy);
    virtual_pin_in_c(uint16_t& target, buttons position, hwlib::port_in* port);
    
    bool read() override;
    void refresh() override;
private:
    uint16_t* target;
    buttons position;
    hwlib::port_in* const port;
};