#pragma once

#include <hwlib.hpp>

namespace r2d2::manual_control {

    /**
     * \brief
     * This class is for reading the data from the steering wheel
     */
    class steering_wheel_controller_c : public hwlib::pin_in {
    private:
        std::array<hwlib::target::pin_in *, 4> buttons;
        std::array<hwlib::target::pin_adc *, 2> sliders;

    public:
        steering_wheel_controller_c(hwlib::target::pin_in &button1,
                                    hwlib::target::pin_in &button2,
                                    hwlib::target::pin_in &button3,
                                    hwlib::target::pin_in &button4,
                                    hwlib::target::pin_adc &wheel,
                                    hwlib::target::pin_adc &pedals);

        /**
         * Refreshes the data of the read buffer and reads the data.
         */
        bool read() override;

        uint8_t get_slider(const int &slider);

        bool get_button(const int &button);

        /**
         * Reads and prints the recieved data from the steering wheel.
         */
        void print();
    };
} // namespace r2d2::manual_control
