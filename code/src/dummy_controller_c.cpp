#include <dummy_controller_c.hpp>
#include <controller_interface_c.hpp>

/**
    * @brief Get a button value from the controller
    * 
    * @return bool 
    */
        bool R2D2::manual_control::dummy_controller_c::get_button(R2D2::manual_control::buttons button){
            return buttons[button];
        };
        
    /**
    * @brief Get a slider value from the controller
    * 
    * @return unsigned char 
    */
        unsigned char R2D2::manual_control::dummy_controller_c::get_slider(R2D2::manual_control::sliders slider){
            return sliders[slider];
        };
   
    /**
    * @brief Get a joystick value from the controller. This returns a struct. 
    * 
    * @return joystick_value_s 
    */   
        joystick_value_s R2D2::manual_control::dummy_controller_c::get_joystick(R2D2::manual_control::joysticks joystick){
            return joysticks[joystick];
        };

    void R2D2::manual_control::dummy_controller_c::set_button(R2D2::manual_control::buttons button, bool button_state){
        buttons[button] = button_state;
    };

    void R2D2::manual_control::dummy_controller_c::set_slider(R2D2::manual_control::sliders slider, unsigned char slider_state){
        sliders[slider] = slider_state;
    };

    void R2D2::manual_control::dummy_controller_c::set_joystick(R2D2::manual_control::joysticks joystick, joystick_value_s joystick_state){
        joysticks[joystick] = joystick_state;
    };
