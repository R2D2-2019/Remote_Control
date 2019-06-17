#include "hwlib.hpp"
#include <dummy_controller_c.hpp>

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
      hwlib::cout << "this works via arduino\n";
      hwlib::wait_ms(1000);
      auto dummy_controller = R2D2::manual_control::dummy_controller_c();
      hwlib::cout << "all buttons:\n";
      for(int x = R2D2::manual_control::button_a; x <= R2D2::manual_control::menu_right; x++){
        //check buttons
          R2D2::manual_control::buttons button = static_cast<R2D2::manual_control::buttons>(x);
          hwlib::cout << "\nbutton " << button << "\nbefore button changed: " << dummy_controller.get_button(button) << "\n";

        //change button state
          dummy_controller.set_button(button, 1);
          hwlib::cout << "after button changed: ";

        //check buttons
          hwlib::cout << dummy_controller.get_button(button) << "\n";
      }

      //check sliders
      hwlib::cout << "\n\nsliders:\nslider_l: " << dummy_controller.get_slider(R2D2::manual_control::slider_l);
      hwlib::cout << "\nslider_r: " << dummy_controller.get_slider(R2D2::manual_control::slider_r);

      //change slider state
      dummy_controller.set_slider(R2D2::manual_control::slider_l, 50);
      dummy_controller.set_slider(R2D2::manual_control::slider_r, 50);

      //check sliders
      hwlib::cout << "\n\nsliders after change:\nslider_l: " << dummy_controller.get_slider(R2D2::manual_control::slider_l);
      hwlib::cout << "\nslider_r: " << dummy_controller.get_slider(R2D2::manual_control::slider_r);

      //check joysticks
      hwlib::cout << "\n\njoysticks:\njoystick_l: " << dummy_controller.get_joystick(R2D2::manual_control::joystick_l).x;
      hwlib::cout << ", " << dummy_controller.get_joystick(R2D2::manual_control::joystick_l).y;
      hwlib::cout << "\njoystick_r: " << dummy_controller.get_joystick(R2D2::manual_control::joystick_r).x;
      hwlib::cout << ", " << dummy_controller.get_joystick(R2D2::manual_control::joystick_r).y;

      //change joystick state
      dummy_controller.set_joystick(R2D2::manual_control::joystick_l, {50, 46});
      dummy_controller.set_joystick(R2D2::manual_control::joystick_r, {68, 100});

      //check joysticks
      hwlib::cout << "\n\njoysticks after change:\njoystick_l: " << dummy_controller.get_joystick(R2D2::manual_control::joystick_l).x;
      hwlib::cout << ", " << dummy_controller.get_joystick(R2D2::manual_control::joystick_l).y;
      hwlib::cout << "\njoystick_r: " << dummy_controller.get_joystick(R2D2::manual_control::joystick_r).x;
      hwlib::cout << ", " << dummy_controller.get_joystick(R2D2::manual_control::joystick_r).y;


}