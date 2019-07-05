#pragma once

#include <hwlib.hpp>

#include "manual_control_interface.hpp"

namespace r2d2::manual_control {

    /**
     * Class steering_wheel_controller_c provides functions
     * for reading the data of the trust steering wheel.
     */
    class steering_wheel_controller_c : public manualControl_c {
    private:
        std::array<hwlib::target::pin_in *, 4> buttons;
        std::array<hwlib::target::pin_adc *, 2> sliders;

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
        steering_wheel_controller_c(hwlib::target::pin_in &button1,
                                    hwlib::target::pin_in &button2,
                                    hwlib::target::pin_in &button3,
                                    hwlib::target::pin_in &button4,
                                    hwlib::target::pin_adc &wheel,
                                    hwlib::target::pin_adc &pedals);

        /**
         * This function overrides the read() function of pin_in
         * and reads the data of a pin_in.
         *
         * @internal refreshes/reads the incoming data.
         */
        // bool read() override;

        /**
         * This function gets the data of a slider
         *
         *  @param slider - Choose the slider you want to get.
         *  @internal Reads the data of the slider.
         *  @return the data of the slider (type: uint8_t).
         */
        int8_t get_slider(const int &slider);

        /**
         * This function gets the data of a button.
         *
         *  @param slider - Choose the button you want to get.
         *  @internal Reads the data of the button.
         *  @return the data of the button (type: boolean).
         */
        bool get_button(const int &button);

        /**
         * This function is for testing/reading
         * the incoming data of the steering wheel.
         */
        void print();

        /**
         * \brief
         * override function of get state.
         * \detailed
         * This overrides the get_state function so that the state first gets
         * set and than returned.
         * @return state_s m_state - the state of the controller.
         */
        state_s get_state() override;
    };
} // namespace r2d2::manual_control
