#pragma once
#include <controller_interface.hpp>

namespace r2d2::manual_control {

    class dummy_controller_c : public controller_interface_c {
    private:
        // initializing all buttons, sliders and joysticks at their base (0)
        unsigned char sliders[2] = {};

        std::array<bool, 12> buttons;
        std::array<joystick_value_s, 2> joysticks;

    public:
        dummy_controller_c(int controller_id)
            : controller_interface_c(controller_id) {
        }
        /**
         * @brief Get a button value from the controller
         *
         * @return bool
         */
        bool get_button(r2d2::manual_control::buttons button);

        /**
         * @brief Get a slider value from the controller
         *
         * @return unsigned char
         */
        unsigned char get_slider(r2d2::manual_control::sliders slider);

        /**
         * @brief Get a joystick value from the controller. This returns a
         * struct.
         *
         * @return joystick_value_s
         */
        joystick_value_s get_joystick(r2d2::manual_control::joysticks joystick);

        /**
         * @brief Set a button value.
         *
         * @param button button to set
         * @param button_state new button value
         */
        void set_button(r2d2::manual_control::buttons button,
                        bool button_state);

        /**
         * @brief Set a slider value.
         *
         * @param slider slider to set
         * @param slider_state new slider value
         */
        void set_slider(r2d2::manual_control::sliders slider,
                        unsigned char slider_state);

        /**
         * @brief Set a joystick value.
         *
         * @param joystick joystick to set
         * @param joystick_state new joystick value
         */
        void set_joystick(r2d2::manual_control::joysticks joystick,
                          joystick_value_s joystick_state);
    };

} // namespace r2d2::manual_control
