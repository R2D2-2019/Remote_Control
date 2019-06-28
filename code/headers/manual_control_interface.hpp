/// This is the first concept version of the manual control interface. 
/// Based upon the research done about other libraries.

#include <stdint.h>

namespace r2d2::manual_control {

    class manualControl_c{

    public:
        /// \brief   
        /// Controller capabilities.
        /// \details
        /// This struct stores the capabilities of the controller. The controller has to set these himself.
        struct Capabilities {
            uint8_t buttonCount;    // holds the amound of buttons the controller has
            bool EAxesLY;           // true if this axes is used, false of not
            bool EAxesRX;           // true if this axes is used, false of not
            bool AxesLX;            // true if this axes is used, false of not
            bool AxesLY;            // true if this axes is used, false of not
            bool AxesRX;            // true if this axes is used, false of not
            bool AxesRY;            // true if this axes is used, false of not
        };

        /// \brief   
        /// The controller state.
        /// \details
        /// This struct stores the state of the controller. The state holds al buttons and axes.
        /// Axes have a range of -127 to 127.
        struct State {
            uint16_t mButtons;  // holds the button states. Each bit corresponds to a button state
            int8_t mEAxesLY;    // Holds the EAxesLY
            int8_t mEAxesRX;    // Holds the EAxesRX
            int8_t mAxesLX;     // Holds the AxesLX
            int8_t mAxesLY;     // Holds the AxesLY
            int8_t mAxesRX;     // Holds the AxesRX
            int8_t mAxesRY;     // Holds the AxesRY
        };

    protected:

        Capabilities capabilities; // default capabillities

        State state = {0, 0, 0, 0, 0, 0, 0}; // default state

    public:

        /// \brief   
        /// Manualcontrol constructor.
        /// \details
        /// This is the constructor for manual control. 
        manualControl_c(
            int8_t buttonCount = 4, 
            bool EAxesLY = 0, 
            bool EAxesRX = 0, 
            bool AxesLX = 1,  
            bool AxesLY = 1, 
            bool AxesRX = 1, 
            bool setAxesRY = 1
        ):
            capabilities{4, 0, 0, 1, 1, 1, 1}
        {}


        /// \brief   
        /// Get controller state
        /// \details
        /// This controller returns the state of the controller. The controller has to update the state himself. 
        /// If this function returns the same values all the time that is a fault on the controller side.
        virtual State getState();

        /// \brief   
        /// Set the state of a single button.
        /// \details
        /// This function sets the state of a single button. If position is more than 15 it will be set at 16.
        void setButton(uint8_t position, bool newState){
            if (position > 15){
                position = 15;
            }

            int16_t mask = 1 << position;

            if(newState){
                state.mButtons |= mask; 
            } else {
                state.mButtons &= ~mask;
            }
        }

        /// \brief   
        /// Set the button state.
        /// \details
        /// This function sets the button state variable of state.
        void setButtons(uint16_t buttons){
            state.mButtons = buttons;
        }

        /// \brief   
        /// Set the EAxesLY.
        /// \details
        /// This function sets the EAxesLY. This axes is an extra axes variable. 
        /// Can be used for trigger buttons, paddles or in combination with EAxesRX for an extra joystick.
        /// Try to match the function to the name. This variable is mend for something on the left or for an y axes.
        void setEAxesLY(int8_t axes){
            state.mEAxesLY = axes;
        }

        /// \brief   
        /// Set the EAxesRX.
        /// \details
        /// This function sets the EAxesRX. This axes is an extra axes variable. 
        /// Can be used for trigger buttons, paddles or in combination with EAxesLY for an extra joystick.
        /// Try to match the function to the name. This variable is mend for something on the right or for an x axes.
        void setEAxesRX(int8_t axes){
            state.mEAxesRX = axes;
        }

        /// \brief   
        /// Set the AxesLX.
        /// \details
        /// This function sets the AxesLX axes.
        /// Try to match the function to the name. This variable is mend for the left x axes.
        void setAxesLX(int8_t axes){
            state.mAxesLX = axes;
        }

        /// \brief   
        /// Set the AxesLY.
        /// \details
        /// This function sets the AxesLY axes.
        /// Try to match the function to the name. This variable is mend for the left y axes.
        void setAxesLY(int8_t axes){
            state.mAxesLY = axes;
        }

        /// \brief   
        /// Set the AxesRX.
        /// \details
        /// This function sets the AxesRX axes.
        /// Try to match the function to the name. This variable is mend for the right x axes.
        void setAxesRX(int8_t axes){
            state.mAxesRX = axes;
        }

        /// \brief   
        /// Set the AxesRY.
        /// \details
        /// This function sets the AxesRY axes.
        /// Try to match the function to the name. This variable is mend for the right y axes.
        void setAxesRY(int8_t axes){
            state.mAxesRY = axes;
        }

        /// \brief   
        /// Get the controller capabilities.
        /// \details
        /// This function returns the controller capabilities.
        virtual Capabilities getCapabilities(){
            return capabilities;
        }

    };
} // namespace r2d2::manual_control