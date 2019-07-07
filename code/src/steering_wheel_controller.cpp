#include <steering_wheel_controller.hpp>

r2d2::manual_control::steering_wheel_controller_c::steering_wheel_controller_c(
    hwlib::target::pin_in &button1, hwlib::target::pin_in &button2,
    hwlib::target::pin_in &button3, hwlib::target::pin_in &button4,
    hwlib::target::pin_adc &wheel, hwlib::target::pin_adc &pedals
    
): 
    manual_control_c(4, 0, 0, 1, 0, 1, 1),
    buttons{&button1, &button2, &button3, &button4},
    sliders{&wheel, &pedals}
{}

int8_t r2d2::manual_control::steering_wheel_controller_c::get_slider(
    const int &slider) {
    if (slider == 0) {
        int wheel_degrees = sliders[0]->read();

        wheel_degrees = ((wheel_degrees - 320) * 180 / (4030 - 320) - 90);
        if (wheel_degrees < 15 && wheel_degrees > -15) {
            return 0;
        } else if (wheel_degrees > 90) {
            return 100;
        } else if (wheel_degrees < -90) {
            return -100;
        } else {
            return wheel_degrees;
        }
    } else {
        int pedal_percentage = sliders[1]->read();

        pedal_percentage =
            ((pedal_percentage - 340) * 200 / (4030 - 340) - 110);

        if(pedal_percentage > -5 && pedal_percentage < 5){
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
    hwlib::cout << "B1: " << buttons[0]->read()
                << "| B2: " << buttons[1]->read()
                << "| B3: " << buttons[2]->read()
                << "| B4: " << buttons[3]->read() << "| \n";

    hwlib::cout << "wheel: " << get_slider(0) << " | pedals: " << get_slider(1)
                << "\n";
}

r2d2::manual_control::state_s r2d2::manual_control::steering_wheel_controller_c::get_state(){
    set_button(0, !buttons[0]->read());
    set_button(1, !buttons[1]->read());
    set_button(2, !buttons[2]->read());
    set_button(3, !buttons[3]->read());

    float wheel_axes = get_slider(0);
    if(wheel_axes > 0){
        wheel_axes /= 80;
        wheel_axes *= -127;
        if(wheel_axes < -127){
            wheel_axes = -127;
        }

    } else if(wheel_axes < 0) {
        wheel_axes /= 100;
        wheel_axes *= -127;
        if(wheel_axes > 127){
            wheel_axes = 127;
        }
    }
    set_axes_lx(wheel_axes);

    float thrust = get_slider(1);
    if(thrust > 0){
        thrust = (float(get_slider(1))/91.0)*127; //convert to 0-127 range
        if(thrust > 127  || thrust < 0){
            thrust = 127;
        }
        set_axes_rx(int8_t(thrust));
        set_axes_ry(0);

    } else if(thrust < 0){
        thrust = (float(get_slider(1) * -1)/100.0)*127; //convert to 0-127 range
        if(thrust > 127 || thrust < 0){
            thrust = 127;
        }
        set_axes_rx(0);
        set_axes_ry(int8_t(thrust));
    } else {
        set_axes_rx(0);
        set_axes_ry(0);
    }
    return m_state;
    
}