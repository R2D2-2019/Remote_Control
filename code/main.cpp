#include <hwlib.hpp>
#include <ps2_bus.hpp>
#include <ps2_mat.hpp>

typedef hwlib::target::pins duepin ;
namespace target = hwlib::target;

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto ss = hwlib::target::pin_out(duepin::d7);
    auto sclk = hwlib::target::pin_out(duepin::d4);
    auto miso = hwlib::target::pin_in(duepin::d12);
    auto mosi = hwlib::target::pin_out(duepin::d2);
    auto ack = target::pin_in(duepin::d25);

    r2d2::ps2_bus_c bus(ss, sclk, miso, mosi, ack);
    r2d2::ps2_controller_c controller(bus);
    for (;;) {
        // r2d2::button_states_s states = controller.get_button_states();
        // hwlib::cout << "select:" << states.select << "\n";
        // hwlib::cout << "start:" << states.start << "\n";
        // hwlib::cout << "up:" << states.up << "\n";
        // hwlib::cout << "down:" << states.down << "\n";
        // hwlib::cout << "left:" << states.left << "\n";
        // hwlib::cout << "right:" << states.right << "\n";

        // hwlib::cout << "l1:" << states.l1 << "\n";
        // hwlib::cout << "l2:" << states.l2 << "\n";
        // hwlib::cout << "r1:" << states.r1 << "\n";
        // hwlib::cout << "r2:" << states.r2 << "\n";
        // hwlib::cout << "square:" << states.square << "\n";
        // hwlib::cout << "cross:" << states.cross << "\n";
        // hwlib::cout << "triangle:" << states.triangle << "\n";
        // hwlib::cout << "circle:" << states.circle << "\n";
        // hwlib::cout << "end\n";
        hwlib::cout << controller.get_button(r2d2::button_cross) << "\n";
        hwlib::wait_ms(5000);
    }
}