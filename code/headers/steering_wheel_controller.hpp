#pragma once

#include "controller_interface.hpp"
#include "joystick_value.hpp"
#include <hwlib.hpp>

namespace r2d2::manual_control {

    /**
     * Class steering_wheel_controller_c provides functions
     * for reading the data of the trust steering wheel.
     */
    class steering_wheel_controller_c : public hwlib::pin_in,
                                        public controller_interface_c {
    private:
        // Button on the steering wheel
        hwlib::pin_in &button1;
        hwlib::pin_in &button2;
        hwlib::pin_in &button3;
        hwlib::pin_in &button4;

        // The steering wheel itself
        hwlib::adc &steering_wheel;

        // The pedals
        hwlib::adc &pedals;

        /**
         * This function overrides the read() function of pin_in
         * and reads the data of a pin_in.
         *
         * @internal refreshes/reads the incoming data.
         */
        bool read() override;

        /**
         * Calculates the value of steering wheel
         *
         * @return direction of the steering wheel (type: int)
         */
        int get_steering_wheel();

        /**
         * Calculates the value of the pedals
         *
         * @return combined value of the pedals (type: int)
         */
        int get_pedals();

    public:
        /**
         * Instantiate the steering wheel controller class
         *
         * @param button1 The digital input that reads the button state.
         * @param button2 The digital input that reads the button state.
         * @param button3 The digital input that reads the button state.
         * @param button4 The digital input that reads the button state.
         * @param wheel The adc input that reads the data of the potmeter.
         * @param pedals The adc input that reads the data of the potmeter.
         */
        steering_wheel_controller_c(int controller_id, hwlib::pin_in &button1,
                                    hwlib::pin_in &button2,
                                    hwlib::pin_in &button3,
                                    hwlib::pin_in &button4, hwlib::adc &wheel,
                                    hwlib::adc &pedals);

        /**
         * This function gets the data of a button.
         *
         *  @param slider - Choose the button you want to get.
         *  @internal Reads the data of the button.
         *  @return the data of the button (type: boolean).
         */
        virtual bool get_button(buttons button) override;

        /**
         * This function gets the data of a slider
         *
         *  @param slider - Choose the slider you want to get.
         *  @internal Reads the data of the slider.
         *  @return the data of the slider (type: uint8_t).
         */
        unsigned char get_slider(sliders slider) override;

        /**
         * This functions gets the data of a joystick
         *
         * @param joystick
         * @return
         */
        virtual joystick_value_c get_joystick(joysticks joystick);

        /**
         * This function is for testing/reading
         * the incoming data of the steering wheel.
         */
        void print();
    };
} // namespace r2d2::manual_control