#pragma once

#include <hwlib.hpp>

class PS2_bus_c : public hwlib::spi_bus{
private:
    hwlib::pin_out &select;
    hwlib::pin_out &sclk;
    hwlib::pin_in &miso;
    hwlib::pin_out &mosi;
    hwlib::pin_in &acknowlage;
    unsigned int transfer_rate;
public:
    PS2_bus_c() = delete;
    PS2_bus_c(PS2_bus_c &ps2) = delete;
    PS2_bus_c(hwlib::pin_out &select,
            hwlib::pin_out &sclk,
            hwlib::pin_in &miso,
            hwlib::pin_out &mosi,
            hwlib::pin_in &acknowlage,
            unsigned int transfer_rate = 0); 

    void write_and_read(const size_t numb_bytes_read, 
                        const uint8_t data_out[], 
                        uint8_t data_in[])override;

protected:
    bool tick(bool data_out);
    uint8_t transfer_byte(uint8_t command);
};