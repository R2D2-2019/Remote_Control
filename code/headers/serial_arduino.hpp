#pragma once
#include "SerialPort.h"
#include <iostream>
#include <vector>

class serial_arduino {
private:
    const char *port;
    unsigned int buffer_size;
    SerialPort *arduino;
    std::vector<unsigned char> extract_bytes(std::string input);

public:
    serial_arduino(const char *port, unsigned int buffer_size)
        : port(port), buffer_size(buffer_size), arduino(new SerialPort(port)) {
    }
    ~serial_arduino() {
        delete arduino;
    }
    std::vector<unsigned char> serial_read();
    bool isConnected();
};