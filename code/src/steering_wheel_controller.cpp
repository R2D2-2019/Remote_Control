#include <steering_wheel_controller.hpp>

steering_wheel_controller_c::steering_wheel_controller_c(
    hwlib::target::pin_adc &wheel, hwlib::target::pin_adc &pedals,
    hwlib::pin_in &button1, hwlib::pin_in &button2, hwlib::pin_in &button3,
    hwlib::pin_in &button4)
    : wheel(wheel),
      pedals(pedals),
      button1(button1),
      button2(button2),
      button3(button3),
      button4(button4) {
}

bool steering_wheel_controller_c::read() {
    this->refresh();
    return false;
}

void steering_wheel_controller_c::print() {
    hwlib::cout << "B1: " << button1.read() << "| B2: " << button2.read()
                << "| B3: " << button3.read() << "| B4: " << button4.read()
                << "| \n";
    hwlib::cout << "wheel: " << wheel.read() << " | pedals: " << pedals.read()
                << "\n";
}