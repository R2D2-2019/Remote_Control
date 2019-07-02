#include <controller_interface.hpp>
#include <serial_controller.hpp>
#include <hwlib.hpp>

bool r2d2::manual_control::serial_controller_c::get_button(r2d2::manual_control::buttons button){
    refresh();

    return false;
};

unsigned char r2d2::manual_control::serial_controller_c::get_slider(r2d2::manual_control::sliders slider){
    refresh();

    return 80;
};

joystick_value_s r2d2::manual_control::serial_controller_c::get_joystick(r2d2::manual_control::joysticks joystick){
    refresh();

    return {0,0};
};

void r2d2::manual_control::serial_controller_c::refresh(){

    hwlib::string<10> buffer;
    int buffer_size = 0;

    while(hwlib::cin.char_available()){
        buffer += hwlib::cin.getc();
        buffer_size += 1;
        hwlib::wait_ms(10);
    }

    if(buffer.length()){
        hwlib::cout << buffer_size << hwlib::endl;
    }

};