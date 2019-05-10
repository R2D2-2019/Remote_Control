#include "hwlib.hpp"
#include "steering_wheel_controller.hpp"
//#include <comm.hpp>

namespace target = hwlib::target;

int main(void) {

    using namespace r2d2;

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(10);

   // r2d2::comm_c comm;

    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d2);
    auto button2 = hwlib::target::pin_in(hwlib::target::pins::d3);
    auto button3 = hwlib::target::pin_in(hwlib::target::pins::d4);
    auto button4 = hwlib::target::pin_in(hwlib::target::pins::d5);
    auto wheel = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
    auto pedals = hwlib::target::pin_adc(hwlib::target::ad_pins::a1);

    manual_control::steering_wheel_controller_c steering_wheel_controller(
        wheel, pedals, button1, button2, button3, button4);

    while (true) {
        hwlib::wait_ms(500);
        steering_wheel_controller.print();
    }

    return 0;
}