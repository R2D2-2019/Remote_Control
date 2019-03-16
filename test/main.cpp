#include "usb_controller.hpp"
#include <algorithm>
#include <iostream>
#include <libusb.h>
#include <windows.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Output, empty") {
    usb_controller usb(129, 1133, 49686);
    usb.read_controller_output();
    std::vector<unsigned char> in = usb.get_last_input();
    std::vector<unsigned char> vec = {0, 0, 0, 0, 0, 0, 0, 0};
    bool test = std::equal(in.begin(), in.end(), vec.begin(), vec.end());
    REQUIRE(1 == 2);
}