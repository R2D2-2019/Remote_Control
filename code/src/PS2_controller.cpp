#include "PS2_controller.hpp"

PS2_controller_c::PS2_controller_c(PS2_bus_c &ps2_bus, hwlib::pin_out &select): 
    ps2_bus(ps2_bus),
    select(select),
    buffer(0x00), 
    default_buffer({0}),
    analog_mode(false), 
    config_mode(false), 
    controller_locked(false)
{}


void PS2_controller_c::init() {
    std::array<uint8_t, 21> output = { 0 };
    this->set_config_mode(true);
    hwlib::wait_ms(1);
    this->set_analog_mode(true, true);
    hwlib::wait_ms(1);
    {
        auto enable_buttons = this->_enableAllButtonsCommand;
        this->ps2_bus.write_and_read(9, enable_buttons.data(), output.data());
    }
    hwlib::wait_ms(1);
    this->set_config_mode(false);
}

uint16_t PS2_controller_c::get_button_bytes(){
    auto output = this->execute_command(this->_readGamepadCommand);
    uint16_t value = (uint16_t(output[3]) << 8 | output[4]);
    return value;
}

bool PS2_controller_c::in_analog(){
    return this->analog_mode;
}

bool PS2_controller_c::in_config(){
    return this->config_mode;
}

bool PS2_controller_c::is_locked(){
    return this->controller_locked;
}

std::array<uint16_t, 2> PS2_controller_c::get_joystick(const bool right_joystick) {
    std::array<uint16_t, 2> values;
    if(!this->analog_mode) {
        this->set_analog_mode(true, true);
    }
    const std::array<uint8_t, 21>& output = this->execute_command(this->_pollCommand);
    const pull_all_responses_s &bytes = *reinterpret_cast<const pull_all_responses_s*>(&output);
    if(right_joystick){
        this->buffer = bytes.digitalButtons1 << 8 | bytes.digitalButtons2;
        values = { bytes.rightJoystickX, bytes.rightJoystickY};
    }else {
        values = { bytes.leftJoystickX, bytes.leftJoystickY };
    }
    return values;
}


uint_fast8_t PS2_controller_c::read() {
    this->refresh();
    return this->hwlib_buffer;
}

void PS2_controller_c::refresh() {
    uint_fast16_t values = this->get_button_bytes();
    this->buffer = ~values;
    uint_fast8_t output = 0x00;
    output |= ((output & 0x0F << 9) >> 5);
    output |= 0x0F & output;
    this->hwlib_buffer = ~output;
}

virtual_pin_in_c PS2_controller_c::pin_button(const virtual_pin_in_c::buttons &button){
    return virtual_pin_in_c(this->buffer, button, this);
}

void PS2_controller_c::set_config_mode(const bool enabled){
    if(enabled && !this->config_mode){
        this->execute_command(this->_enterConfigCommand);
    }
    else if(!enabled && this->config_mode) {
        this->execute_command(this->_exitConfigCommand);
    }
    this->config_mode = enabled;
}

void PS2_controller_c::set_analog_mode(const bool enabled, const bool locked ) {
    this->set_config_mode(true);
    if(enabled){
        _setModeCommand[3] = uint8_t(0x01);
        analog_mode = true;
    }
    else{
        _setModeCommand[3] = uint8_t(0x00);
        analog_mode = true; 
    }
    if(locked){
        _setModeCommand[4] = uint8_t(0x03);
        controller_locked = true;
    }
    else{
        _setModeCommand[4] = uint8_t(0x00);
        controller_locked = false;
    }
    this->execute_command(this->_setModeCommand);
    this->set_config_mode(false);
}
void PS2_controller_c::set_locked(const bool locked) {
    this->set_analog_mode(this->analog_mode, locked);
}
template<size_t SIZE>
const std::array<uint8_t, 21>&  PS2_controller_c::execute_command(const std::array<uint8_t, SIZE>& command) {
        this->ps2_bus.write_and_read(command.max_size(), command.data(), this->default_buffer.data());
    return this->default_buffer;
}