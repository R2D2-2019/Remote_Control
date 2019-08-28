#pragma once

#include <hwlib.hpp>
#include <ps2_bus.hpp>
#include <array>
/*
*Struct that contains the states of all buttons.
*/
struct button_states_s {
    bool l1 = 0;
    bool l2 = 0;
    bool r1 = 0;
    bool r2 = 0;
    bool start = 0;
    bool select = 0;
    bool square = 0;
    bool cross = 0;
    bool triangle = 0;
    bool circle = 0;
    bool up = 0;
    bool down = 0;
    bool left = 0;
    bool right = 0;
};
/*
*   This class is the ps2_controller interface that uses the ps2 bus for sending and receiving data.
*   Right now it only works for digital buttons.
*/
    class ps2_controller_c{
    private:
/*
*   The ps2 bus used for communicating with the ps2 controller.
*/
        ps2_bus_c &ps2_bus;
/*
*   Method used to get the raw data button data from the controller.
*/
        std::array<uint8_t, 8> read_raw();
/*
*   All masks used to check if a certain button is pressed.
*/
        //button masks
        //byte 1
        uint8_t start_mask = 8;
        uint8_t select_mask = 127;
        uint8_t up_mask = 16;
        uint8_t down_mask = 64;
        uint8_t left_mask = 128;
        uint8_t right_mask = 32;

        //byte 2
        uint8_t l1_mask = 4;
        uint8_t l2_mask = 1;
        uint8_t r1_mask = 8;
        uint8_t r2_mask = 2;
        uint8_t square_mask = 128;
        uint8_t cross_mask = 64;
        uint8_t triangle_mask = 16;
        uint8_t circle_mask = 32;

    public:
/*
*   Constructor.
*   @param ps2_bus is the bus used to communicate with the ps2 controller.
*/
        ps2_controller_c(ps2_bus_c &ps2_bus);
/*
*   Commands used for interfacing with the ps2_controller
*/
        //commands
        const uint8_t poll_command[8] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
/*
*   Method to get more usable data from the buttons pressed.
*   Returns true or false for every button.
*/
        button_states_s get_button_states();
    };