#pragma once
#include "SerialPort.h"
#include <iostream>
#include <vector>

namespace r2d2::remote_control {
    class serial_arduino_c {
    private:
        const char *port;
        unsigned int buffer_size;
        SerialPort *arduino;

        /**
         * This method extracts bytes from a std::string and puts them in
         * a std::vector<unsigned char>.
         * @param input
         * @return std::vector<unsigned char>
         */
        std::vector<unsigned char> extract_bytes(std::string input);

    public:
        /**
         * This constructor creates a new serial_arduino_c object using a
         * COM-port and a buffer size.
         * @param port
         * @param buffer_siz
         */
        serial_arduino_c(const char *port, unsigned int buffer_size)
            : port(port),
              buffer_size(buffer_size),
              arduino(new SerialPort(port)) {
        }

        /**
         * This destructor destroys a serial_arduino_c object.
         */
        ~serial_arduino_c() {
            delete arduino;
        }

        /**
         * This method returns the serial input data as an std::vector<unsigned
         * char>.
         * @return std::vector<unsigned char>
         */
        std::vector<unsigned char> serial_read();

        /**
         * This method checks of there is a connection between the PC and the
         * Arduino and returns true for a connection and false for no
         * connection.
         * @return bool
         */
        bool isConnected();
    };
} // namespace r2d2::remote_control
