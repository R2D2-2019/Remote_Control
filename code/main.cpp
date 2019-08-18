#include <comm.hpp>
#include <dummy_controller.hpp>
#include <hwlib.hpp>
#include <manual_control.hpp>
#include <steering_wheel_controller.hpp>
#include <ps2_bus.hpp>

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

    const uint8_t poll_command[8] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    ps2_bus_c mat(ss, sclk, miso, mosi, ack);

    for (;;) {
        mat.read_write(poll_command, 8);
        for(int i = 0; i < 8; i++){
            hwlib::cout << mat.last_data[i] << "\n";
        }
        hwlib::cout << "end\n";
        hwlib::wait_ms(1000);
    }
}