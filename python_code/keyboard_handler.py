#this is an easy way of sending pressed keys to an arduino.
#This code is used for demo's to use keyboard input as a controller.
#to use this code, first run the following command:
#pip install -r requirements.txt

from pynput.keyboard import Key, Listener, KeyCode
import serial
import numpy as np

ser = serial.Serial('COM2', 2400)  # open serial port
ser.write(0b00010000)


controller_state = np.uint8(0)
#if the key wasn't already pressed, output on serial
def on_press(key):
    global controller_state
    print(key)
    preState = controller_state

    if key.char == 'a' or key.char == 'A':
        controller_state = controller_state | 0b0000001

    if key.char == 'd' or key.char == 'D':
        controller_state = controller_state | 0b0000010

    if key.char == 'w' or key.char == 'W':
        controller_state = controller_state | 0b0000100

    if key.char == 's' or key.char == 'S':
        controller_state = controller_state | 0b0001000

    if preState != controller_state:
        ser.write(bytes(str(controller_state), encoding='utf-8'))

#output key on serial
def on_release(key):
    global controller_state

    if key.char == 'a' or key.char == 'A':
        controller_state = controller_state & 0b1111110

    if key.char == 'd' or key.char == 'D':
        controller_state = controller_state & 0b11111101

    if key.char == 'w' or key.char == 'W':
        controller_state = controller_state & 0b11111011

    if key.char == 's' or key.char == 'S':
        controller_state = controller_state & 0b11110111

    ser.write(bytes(str(controller_state), encoding='utf-8'))

# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()


ser.close()             # close port
