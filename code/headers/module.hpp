#pragma once

#include <base_module.hpp>
#include <steering_wheel_controller.hpp>

namespace r2d2::manual_control {
    class module_c : public base_module_c {
    private:
        steering_wheel_controller_c &steering_wheel;

    public:
        steering_wheel_controller_c(base_comm_c &comm, steering_wheel)
            : base_module_c(comm), steering_wheel(steering_wheel) {

            comm.listen_for_frames({
                frame_type::MANUAL_CONTROL // frame_type not yet implemented in
                                           // internal communication
            });
        }

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

                // Is this frame a request?
                if (!frame.request) {
                    continue;
                }

                // Send it off!
                comm.send(frame);
            }
        }
    };

} // namespace r2d2::manual_control
