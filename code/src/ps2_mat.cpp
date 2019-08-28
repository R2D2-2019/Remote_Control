#include <ps2_mat.hpp>

r2d2::ps2_controller_c::ps2_controller_c(ps2_bus_c &ps2_bus):
    ps2_bus(ps2_bus)
    {}

std::array<uint8_t, 8> r2d2::ps2_controller_c::read_raw(){
    std::array<uint8_t, 8> data = ps2_bus.read_write(poll_command, 8);
    if(!(data[1] == 65 && data[2] == 90)){
        data.fill(255);
    }
    return data;
}

r2d2::button_states_s r2d2::ps2_controller_c::get_button_states(){
    std::array<uint8_t, 8> raw_data = read_raw();
    r2d2::button_states_s states;
    states.select = ((raw_data[3]&select_mask) == 0);
    states.start = ((raw_data[3]&start_mask) == 0);
    states.up = ((raw_data[3]&up_mask) == 0);
    states.down = ((raw_data[3]&down_mask) == 0);
    states.left = ((raw_data[3]&left_mask) == 0);
    states.right = ((raw_data[3]&right_mask) == 0);

    states.l1 = ((raw_data[4]&l1_mask) == 0);
    states.l2 = ((raw_data[4]&l2_mask) == 0);
    states.r1 = ((raw_data[4]&r1_mask) == 0);
    states.r2 = ((raw_data[4]&r2_mask) == 0);
    states.square = ((raw_data[4]&square_mask) == 0);
    states.cross = ((raw_data[4]&cross_mask) == 0);
    states.triangle = ((raw_data[4]&triangle_mask) == 0);
    states.circle = ((raw_data[4]&circle_mask) == 0);

    return states;
}