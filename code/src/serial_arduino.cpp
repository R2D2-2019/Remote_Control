#include "serial_arduino.hpp"

std::vector<unsigned char>
r2d2::remote_control::serial_arduino_c::extract_bytes(std::string input) {
    std::vector<unsigned char> vec;
    std::string tmp = "";
    for (unsigned int i = 0; i < input.size(); i++) {
        if (input[i] != '-') {
            tmp += input[i];
        } else {
            vec.push_back(std::stoi(tmp));
            tmp = "";
        }
    }
    return vec;
}

std::vector<unsigned char>
r2d2::remote_control::serial_arduino_c::serial_read() {
    unsigned char input[buffer_size];
    std::vector<unsigned char> vec;
    std::string tmp = "";
    while (input[0] != '\n') {
        int in = arduino->readSerialPort(input, buffer_size);
        if (in) {
            if (input[0] == '-' || (input[0] >= '0' && input[0] <= '9')) {
                tmp += input[0];
            } else if (input[0] == '\n') {
                vec = extract_bytes(tmp);
            }
        }
    }
    return vec;
}

bool r2d2::remote_control::serial_arduino_c::isConnected() {
    return arduino->isConnected();
}