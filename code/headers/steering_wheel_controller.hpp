#pragma once

#include <hwlib.hpp>

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
    bool read() override;
    void print();
};