#pragma once

#include <hwlib.hpp>

struct raw_data_s{
    uint8_t data1 =0;
    uint8_t data2 =0;
    uint8_t data3 =0;
    uint8_t data4 =0;
    uint8_t data5 =0;
    uint8_t data6 =0;
    uint8_t data7 =0;
    uint8_t data8 =0;
    uint8_t data9 =0;
};

class ps2_bus_c {
private:
    hwlib::pin_out &attention;
    hwlib::pin_out &clock;
    hwlib::pin_in &data;
    hwlib::pin_out &command;
    hwlib::pin_in &acknowledge;

    //commands:
    const uint8_t poll_command[8] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    
    void wait_half_period(){
      hwlib::wait_us( 5 );      
    };


    

public:
    ps2_bus_c(
        hwlib::pin_out &attention,
        hwlib::pin_out &clock,
        hwlib::pin_in &data,
        hwlib::pin_out &command,
        hwlib::pin_in &acknowledge);

    uint8_t last_data[9] = {0};
    void read_write(const uint8_t command[], uint8_t n);
};