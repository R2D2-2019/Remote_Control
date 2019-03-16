#pragma once

#include <bitset>
#include <iostream>
#include <libusb.h>
#include <vector>

class usb_controller {
private:
    unsigned int buffer_size;
    unsigned int endpoint_address;
    unsigned int usb_index;
    bool no_index = true;
    bool device_list_freed = false;
    bool context_exited = false;
    bool handle_closed = false;
    uint16_t vendor_id;
    uint16_t product_id;
    int input_data_size;
    libusb_device **devs;
    libusb_device *controller;
    libusb_context *ctx = NULL;
    libusb_device_handle *device_handle;
    ssize_t count;
    std::vector<unsigned char> input_vector;

    void init_controller();
    bool set_usb_index();
    bool claim_interface();
    void free_device_list();
    void exit_context();
    void close_device_handle();

public:
    usb_controller(unsigned int endpoint, uint16_t vendor_id,
                   uint16_t product_id)
        : endpoint_address(endpoint),
          vendor_id(vendor_id),
          product_id(product_id) {
        init_controller();
        input_vector.assign(buffer_size, 0);
    }
    ~usb_controller() {
        if (!no_index) {
            if (!handle_closed) {
                close_device_handle();
            }
        }
        if (!device_list_freed) {
            free_device_list();
        }
        if (!context_exited) {
            exit_context();
        }
    }
    std::vector<unsigned char> get_controller_output();
    bool controller_exist();
};