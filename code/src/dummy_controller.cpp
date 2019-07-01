#include <controller_interface.hpp>
#include <dummy_controller.hpp>

// getters
bool r2d2::manual_control::dummy_controller_c::get_button(
    r2d2::manual_control::buttons button) {
    return buttons[button];
};
unsigned char r2d2::manual_control::dummy_controller_c::get_slider(
    r2d2::manual_control::sliders slider) {
    return sliders[slider];
};
joystick_value_s r2d2::manual_control::dummy_controller_c::get_joystick(
    r2d2::manual_control::joysticks joystick) {
    return joysticks[joystick];
};

// setters
void r2d2::manual_control::dummy_controller_c::set_button(
    r2d2::manual_control::buttons button, bool button_state) {
    buttons[button] = button_state;
};
void r2d2::manual_control::dummy_controller_c::set_slider(
    r2d2::manual_control::sliders slider, unsigned char slider_state) {
    sliders[slider] = slider_state;
};
void r2d2::manual_control::dummy_controller_c::set_joystick(
    r2d2::manual_control::joysticks joystick, joystick_value_s joystick_state) {
    joysticks[joystick] = joystick_state;
};