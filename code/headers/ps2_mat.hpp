#pragma once

#include <hwlib.hpp>
#include <ps2_bus.hpp>
#include <array>

class ps2_mat_c {
private:
    ps2_bus_c &ps2_bus;

public:
    ps2_mat_c(ps2_bus_c &ps2_bus);

    //commands
    const uint8_t poll_command[8] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    std::array<uint8_t, 8> read_mat();
};