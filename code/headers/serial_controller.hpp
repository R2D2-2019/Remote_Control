#pragma once
#include <controller_interface.hpp>

namespace r2d2::manual_control {

    class serial_controller_c : public controller_interface_c {

    public:
        serial_controller_c(int controller_id)
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
         *
         */
        void refresh();
    };

} // namespace r2d2::manual_control
