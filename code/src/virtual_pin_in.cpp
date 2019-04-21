#include "virtual_pin_in.hpp"

VirtualPinIn::VirtualPinIn(const VirtualPinIn &copy): 
    _target(copy._target), 
    _position(copy._position), 
    _port(copy._port) 
{}

VirtualPinIn::VirtualPinIn(uint16_t &target, buttons position, hwlib::port_in* port):
    _target(&target), 
    _position(position), 
    _port(port) 
{}

bool VirtualPinIn::read() {
    if(this->_port != nullptr) {
        this->_port->refresh();
    }
    return ((*this->_target) >> (uint16_t)this->_position) & 0x01;
}

void VirtualPinIn::refresh(){
        if(this->_port == nullptr){
            return;
        }
        this->_port->refresh();
    }