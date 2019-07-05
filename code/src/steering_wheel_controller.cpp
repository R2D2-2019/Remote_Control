#include <steering_wheel_controller.hpp>

namespace r2d2::manual_control {

    steering_wheel_controller_c::steering_wheel_controller_c(
        int controller_id, hwlib::pin_in &button1, hwlib::pin_in &button2,
        hwlib::pin_in &button3, hwlib::pin_in &button4,
        hwlib::adc &steering_wheel, hwlib::adc &pedals)
        : controller_interface_c(controller_id),
          button1(button1),
          button2(button2),
          button3(button3),
          button4(button4),
          steering_wheel(steering_wheel),
          pedals(pedals) {
    }

    bool steering_wheel_controller_c::read() {
        this->refresh();

        return false;
    }

    unsigned char steering_wheel_controller_c::get_slider(sliders slider) {
        int pedalsvalue = get_pedals();

        if (slider == sliders::slider_l) {
            if (pedalsvalue > 0) {
                return 0;
            } else {
                return pedalsvalue * -1;
            }
        } else if (slider == sliders::slider_r) {
            if (pedalsvalue < 0) {
                return 0;
            } else {
                return pedalsvalue;
            }
        } else {
            return 0;
        }
    }

    bool steering_wheel_controller_c::get_button(buttons button) {

        switch (button) {
        case buttons::button_a:
            return !button1.read();
        case buttons::button_b:
            return !button2.read();
        case buttons::button_x:
            return !button3.read();
        case buttons::button_y:
            return !button4.read();
        default:
            return 0;
        }
    }

    joystick_value_s
    steering_wheel_controller_c::get_joystick(joysticks joystick) {

        if (joystick == joysticks::joystick_l) {
            return {get_steering_wheel(), 0};
        } else {
            return {0, 0};
        }
    }

    int steering_wheel_controller_c::get_steering_wheel() {
        // Read the steering wheel
        int wheel_degrees = steering_wheel.read();

        // 266 is min range wheel, 3870 is max range wheel. Gives output between
        // 90 and -90. plus two is adjusting range (came up while testing)
        wheel_degrees = ((wheel_degrees - 266) * 180 / (3870 - 266) - 90) + 2;

        // Inverse so the left is negative and the right is positive
        wheel_degrees = -1 * wheel_degrees;

        if (wheel_degrees < 5 && wheel_degrees > -5) {
            return 0;
        } else if (wheel_degrees > 90) {
            return 90;
        } else if (wheel_degrees < -90) {
            return -90;
        } else {
            return wheel_degrees;
        }
    }

    int steering_wheel_controller_c::get_pedals() {
        // Read the pedals
        int pedal_percentage = pedals.read();

        // 254 is min range pedal, 4051 is max range pedal. Gives output between
        // 100 and -100.
        pedal_percentage =
            ((pedal_percentage - 264) * 200 / (4051 - 264) - 100);

        // 15 is deadzone
        if (pedal_percentage > -15 && pedal_percentage < 15) {
            return 0;
        } else if (pedal_percentage > 100) {
            return 100;
        } else if (pedal_percentage < -100) {
            return -100;
        } else {
            return pedal_percentage;
        }
    }
} // namespace r2d2::manual_control