#include "ostream"
#include <dummy_controller_c.hpp>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("testing buttons", " [interface]") {
    auto dummy_controller = r2d2::manual_control::dummy_controller_c();
    for (int x = r2d2::manual_control::button_a;
         x <= r2d2::manual_control::menu_right; x++) {
        // check buttons
        r2d2::manual_control::buttons button =
            static_cast<r2d2::manual_control::buttons>(x);
        CHECK(dummy_controller.get_button(button) == 0);
        dummy_controller.set_button(button, 1);
        CHECK(dummy_controller.get_button(button) == 1);
    }

    // check sliders
    CHECK(dummy_controller.get_slider(r2d2::manual_control::slider_l) == 0);
    CHECK(dummy_controller.get_slider(r2d2::manual_control::slider_r) == 0);
    dummy_controller.set_slider(r2d2::manual_control::slider_l, 1);
    dummy_controller.set_slider(r2d2::manual_control::slider_r, 1);
    CHECK(dummy_controller.get_slider(r2d2::manual_control::slider_l) == 1);
    CHECK(dummy_controller.get_slider(r2d2::manual_control::slider_r) == 1);

    // check joysticks
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_l).x ==
          0);
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_l).y ==
          0);
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_r).x ==
          0);
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_r).y ==
          0);
    dummy_controller.set_joystick(r2d2::manual_control::joystick_l, {1, 1});
    dummy_controller.set_joystick(r2d2::manual_control::joystick_r, {1, 1});
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_l).x ==
          1);
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_l).y ==
          1);
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_r).x ==
          1);
    CHECK(dummy_controller.get_joystick(r2d2::manual_control::joystick_r).y ==
          1);
}