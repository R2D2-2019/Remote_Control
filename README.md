# Remote_Control
## From Arduino  to PC
If you want to send values from the Arduino Due to the PC, then you must send a ```-``` character after each value. After the last value you need to send use ```hwlib::endl```. Here are some examples of how to send values to the PC:
```c++
// Single value
hwlib::cout << 33 << '-' << hwlib::endl;
```
```c++
// Multiple values
hwlib::cout << 33 << '-' << 42 << '-' << hwlib::endl;
```
```c++
// Array of values
unsigned char byte_array[] = {0, 1, 2, 4, 8, 16, 32, 64};
for (unsigned int i = 0; i < 8; i++) {
    hwlib::cout << byte_array[i] << '-';
}
hwlib::cout << hwlib::endl;
```
To receive values from the Arduino, you use the ```serial_read()``` function. Here is an example of receiving values at the PC:
```c++
const char* port = "\\\\.\\COM2";
r2d2::remote_control::serial_arduino_c arduino(port, 16);
std::vector<unsigned char> input;

input = arduino.serial_read();
```
## From PC to Arduino
To write values to the Arduino, you use ```serial_write()```:
```c++
const char* port = "\\\\.\\COM2";
r2d2::remote_control::serial_arduino_c arduino(port, 16);
std::array<unsigned char, 4> output = {42, 33, 12, 4};

arduino.serial_write<4>(output);
```