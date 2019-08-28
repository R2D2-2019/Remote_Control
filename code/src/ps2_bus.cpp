#include <ps2_bus.hpp>

r2d2::ps2_bus_c::ps2_bus_c(
        hwlib::pin_out &attention,
        hwlib::pin_out &clock,
        hwlib::pin_in &data,
        hwlib::pin_out &command,
        hwlib::pin_in &acknowledge) :

        attention(attention),
        clock(clock),
        data(data),
        command(command),
        acknowledge(acknowledge)
        {}

std::array<uint8_t, 8> r2d2::ps2_bus_c::read_write(const uint8_t command_data[], uint8_t n){

    attention.write( 0 );
    hwlib::wait_us(10);
    uint8_t data_in[8] = {0};
    auto counter = data_in;

    for( uint_fast8_t i = 0; i < n; ++i ){

        uint_fast8_t d = 
            ( command_data == nullptr )
            ? 0 
            : *command_data++;
             
        for( uint_fast8_t j = 0; j < 8; ++j ){
            command.write( ( d & 0x01 ) != 0 );
            wait_half_period();
            clock.write( 0 );
            wait_half_period();
            clock.write( 1 );   
            d = d >> 1;
            if( data.read() ){
                (d |= 0x80);
            }           
          }


        if( counter != nullptr ){
            *counter++ = d;
        }
        hwlib::wait_us(50);
    }      
    wait_half_period();
    attention.write( 1 );
    wait_half_period();
    std::array<uint8_t, 8> last_data;
    std::copy(std::begin(data_in), std::end(data_in), std::begin(last_data));
    return last_data;
}

void r2d2::ps2_bus_c::wait_half_period(){
    hwlib::wait_us( 5 );
}

