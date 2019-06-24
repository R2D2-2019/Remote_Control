#include <dummy_controller.hpp>
#include <hwlib.hpp>


int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    hwlib::cout << "this works via arduino";
    hwlib::wait_ms(1000);
    auto test = r2d2::manual_control::dummy_controller_c();
}