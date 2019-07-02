#this is an easy way of sending pressed keys to an arduino.
#This code is used for demo's to use keyboard input as a controller.
#to use this code, first run the following command:
#pip install -r requirements.txt

from pynput.keyboard import Key, Listener
import serial

ser = serial.Serial('COM2', 9600)  # open serial port
pressedKeys = set()

#if the key wasn't already pressed, output on serial
def on_press(key):
    if key not in pressedKeys:
        ser.write(bytes(str(key), encoding='utf-8'))
    pressedKeys.add(key)

#output key on serial
def on_release(key):
    ser.write(bytes(str(key), encoding='utf-8'))
    pressedKeys.remove(key)

    if key == Key.esc:
        # Stop listener
        return False

# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()


ser.close()             # close port
