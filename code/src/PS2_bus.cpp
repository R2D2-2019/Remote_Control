#include "PS2_bus.hpp"

PS2_bus_c::PS2_bus_c(hwlib::pin_out &select, hwlib::pin_out &sclk, hwlib::pin_in &miso, hwlib::pin_out &mosi, hwlib::pin_in &acknowlage, unsigned int transfer_rate):
    select(select),
    sclk(sclk),
    miso(miso),
    mosi(mosi),
    acknowlage(acknowlage),
    transfer_rate(transfer_rate)
{}           

void PS2_bus_c::write_and_read(const size_t numb_bytes_read, const uint8_t data_out[], uint8_t data_in[] ){
    select.write(false);
    select.flush();
    for(unsigned int i = 0; i < numb_bytes_read; i++) {
        uint8_t output = this->transfer_byte(data_out[i]);
        data_in[i] = output;
    }
    select.write(true);
    select.flush();
}
        

bool PS2_bus_c::tick(bool data_out){
    mosi.write(data_out); 
    mosi.flush();
    hwlib::wait_us(20);
    //hwlib::wait_ms(1);
    sclk.write(1);
    sclk.flush();
    // hwlib::wait_us(100);
    hwlib::wait_us(4);
    miso.refresh();
    bool inputValue = miso.read();
    hwlib::wait_us(20);
    sclk.write(0);
    sclk.flush();
    return inputValue;
}
uint8_t PS2_bus_c::transfer_byte(uint8_t command){        
    uint8_t output = 0x00;
    for(uint_fast8_t bit = 0; bit < 8; bit++) {
        output <<= 1;    
        bool value = this->tick((command >> bit) & 1);
        output |= value;
    }
    return output;
}