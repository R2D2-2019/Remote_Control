#include <ostream>
#include <dummy_controller.hpp>
#include <manual_control.hpp>
#include <mock_bus.hpp>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace r2d2::manual_control;

TEST_CASE("Testing button", " [canbus]") {
    // Numbers
    int controller_id = 1;
    buttons button = buttons::button_a;

    // Create mock bus
    r2d2::mock_comm_c comm;

    // Accept all frames
    comm.listen_for_frames({r2d2::frame_type::ALL});

    // Create dummy controller
    auto controller = dummy_controller_c(controller_id);

    // Create the module with a dummy_controller
    module_c module(comm, controller);

    // Change the button state
    controller.set_button(button, true);

    // Should send a frame with the new value of the button
    module.process();

    // Check if module created a frame
    REQUIRE(comm.get_send_frames().size() == 1);

    // Get the first item in the vector
    auto comm_data = (*comm.get_send_frames().begin());
    REQUIRE(comm_data.type == r2d2::frame_type::MANUAL_CONTROL_BUTTON);

    auto frame = comm_data.as_frame_type<r2d2::frame_type::MANUAL_CONTROL_BUTTON>();

    // Assert
    REQUIRE(frame.controller_id == controller_id);
    REQUIRE(frame.button_id == button);
    REQUIRE(frame.value == true);
}

TEST_CASE("Testing sliders", " [canbus]") {
    // Numbers
    int controller_id = 1;
    sliders slider = sliders::slider_l;
    int new_value = 100;

    // Create mock bus
    r2d2::mock_comm_c comm;

    // Accept all frames
    comm.listen_for_frames({r2d2::frame_type::ALL});

    // Create dummy controller
    auto controller = dummy_controller_c(controller_id);

    // Create the module with a dummy_controller
    module_c module(comm, controller);

    // Change the slider value
    controller.set_slider(slider, new_value);

    // Should send a frame with the new value of the slider
    module.process();

    // Check if module created a frame
    REQUIRE(comm.get_send_frames().size() == 1);

    // Get the first item in the vector
    auto comm_data = (*comm.get_send_frames().begin());
    REQUIRE(comm_data.type == r2d2::frame_type::MANUAL_CONTROL_SLIDER);

    auto frame = comm_data.as_frame_type<r2d2::frame_type::MANUAL_CONTROL_SLIDER>();

    // Assert
    REQUIRE(frame.controller_id == controller_id);
    REQUIRE(frame.slider_id == slider);
    REQUIRE(frame.value == new_value);
}

TEST_CASE("Testing joysticks", " [canbus]") {
    // Numbers
    int controller_id = 1;
    int new_x = 100;
    int new_y = 100;
    joysticks joystick = joysticks::joystick_l;

    // Create mock bus
    r2d2::mock_comm_c comm;

    // Accept all frames
    comm.listen_for_frames({r2d2::frame_type::ALL});

    // Create dummy controller
    auto controller = dummy_controller_c(controller_id);

    // Create the module with a dummy_controller
    module_c module(comm, controller);

    controller.set_joystick(joystick, {new_x, new_y});

    module.process();

    // Check if module created a frame
    REQUIRE(comm.get_send_frames().size() == 1);

    // Get the first item in the vector
    auto comm_data = (*comm.get_send_frames().begin());
    REQUIRE(comm_data.type == r2d2::frame_type::MANUAL_CONTROL_JOYSTICK);

    auto frame = comm_data.as_frame_type<r2d2::frame_type::MANUAL_CONTROL_JOYSTICK>();

    // Assert
    REQUIRE(frame.controller_id == controller_id);
    REQUIRE(frame.joystick_id == joystick);
    REQUIRE(frame.value_x == new_x);
    REQUIRE(frame.value_y == new_y);
}

TEST_CASE("Testing margin", " [canbus]") {
    // Numbers
    int controller_id = 1;
    int value_y = 100;

    int original_value_x = 100; // First change
    int new_value_x = 102; // Second change

    joysticks joystick = joysticks::joystick_l;

    // Create mock bus
    r2d2::mock_comm_c comm;

    // Accept all frames
    comm.listen_for_frames({r2d2::frame_type::ALL});

    // Create dummy controller
    auto controller = dummy_controller_c(controller_id);

    // Create the module with a dummy_controller
    module_c module(comm, controller);

    controller.set_joystick(joystick, {original_value_x, value_y});

    module.process();

    // Initial change should cause a frame to be send
    REQUIRE(comm.get_send_frames().size() == 1);

    controller.set_joystick(joystick, {new_value_x, value_y});

    module.process();

    // Module should not create a new frame due to the minimum margin (currently 5)
    REQUIRE(comm.get_send_frames().size() == 1);
}