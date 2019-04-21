#pragma once

#include <hwlib.hpp>
#include <iostream>
#include "PS2_bus.hpp"
#include "virtual_pin_in.hpp"
#include <array>

class PS2_controller_c : public hwlib::port_in{
private:
    PS2_bus_c &ps2_bus;
    hwlib::pin_out &select;
    uint16_t buffer;
    uint_fast8_t  hwlib_buffer;
    std::array<uint8_t, 21> default_buffer;
    bool analog_mode;
    bool config_mode;
    bool controller_locked;
    
    const std::array<uint8_t, 21> _pollCommand = {
        0x01, 
        0x42, 
        0x00, 
        0x00, 
        0x00, 
        0x00, 
        0x00, 
        0x00, 
        0x00, 
        0x00, 
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00 
    };
    const std::array<uint8_t, 9> _readGamepadCommand = {
            0x01,
            0x42,
            0x00,
            0x00,
            0x00,
            
            0x00,
            0x00,
            0x00,
            0x00
        };
    const std::array<uint8_t, 5> _enterConfigCommand = {
        0x01,0x43,0x00,0x01,0x00
    };
    const std::array<uint8_t, 9> _exitConfigCommand = {
        0x01,0x43,0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A
    };
    std::array<uint8_t, 9> _setModeCommand = {
        0x01,
        0x44,
        0x00,
        0x00, // 0x01 for analog mode// analog ? uint8_t(0x01) : uint8_t(0x00),
        0x00, // 0x03 for lock on current mode locked ? uint8_t(0x03) : uint8_t(0x00),
        0x00,
        0x00,
        0x00,
        0x00
    };
    const std::array<uint8_t, 9> _getStatusCommand {
        0x01,
        0x45,
        0x00,
        0x5A,
        0x5A,
        0x5A,
        0x5A,
        0x5A,
        0x5A
    };
    std::array<uint8_t, 9> _enableAllButtonsCommand  = {
        0x01,0x4F,0x00,0xFF,0xFF,0x03,0x00,0x00,0x00
    };
    struct pull_all_responses_s {
    const uint8_t startPadding;
    const uint8_t deviceMode;
    const uint8_t p1;
    const uint8_t digitalButtons1;
    const uint8_t digitalButtons2;
    const uint8_t rightJoystickX;
    const uint8_t rightJoystickY;
    const uint8_t leftJoystickX;
    const uint8_t leftJoystickY;
    const uint8_t rightButton;   
    const uint8_t leftButton;
    const uint8_t upButton;
    const uint8_t downButton;
    const uint8_t triangleButton;
    const uint8_t circleButton;
    const uint8_t exButton;   
    const uint8_t squareButton;
    const uint8_t leftTopBumper;
    const uint8_t rightTopBumper;
    const uint8_t leftBottomBumper;
    const uint8_t rightBottomBumper;
};

public:
    PS2_controller_c(PS2_bus_c& bus, hwlib::pin_out &select);
    void init();
    uint16_t get_button_bytes();

    bool in_analog();
    bool in_config();
    bool is_locked();

    std::array<uint16_t, 2> get_joystick(const bool right_joystick);
    virtual uint_fast8_t number_of_pins() override;
    uint_fast8_t read() override;
    virtual void refresh() override;

    void set_config_mode(const bool enabled);
    void set_analog_mode(const bool enabled, const bool locked = false);
    void set_locked(const bool locked);
 
    VirtualPinIn pin_button(const VirtualPinIn::buttons &button);

    template<size_t SIZE>
    const std::array<uint8_t, 21>&  execute_command(const std::array<uint8_t, SIZE>& command);
};



