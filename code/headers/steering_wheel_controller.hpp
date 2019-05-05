#pragma once

#include <hwlib.hpp>

/**
 * \brief
 * This class is for reading the data from the steering wheel
 */

class steering_wheel_controller_c : public hwlib::pin_in {
private:
    hwlib::target::pin_adc &wheel;
    hwlib::target::pin_adc &pedals;
    hwlib::pin_in &button1;
    hwlib::pin_in &button2;
    hwlib::pin_in &button3;
    hwlib::pin_in &button4;

public:
    steering_wheel_controller_c(hwlib::target::pin_adc &wheel,
                                hwlib::target::pin_adc &pedals,
                                hwlib::pin_in &button1, hwlib::pin_in &button2,
                                hwlib::pin_in &button3, hwlib::pin_in &button4);

    /**
     * Refreshes the data of the read buffer and reads the data.
     */
    bool read() override;

    /**
     * Reads and prints the recieved data from the steering wheel.
     */
    void print();
};