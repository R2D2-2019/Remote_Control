#pragma once

#include <iostream>

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
}