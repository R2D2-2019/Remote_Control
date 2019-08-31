#pragma once

#include <hwlib.hpp>
#include <array>

namespace r2d2 {
    /*
    *   Class to interface directly with the ps2 controller
    */
    class ps2_bus_c {
    private:
    /*
    *   Attention pin off the controller.
    */
        hwlib::pin_out &attention;
    /*
    *   clock pin off the controller.
    */
        hwlib::pin_out &clock;
    /*
    *   data pin off the controller.
    */
        hwlib::pin_in &data;
    /*
    *   command pin off the controller.
    */
        hwlib::pin_out &command;
    /*
    *   acknowledge pin off the controller.
    */
        hwlib::pin_in &acknowledge;
    /*
    *   Function to wait half a clock period.
    */
        void wait_half_period();

    public:
    /*
    *   Constructor of the ps2 bus.
    *   @param attention attention pin of the ps2 controller
    *   @param clock clock pin of the ps2 controller
    *   @param data data pin of the ps2 controller
    *   @param command command pin of the ps2 controller
    *   @param acknowledge acknowledge pin of the ps2 controller
    */
        ps2_bus_c(
            hwlib::pin_out &attention,
            hwlib::pin_out &clock,
            hwlib::pin_in &data,
            hwlib::pin_out &command,
            hwlib::pin_in &acknowledge);
    /*
    *   Method used to send a command to the controller and read the data(since ps2 controller is full duplex).
    *   @param command[] The command you want to send to the controller
    *   @param n The length of the command.
    */
        std::array<uint8_t, 8> read_write(const uint8_t command[], uint8_t n);
    };
};