#pragma once
#include <controller_interface_c.hpp>

namespace R2D2::manual_control {
    
    

    class dummy_controller_c: public controller_interface_c{
    private:
    bool buttons[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char sliders[2] = {0, 0};
    joystick_value_s joysticks[2] = {{0, 0},{0, 0}};


    
    public:

        dummy_controller_c() {
            
        }

        /**
    * @brief Get a button value from the controller
    * 
    * @return bool 
    */
        bool get_button(R2D2::manual_control::buttons button);
        
    /**
    * @brief Get a slider value from the controller
    * 
    * @return unsigned char 
    */
        unsigned char get_slider(R2D2::manual_control::sliders slider);
   
    /**
    * @brief Get a joystick value from the controller. This returns a struct. 
    * 
    * @return joystick_value_s 
    */   
        joystick_value_s get_joystick(R2D2::manual_control::joysticks joystick);



    void set_button(R2D2::manual_control::buttons button, bool button_state);
    void set_slider(R2D2::manual_control::sliders slider, unsigned char slider_state);
    void set_joystick(R2D2::manual_control::joysticks joystick, joystick_value_s joystick_state);


    };







}
