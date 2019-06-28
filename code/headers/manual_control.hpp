#include <base_module.hpp>
#include <controller_interface.hpp>

namespace r2d2::manual_control {
    class module_c : public base_module_c {
    private:
        /**
         *  \brief
         *  This function returns the ablosule of a joystick_value_c
         *
         *  \details
         *  This function takes the values from a joystick_value_c and makes
         * every value positive
         */
        joystick_value_c abs(joystick_value_c value) {
            if (value.x < 0) {
                value.x *= -1;
            }
            if (value.y < 0) {
                value.y *= -1;
            }
            return value;
        }
        /**
         *  \brief
         *  This function returns the ablosule of an int
         *
         *  \details
         *  This function makes the int positive
         */
        int abs(int value) {
            if (value < 0) {
                value *= -1;
            }
            return value;
        }

        r2d2::manual_control::controller_interface_c &controller;

        // lists to save previous states of buttons, sliders and joysticks
        bool button_list[12] = {};
        unsigned char slider_list[2] = {};
        joystick_value_c joystick_list[2] = {};

        // canbus frames
        frame_manual_control_button_s button_state;
        frame_manual_control_slider_s slider_state;
        frame_manual_control_joystick_s joystick_state;

    public:
        /**
         * @param comm
         */
        module_c(base_comm_c &comm,
                 r2d2::manual_control::controller_interface_c &controller)
            : base_module_c(comm), controller(controller) {
        }

        /**
         * Let the module process data.
         */
        void process() override {
            for (int x = button_a; x <= menu_right; x++) {
                // handle buttons
                buttons button = static_cast<buttons>(x);
                auto button_value = controller.get_button(button);

                // check if button state is changed
                if (button_list[button] != button_value) {
                    button_list[button] = button_value;

                    // fill button_state frame
                    button_state.controller_id = controller.controller_id;
                    button_state.button_id = button;
                    button_state.value = button_value;

                    // put button frame on canbus
                    comm.send(button_state);
                }
            }
            // handle sliders
            auto slider_left =
                controller.get_slider(r2d2::manual_control::slider_l);
            auto slider_right =
                controller.get_slider(r2d2::manual_control::slider_r);
            
            // check if slider_l changed more then 5 (so canbus is not spammed)
            // sometimes it give a random 243, with 100 < weird positive numbers can be prevented
            if (abs(slider_list[slider_l] - slider_left) >= 5 && slider_left < 100) {
            
                slider_list[slider_l] = slider_left;
                // put slider frame on canbus. 
                //hwlib::cout << "slider_l changed" << slider_list[slider_l] << "\n";

                // fill slider_state frame
                slider_state.controller_id = controller.controller_id;
                slider_state.slider_id = slider_l;
                slider_state.value = slider_left;

                // put slider frame on canbus
                comm.send(slider_state);
            }

            // check if slider_r changed more then 5 (so canbus is not spammed)
            if (abs(slider_list[slider_r] - slider_right) >= 5) {
                slider_list[slider_r] = slider_right;
                // fill slider_state frame
                slider_state.controller_id = controller.controller_id;
                slider_state.slider_id = slider_r;
                slider_state.value = slider_right;

                // put slider frame on canbus
                comm.send(slider_state);
            }

            // handle joysticks
            auto joystick_left =
                controller.get_joystick(r2d2::manual_control::joystick_l);
            auto joystick_right =
                controller.get_joystick(r2d2::manual_control::joystick_r);

            // check if joystick_l changed more then 5 (so canbus is not
            // spammed)
            if (abs(joystick_list[joystick_l] - joystick_left) >= 5) {
                joystick_list[joystick_l] = joystick_left;

                // fill joystick_state frame
                joystick_state.controller_id = controller.controller_id;
                joystick_state.joystick_id = joystick_l;
                joystick_state.value_x = joystick_left.x;
                joystick_state.value_y = joystick_left.y;

                // put joystick frame on canbus
                comm.send(joystick_state);
            }

            // check if joystick_r changed more then 5 (so canbus is not
            // spammed)
            if (abs(joystick_list[joystick_r] - joystick_right) >= 5) {
                joystick_list[joystick_r] = joystick_right;

                // fill joystick_state frame
                joystick_state.controller_id = controller.controller_id;
                joystick_state.joystick_id = joystick_l;
                joystick_state.value_x = joystick_right.x;
                joystick_state.value_y = joystick_right.y;

                // put joystick frame on canbus
                comm.send(joystick_state);
            }
        }
    };
} // namespace r2d2::manual_control