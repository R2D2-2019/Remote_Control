#pragma once

#include <hwlib.hpp>
#include "PS2_bus.hpp"
class PS2_controller_c{
private:
    PS2_bus_c &ps2_bus,
    uint_fast16_t buffer;
    uint_fast8_t  hwlib_buffer;
    std::array<uint8_t, 21> default_buffer;
    bool analog_mode;
    bool config_mode;
    bool controller_locked;

public:
    PS2_controller_c::PS2_controller_c(Ps2Bus& bus);
};