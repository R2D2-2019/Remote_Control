#include <dummy_controller.hpp>
#include <ostream>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace r2d2::manual_control;

TEST_CASE("testing buttons", " [interface]") {
    auto dummy_controller = dummy_controller_c();
    for (int x = button_a; x <= menu_right; x++) {
        // check buttons
        buttons button = static_cast<buttons>(x);
        CHECK(dummy_controller.get_button(button) == 0);
        dummy_controller.set_button(button, 1);
        CHECK(dummy_controller.get_button(button) == 1);
    }
    // check sliders
    CHECK(dummy_controller.get_slider(slider_l) == 0);
    CHECK(dummy_controller.get_slider(slider_r) == 0);
    dummy_controller.set_slider(slider_l, 1);
    dummy_controller.set_slider(slider_r, 1);
    CHECK(dummy_controller.get_slider(slider_l) == 1);
    CHECK(dummy_controller.get_slider(slider_r) == 1);
    // check joysticks
    CHECK(dummy_controller.get_joystick(joystick_l).x == 0);
    CHECK(dummy_controller.get_joystick(joystick_l).y == 0);
    CHECK(dummy_controller.get_joystick(joystick_r).x == 0);
    CHECK(dummy_controller.get_joystick(joystick_r).y == 0);
    dummy_controller.set_joystick(joystick_l, {1, 1});
    dummy_controller.set_joystick(joystick_r, {1, 1});
    CHECK(dummy_controller.get_joystick(joystick_l).x == 1);
    CHECK(dummy_controller.get_joystick(joystick_l).y == 1);
    CHECK(dummy_controller.get_joystick(joystick_r).x == 1);
    CHECK(dummy_controller.get_joystick(joystick_r).y == 1);
}