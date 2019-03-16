#include "usb_controller.hpp"
#include <bitset>
#include <iostream>
#include <libusb.h>
#include <vector>
#include <windows.h>

int main(void) {
    std::vector<unsigned char> input_vector;
    usb_controller logitech(129, 1133, 49686);
    while (!(GetKeyState('A') & 0x8000) && logitech.controller_exist()) {
        input_vector = logitech.get_controller_output();
        for (unsigned int i = 0; i < input_vector.size(); i++) {
            std::cout << std::bitset<8>(input_vector[i]) << " ";
        }
        std::cout << std::endl;
    }
}