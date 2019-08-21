#include <ps2_mat.hpp>

ps2_mat_c::ps2_mat_c(ps2_bus_c &ps2_bus):
    ps2_bus(ps2_bus)
    {}

std::array<uint8_t, 8> ps2_mat_c::read_mat(){
    std::array<uint8_t, 8> data = ps2_bus.read_write(poll_command, 8);
    return data;
}