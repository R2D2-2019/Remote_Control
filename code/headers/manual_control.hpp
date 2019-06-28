#include <base_module.hpp>
#include <controller_interface.hpp>

namespace r2d2::manual_control {
    class module_c : public base_module_c {
    private:
        joystick_value_c abs(joystick_value_c value){
	        if (value.x < 0){
	            value.x *= -1;
	        }
            if (value.y < 0){
                value.y *= -1;
            }
	        return value;
        }

        int abs(int value){
            if (value < 0){
                value *= -1;
            }
            return value;
        }

        r2d2::manual_control::controller_interface_c & controller;
        bool button_list[12] = {};
        unsigned char slider_list[2] = {};
        joystick_value_c joystick_list[2] = {};
        frame_manual_control_button_s button_state;
        frame_manual_control_slider_s slider_state;
        frame_manual_control_joystick_s joystick_state;

    public:
        /**
         * @param comm
         */
        module_c(base_comm_c &comm, r2d2::manual_control::controller_interface_c & controller) 
            : base_module_c(comm),
              controller(controller) {}

        /**
         * Let the module process data.
         */
        void process() override {
            for (int x = button_a; x <= menu_right; x++) {
                // handle buttons
            buttons button = static_cast<buttons>(x);
            auto button_value = controller.get_button(button);

            if (button_list[button] != button_value){          //check if button state is changed
                button_list[button] = button_value;

                // put button frame on canbus.
                hwlib::cout << "button " << button << " changed\n";
                button_state.controller_id = controller.controller_id;
                button_state.button_id = button;
                button_state.value = button_value;
                comm.send(button_state);
                hwlib::cout << " should be send\n";



                }
            }
                //handle sliders
            auto slider_left = controller.get_slider(r2d2::manual_control::slider_l);
            auto slider_right = controller.get_slider(r2d2::manual_control::slider_r);

                //check if slider_l changed more then 5 (so canbus is not spammed)
            if (abs(slider_list[slider_l] - slider_left) >= 5){                 
                slider_list[slider_l] = slider_left;
                // put slider frame on canbus. 
                //hwlib::cout << "slider_l changed" << slider_list[slider_l] << "\n";

                slider_state.controller_id = controller.controller_id;
                slider_state.slider_id = slider_l;
                slider_state.value = slider_left;
                comm.send(slider_state);
                //hwlib::cout << " should be send\n";
            }
                //check if slider_r changed more then 5 (so canbus is not spammed)
            if (abs(slider_list[slider_r] - slider_right) >= 5){                
                slider_list[slider_r] = slider_right;
                // put slider frame on canbus. 
                //hwlib::cout << "slider_r changed: " << slider_list[slider_r] << "\n";

                slider_state.controller_id = controller.controller_id;
                slider_state.slider_id = slider_r;
                slider_state.value = slider_right;
                comm.send(slider_state);
                //hwlib::cout << " should be send\n";
            }
            
                //handle joysticks
            auto joystick_left = controller.get_joystick(r2d2::manual_control::joystick_l);
            auto joystick_right = controller.get_joystick(r2d2::manual_control::joystick_r);

                //check if joystick_l changed more then 5 (so canbus is not spammed)
            if (abs(joystick_list[joystick_l] - joystick_left) >= 5){
                joystick_list[joystick_l] = joystick_left;
                // put joystick frame on canbus. 
                //hwlib::cout << "joystick_l changed: " << joystick_list[joystick_l].x << " " << joystick_list[joystick_l].y << "\n";

                joystick_state.controller_id = controller.controller_id;
                joystick_state.joystick_id = joystick_l;
                joystick_state.value_x = joystick_left.x;
                joystick_state.value_y = joystick_left.y;
                comm.send(joystick_state);
                //hwlib::cout << " should be send\n";
            }
           
                //check if joystick_r changed more then 5 (so canbus is not spammed)
            if (abs(joystick_list[joystick_r] - joystick_right) >= 5){
                joystick_list[joystick_r] = joystick_right;
                // put joystick frame on canbus. 
                //hwlib::cout << "joystick_r changed: " << joystick_list[joystick_r].x << " " << joystick_list[joystick_r].y << "\n";

                joystick_state.controller_id = controller.controller_id;
                joystick_state.joystick_id = joystick_l;
                joystick_state.value_x = joystick_right.x;
                joystick_state.value_y = joystick_right.y;
                comm.send(joystick_state);
                //hwlib::cout << " should be send\n";
            }



        }
    };
}