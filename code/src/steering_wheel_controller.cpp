#include <steering_wheel_controller.hpp>

r2d2::manual_control::steering_wheel_controller_c::steering_wheel_controller_c(
    hwlib::target::pin_in &button1, hwlib::target::pin_in &button2,
    hwlib::target::pin_in &button3, hwlib::target::pin_in &button4,
    hwlib::target::pin_adc &wheel, hwlib::target::pin_adc &pedals)
    : buttons{&button1, &button2, &button3, &button4},
      sliders{&wheel, &pedals} {
}

bool r2d2::manual_control::steering_wheel_controller_c::read() {
    this->refresh();

    return false;
}

int8_t r2d2::manual_control::steering_wheel_controller_c::get_slider(
    const int &slider) {
    if (slider == 0) {
        int wheel_degrees = sliders[0]->read();

        // 266 is min range wheel, 3870 is max range wheel. Gives output between
        // 90 and -90. plus two is adjusting range (came up while testing)
        wheel_degrees = ((wheel_degrees - 266) * 180 / (3870 - 266) - 90) + 2;
        if (wheel_degrees < 5 && wheel_degrees > -5) {
            return 0;
        } else if (wheel_degrees > 90) {
            return 90;
        } else if (wheel_degrees < -90) {
            return -90;
        } else {
            return wheel_degrees;
        }
    } else {
        int pedal_percentage = sliders[1]->read();

        // 254 is min range pedal, 4051 is max range pedal. Gives output between
        // 100 and -100.
        pedal_percentage =
            ((pedal_percentage - 264) * 200 / (4051 - 264) - 100);

        if (pedal_percentage > -13 && pedal_percentage < 13) {
            return 0;
        } else if (pedal_percentage > 100) {
            return 100;
        } else if (pedal_percentage < -100) {
            return -100;
        } else {
            return pedal_percentage;
        }
    }
}

bool r2d2::manual_control::steering_wheel_controller_c::get_button(
    const int &button) {
    return !buttons[button]->read();
}

void r2d2::manual_control::steering_wheel_controller_c::print() {
    hwlib::cout << "B1: " << get_button(0) << "| B2: " << get_button(1)
                << "| B3: " << get_button(2) << "| B4: " << get_button(3)
                << "\n";

    hwlib::cout << "wheel: " << get_slider(0) << " | pedals: " << get_slider(1)
                << "\n";
}