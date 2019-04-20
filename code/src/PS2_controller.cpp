#include "PS2_controller.hpp"

PS2_controller_c::PS2_controller_c(Ps2Bus& ps2_bus): 
    ps2_bus(ps2_bus), 
    buffer(0x00), 
    default_buffer({0}),
    analog_mode(false), 
    config_mode(false), 
    controller_locked(false)
{}