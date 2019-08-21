#pragma once

#include <hwlib.hpp>
#include <array>

class ps2_bus_c {
private:
    hwlib::pin_out &attention;
    hwlib::pin_out &clock;
    hwlib::pin_in &data;
    hwlib::pin_out &command;
    hwlib::pin_in &acknowledge;

    void wait_half_period(){
      hwlib::wait_us( 5 );      
    };

public:
    ps2_bus_c(
        hwlib::pin_out &attention,
        hwlib::pin_out &clock,
        hwlib::pin_in &data,
        hwlib::pin_out &command,
        hwlib::pin_in &acknowledge);

    std::array<uint8_t, 8> read_write(const uint8_t command[], uint8_t n);
};