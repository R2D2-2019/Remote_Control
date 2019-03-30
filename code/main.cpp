#include "serial_arduino.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

/*
COM2:   Due
COM5:   Uno
*/

int main(void) {
    const char *port = "\\\\.\\COM2";
    serial_arduino arduino(port, 64);
    std::vector<unsigned char> input;
    while (!(GetKeyState('A') & 0x8000) && arduino.isConnected()) {
        input = arduino.serial_read();
        for (auto &i : input) {
            std::cout << static_cast<int>(i) << ",";
        }
        std::cout << std::endl;
    }
}