#include <steering_wheel_controller.hpp>

r2d2::manual_control::steering_wheel_controller_c::steering_wheel_controller_c(
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

bool r2d2::manual_control::steering_wheel_controller_c::read() {
    this->refresh();

    return false;
}

uint8_t r2d2::manual_control::steering_wheel_controller_c::get_slider(hwlib::target::pin_adc &slider){
    if( (slider.read()/16) > 0){
        return slider.read()/16;
    }
    
    return slider.read();
}

int r2d2::manual_control::steering_wheel_controller_c::get_button(hwlib::pin_in &button){
    return button.read();
}

void r2d2::manual_control::steering_wheel_controller_c::print() {
    hwlib::cout << "B1: " << button1.read() << "| B2: " << button2.read()
                << "| B3: " << button3.read() << "| B4: " << button4.read()
                << "| \n";
    hwlib::cout << "wheel: " << wheel.read()/16 << " | pedals: " << pedals.read()/16
                << "\n";
}