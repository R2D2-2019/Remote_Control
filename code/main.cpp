//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <hwlib.hpp>
#include "PS2_bus.hpp"
#include "PS2_controller.hpp"
#include "virtual_pin_in.hpp"
#include <array>

typedef hwlib::target::pins duepin ;
namespace target = hwlib::target;

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    auto ss = hwlib::target::pin_out(duepin::d7);
    auto sclk = hwlib::target::pin_out(duepin::d4);
    auto miso = hwlib::target::pin_in(duepin::d12);
    miso.pullup_enable();
    auto mosi = hwlib::target::pin_out(duepin::d2);
    auto ack = target::pin_in(duepin::d25);
    
    PS2_bus_c ps2_bus(ss, sclk, miso, mosi, ack);
    PS2_controller_c ps2_controller(ps2_bus, ss);
    ps2_controller.init();

    std::array<uint16_t, 2> left = ps2_controller.get_joystick(0);
    std::array<uint16_t, 2> right = ps2_controller.get_joystick(1);
    hwlib::cout << ps2_controller.in_analog() << " " << ps2_controller.is_locked() << " " << ps2_controller.in_config() << '\n'; 
    hwlib::cout << "LEFT: " <<left[0] << " " << left[1] << '\n';
    hwlib::cout << "RIGHT: " <<right[0] << " " << right[1] << '\n';
    while(true){
        ps2_controller.init();
        left = ps2_controller.get_joystick(0);
        right = ps2_controller.get_joystick(1);
        hwlib::cout << "LEFT: " <<left[0] << " " << left[1] << '\n';
        hwlib::cout << "RIGHT: " <<right[0] << " " << right[1] << '\n';
    }
    return 0;
}