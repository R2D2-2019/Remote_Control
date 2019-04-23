#include "virtual_pin_in.hpp"

virtual_pin_in_c::virtual_pin_in_c(const virtual_pin_in_c &copy): 
    target(copy.target), 
    position(copy.position), 
    port(copy.port) 
{}

virtual_pin_in_c::virtual_pin_in_c(uint16_t &target, buttons position, hwlib::port_in* port):
    target(&target), 
    position(position), 
    port(port) 
{}

bool virtual_pin_in_c::read() {
    if(this->port != nullptr) {
        this->port->refresh();
    }
    return ((*this->target) >> (uint16_t)this->position) & 0x01;
}

void virtual_pin_in_c::refresh(){
        if(this->port == nullptr){
            return;
        }
        this->port->refresh();
    }