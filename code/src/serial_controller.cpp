#include <controller_interface.hpp>
#include <serial_controller.hpp>
#include <hwlib.hpp>

using namespace r2d2::manual_control;

bool serial_controller_c::get_button(buttons button){
    refresh();
    bool button_value;

    switch(button){
        case buttons::button_a:
            button_value = buttons_state[0];
            break;
        case buttons::button_b:
            button_value = buttons_state[1];
            break;
        case buttons::button_x:
            button_value = buttons_state[2];
            break;
        case buttons::button_y:
            button_value = buttons_state[3];
            break;
        default:
            button_value = false;
    }

    return button_value;
};

unsigned char serial_controller_c::get_slider(sliders slider){
    refresh();
    unsigned char slider_value;

    switch(slider){
        case sliders::slider_l:
            slider_value = sliders_state[0];
            break;
        case sliders::slider_r:
            slider_value = sliders_state[1];
            break;
    }

    return slider_value;
};

joystick_value_s serial_controller_c::get_joystick(joysticks joystick){
    refresh();
    joystick_value_s joystick_value;

    switch(joystick){
        case joysticks::joystick_l:
            joystick_value = joysticks_state[0];
            break;
        default:
            joystick_value = {0,0};
            break;
    }

    return joystick_value;
};

void serial_controller_c::refresh(){
    char controller_state;

    if(hwlib::cin.char_available()){
        controller_state = hwlib::cin.getc();

        if(controller_state & 1){
            joysticks_state[0].x = -90;
            sliders_state[1] = 20;
        }else{
            joysticks_state[0].x = 0;
            sliders_state[1] = 0;
        }

        if(controller_state & 2){
            joysticks_state[0].x = 90;
            sliders_state[1] = 20;
        }

        sliders_state[1] = (controller_state & 4)? 30 : 0; // Up
        sliders_state[0] = (controller_state & 8)? 30 : 0; //Down
        buttons_state[0] = (controller_state & 16); // Button_A
        buttons_state[1] = (controller_state & 32); // Button_B
        buttons_state[2] = (controller_state & 64); // Button_X
        buttons_state[3] = (controller_state & 128); // Button_Y
    }
};