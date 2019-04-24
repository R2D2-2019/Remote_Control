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

    while(true){

    }
    return 0;
}