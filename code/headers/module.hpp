#pragma once

#include <base_module.hpp>
#include <steering_wheel_controller.hpp>

namespace r2d2::manual_control {

    /**
     * Class module_c provides the process function
     * for receiving data requests
     * and sending the data of the steering_wheel_controller_c.
     */
    class module_c : public base_module_c {
    private:
        steering_wheel_controller_c &steering_wheel;

    public:
        /**
         * Instantiate the module class
         *
         * @param comm - The internal communication bus instance.
         * @param steering_wheel - The steering wheel controller that represents
         * the steering wheel/manual control.
         */
        steering_wheel_controller_c(base_comm_c &comm, steering_wheel)
            : base_module_c(comm), steering_wheel(steering_wheel) {

            comm.listen_for_frames({frame_type::MANUAL_CONTROL});
        }

        /**
         * This function lets the module process data
         */
        void process() override {
            frame_manual_control_state_s<4, 2> frame;
            frame.buttons[0] = steering_wheel.get_button(0);
            frame.buttons[1] = steering_wheel.get_button(1);
            frame.buttons[2] = steering_wheel.get_button(2);
            frame.buttons[3] = steering_wheel.get_button(3);

            frame.sliders[0] = steering_wheel.get_sliders(0);
            frame.sliders[1] = steering_wheel.get_sliders(1);

            while (comm.has_data()) {
                auto frame = comm.get_data();

                /*
                 * Only process frame if it is a request
                 */
                if (!frame.request) {
                    continue;
                }

                /*
                 * Send it off!
                 */
                comm.send(frame);
            }
        }
    };

} // namespace r2d2::manual_control
