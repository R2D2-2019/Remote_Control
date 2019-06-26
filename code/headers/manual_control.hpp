#include <base_module.hpp>
#include <controller_interface.hpp>

namespace r2d2::manual_control {
    class module_c : public base_module_c {
    private:
        r2d2::manual_control::controller_interface_c & controller;
        bool button_list[12] = {};
        unsigned char slider_list[2] = {};
        joystick_value_c joystick_list[2] = {};
        frame_manual_control_button_state_s button_state;
        frame_manual_control_slider_state_s slider_state;
        frame_manual_control_joystick_state_s joystick_state;


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
            hwlib::cout << "processing\n";

            for (int x = button_a; x <= menu_right; x++) {
                // handle buttons
            buttons button = static_cast<buttons>(x);
            if (button_list[button] != controller.get_button(button)){
                button_list[button] = controller.get_button(button);

                // put button frame on canbus.
                hwlib::cout << "button " << button << " changed\n";

                }
            }
                //handle sliders
            if (slider_list[slider_l] != controller.get_slider(r2d2::manual_control::slider_l)){
                slider_list[slider_l] = controller.get_slider(r2d2::manual_control::slider_l);
                // put slider frame on canbus. 
                hwlib::cout << "slider_l changed\n";
            }

            if (slider_list[slider_r] != controller.get_slider(r2d2::manual_control::slider_r)){
                slider_list[slider_r] = controller.get_slider(r2d2::manual_control::slider_r);
                // put slider frame on canbus. 
                hwlib::cout << "slider_r changed\n";
            }
            
                //handle joysticks
            if (joystick_list[joystick_l] != controller.get_joystick(r2d2::manual_control::joystick_l)){
                joystick_list[joystick_l] = controller.get_joystick(r2d2::manual_control::joystick_l);
                // put joystick frame on canbus. 
                hwlib::cout << "joystick_l changed\n";
            }
           
            if (joystick_list[joystick_r] != controller.get_joystick(r2d2::manual_control::joystick_r)){
                joystick_list[joystick_r] = controller.get_joystick(r2d2::manual_control::joystick_r);
                // put joystick frame on canbus. 
                hwlib::cout << "joystick_r changed\n";
            }



        }
    };
}