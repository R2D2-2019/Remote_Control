#pragma once
#include <joystick_value_s.hpp>

namespace r2d2::manual_control {
    
    enum buttons {button_a, button_b, button_x, button_y, dpad_up, dpad_down, dpad_left, dpad_right, bumper_left, bumper_right, menu_left, menu_right};
    enum sliders {slider_l, slider_r};
    enum joysticks {joystick_l, joystick_r};


/**
 *  \brief
 *  This class is an interface for different kinds of controllers.
 * 
 *  \details
 *   Every controller will inherit from this class. This class is a custom controller [TO DO: link picture].
 *   The buttons of every controller will map to the buttons of the 'fake controller'.
 */
    class controller_interface_c{
    public:
    /**
    * @brief Get a button value from the controller
    * 
    * @return bool 
    */
        virtual bool get_button(buttons button) = 0;
        
    /**
    * @brief Get a slider value from the controller
    * 
    * @return unsigned char 
    */
        virtual unsigned char get_slider(sliders slider) = 0;
   
    /**
    * @brief Get a joystick value from the controller. This returns a struct. 
    * 
    * @return joystick_value_s 
    */   
        virtual joystick_value_s get_joystick(joysticks joystick) = 0;
    };

}