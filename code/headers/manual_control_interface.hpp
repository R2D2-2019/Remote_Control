/// This is the second concept version of the manual control interface.
/// Based upon the research done about other libraries.

#include <stdint.h>

namespace r2d2::manual_control {

    /**
     * \brief
     * Controller capabilities.
     * \details
     * This struct stores the capabilities of the controller. The controller has
     * to set these himself.
     */
    struct capabilities_s {
        uint8_t button_count; // holds the amound of buttons the controller has
        bool e_axes_ly;       // true if this axes is used, false or not
        bool e_axes_rx;       // true if this axes is used, false or not
        bool axes_lx;         // true if this axes is used, false or not
        bool axes_ly;         // true if this axes is used, false or not
        bool axes_rx;         // true if this axes is used, false or not
        bool axes_ry;         // true if this axes is used, false or not
    };

    /**
     * \brief
     * The controller m_state.
     * \details
     * This struct stores the state of the controller. The state holds al
     * buttons and axes. Axes have a range of -127 to 127.
     */
    struct state_s {
        uint16_t buttons; // holds the button states. Each bit corresponds to a
                          // button state
        int8_t e_axes_ly; // Holds the EAxesLY
        int8_t e_axes_rx; // Holds the EAxesRX
        int8_t axes_lx;   // Holds the AxesLX
        int8_t axes_ly;   // Holds the AxesLY
        int8_t axes_rx;   // Holds the AxesRX
        int8_t axes_ry;   // Holds the AxesRY
    };

    /**
     * \brief
     * print operator for state_s.
     * \details
     * This operator enables to cout a state_s variable.
     */
    template <class T>
    T &operator<<(T &os, const state_s &s) {
        os << "buttons: " << s.buttons << "\n";
        os << "axes_lx: " << s.axes_lx << "\n";
        os << "axes_ly: " << s.axes_ly << "\n";
        os << "axes_rx: " << s.axes_rx << "\n";
        os << "axes_ry: " << s.axes_ry << "\n";
        os << "e_axes_ly: " << s.e_axes_ly << "\n";
        os << "e_axes_rx: " << s.e_axes_rx << "\n";
        return os;
    }

    class manualControl_c {
    protected:
        capabilities_s m_capabilities; // default capabillities

        state_s m_state = {0, 0, 0, 0, 0, 0, 0}; // default state

    public:
        /**
         * \brief
         * Manualcontrol constructor.
         * \details
         * This is the constructor for manual control.
         */
        manualControl_c(uint8_t button_count = 4, bool e_axes_ly = 0,
                        bool e_axes_rx = 0, bool axes_lx = 1, bool axes_ly = 1,
                        bool axes_rx = 1, bool axes_ry = 1)
            : m_capabilities{button_count, e_axes_ly, e_axes_rx, axes_lx,
                             axes_ly,      axes_rx,   axes_ry} {
        }

        /**
         * \brief
         * Get controller state
         * \details
         * This controller returns the state of the controller. The controller
         * has to update the state himself. If this function returns the same
         * values all the time that is a fault on the controller side.
         * @return state_s - the state of the controller.
         */
        virtual state_s get_state();

        /**
         * \brief
         * Set the state of a single button.
         * \details
         * This function sets the state of a single button. If position is more
         * than 15 it will be set at 16.
         * @param uint8_t position - the position of the of the bit to set.
         * @param bool new_state - the value to set.
         */
        void set_button(uint8_t position, bool new_state) {
            if (position > 15) {
                position = 15;
            }

            int16_t mask = 1 << position;

            if (new_state) {
                m_state.buttons |= mask;
            } else {
                m_state.buttons &= ~mask;
            }
        }

        /**
         * \brief
         * Set the button state.
         * \details
         * This function sets the button state variable of state.
         * @param uint16_t buttons - the value to set.
         */
        void set_buttons(uint16_t buttons) {
            m_state.buttons = buttons;
        }

        /**
         * \brief
         * Set the EAxesLY.
         * \details
         * This function sets the EAxesLY. This axes is an extra axes variable.
         * Can be used for trigger buttons, paddles or in combination with
         * EAxesRX for an extra joystick. Try to match the function to the name.
         * This variable is mend for something on the left or for an y axes.
         * @param int8_t axes - the new axes value to set.
         */
        void set_e_axes_ly(int8_t axes) {
            m_state.e_axes_ly = axes;
        }

        /**
         * \brief
         * Set the EAxesRX.
         * \details
         * This function sets the EAxesRX. This axes is an extra axes variable.
         * Can be used for trigger buttons, paddles or in combination with
         * EAxesLY for an extra joystick. Try to match the function to the name.
         * This variable is mend for something on the right or for an x axes.
         * @param int8_t axes - the new axes value to set.
         */
        void set_e_axes_rx(int8_t axes) {
            m_state.e_axes_rx = axes;
        }

        /**
         * \brief
         * Set the AxesLX.
         * \details
         * This function sets the AxesLX axes.
         * Try to match the function to the name. This variable is mend for the
         * left x axes.
         * @param int8_t axes - the new axes value to set.
         */
        void set_axes_lx(int8_t axes) {
            m_state.axes_lx = axes;
        }

        /** \brief
         * Set the AxesLY.
         * \details
         * This function sets the AxesLY axes.
         * Try to match the function to the name. This variable is mend for the
         * left y axes.
         * @param int8_t axes - the new axes value to set.
         */
        void set_axes_ly(int8_t axes) {
            m_state.axes_ly = axes;
        }

        /** \brief
         * Set the AxesRX.
         * \details
         * This function sets the AxesRX axes.
         * Try to match the function to the name. This variable is mend for the
         * right x axes.
         * @param int8_t axes - the new axes value to set.
         */
        void set_axes_rx(int8_t axes) {
            m_state.axes_rx = axes;
        }

        /** \brief
         * Set the AxesRY.
         * \details
         * This function sets the AxesRY axes.
         * Try to match the function to the name. This variable is mend for the
         * right y axes.
         * @param int8_t axes - the new axes value to set.
         */
        void set_axes_ry(int8_t axes) {
            m_state.axes_ry = axes;
        }

        /** \brief
         * Get the controller capabilities.
         * \details
         * This function returns the controller capabilities.
         * @return capabilities_s m_capabilities - this are the capabilities of
         * the controller.
         */
        capabilities_s get_capabilities() {
            return m_capabilities;
        }
    };
} // namespace r2d2::manual_control