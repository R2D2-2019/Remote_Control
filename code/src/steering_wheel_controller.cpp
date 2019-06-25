#include "../headers/steering_wheel_controller.hpp"

r2d2::manual_control::steering_wheel_controller_c::steering_wheel_controller_c( hwlib::target::pin_in &button1, hwlib::target::pin_in &button2, hwlib::target::pin_in &button3, hwlib::target::pin_in &button4, hwlib::target::pin_adc &steering_wheel, hwlib::target::pin_adc &pedals)
        : button1(button1), button2(button2), button3(button3), button4(button4), steering_wheel(steering_wheel), pedals(pedals) {

    }

bool r2d2::manual_control::steering_wheel_controller_c::read() {
    this->refresh();

    return false;
}

unsigned char r2d2::manual_control::steering_wheel_controller_c::get_slider(sliders slider){
    switch (slider){
        case sliders::slider_l:
            if(get_pedals() > 0){
                return 0;
            }else{
                return get_pedals();
            }
        case sliders::slider_r:
            if(get_pedals() < 0){
                return 0;
            }else{
                return get_pedals();
            }
        default:
            return 0;
    }
}

bool r2d2::manual_control::steering_wheel_controller_c::get_button(buttons button){
    switch (button) {
        case buttons::button_a:
            return button1.read();
        case buttons::button_b:
            return button2.read();
        case buttons::button_x:
            return button3.read();
        case buttons::button_y:
            return button4.read();
        default:
            return 0;
    }
}

joystick_value_s r2d2::manual_control::steering_wheel_controller_c::get_joystick(joysticks joystick){
    switch (joystick){
        case joysticks::joystick_l:
            return {get_steering_wheel(), 0};
        default:
            return {0, 0};
    }
}

int r2d2::manual_control::steering_wheel_controller_c::get_steering_wheel(){
    // 266 is min range wheel, 3870 is max range wheel. Gives output between
    // 90 and -90. plus two is adjusting range (came up while testing)
    int wheel_degrees = steering_wheel.read();

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
}

int r2d2::manual_control::steering_wheel_controller_c::get_pedals(){
    // 254 is min range pedal, 4051 is max range pedal. Gives output between
    // 100 and -100.
    int pedal_percentage = pedals.read();

    pedal_percentage = ((pedal_percentage - 264) * 200 / (4051 - 264) - 100);
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

void r2d2::manual_control::steering_wheel_controller_c::print() {
//    hwlib::cout << "B1: " << get_button(0) << "| B2: " << get_button(1)
//                << "| B3: " << get_button(2) << "| B4: " << get_button(3)
//                << "\n";
//
//    hwlib::cout << "wheel: " << get_slider(0) << " | pedals: " << get_slider(1)
//                << "\n";
}