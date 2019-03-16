#include "usb_controller.hpp"

void usb_controller::init_controller() {
    int return_value;
    return_value = libusb_init(&ctx);
    if (return_value < 0) {
        std::cout << "Init Error" << return_value << std::endl;
        exit_context();
        context_exited = true;
        return;
    }
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);
    count = libusb_get_device_list(ctx, &devs);
    if (count < 0) {
        std::cout << "Get Device Error" << std::endl;
        free_device_list();
        exit_context();
        device_list_freed = true;
        context_exited = true;
        return;
    }
    std::cout << count << " devices in list" << std::endl;
    if (set_usb_index()) {
        no_index = false;
        std::cout << "Got Index" << std::endl;
    } else {
        no_index = true;
        std::cout << "Failed To Get Index" << std::endl;
        free_device_list();
        exit_context();
        device_list_freed = true;
        context_exited = true;
        return;
    }
    std::cout << "Controller @[" << usb_index << "]" << std::endl;
    controller = devs[usb_index];
    if (!claim_interface()) {
        close_device_handle();
        free_device_list();
        exit_context();
        handle_closed = true;
        device_list_freed = true;
        context_exited = true;
        return;
    }
    std::cout << "Init complete" << std::endl;
}

bool usb_controller::set_usb_index() {
    libusb_device *dev;
    int i = 0;
    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int return_value = libusb_get_device_descriptor(dev, &desc);
        if (return_value < 0) {
            std::cout << "Failed to get device descriptor" << std::endl;
            return false;
        }
        if (desc.idVendor == vendor_id && desc.idProduct == product_id) {
            usb_index = i - 1;
            return true;
        }
    }
    return false;
}

bool usb_controller::claim_interface() {
    libusb_device_handle *dev_handle;
    int return_value = libusb_open(controller, &dev_handle);
    if (dev_handle == NULL) {
        std::cout << "Cannot open device" << std::endl;
    } else {
        std::cout << "Device opened" << std::endl;
    }
    device_handle = dev_handle;

    buffer_size = libusb_get_max_packet_size(controller, endpoint_address);
    std::cout << "Packet size:\t" << buffer_size << std::endl;

    if (libusb_kernel_driver_active(dev_handle, 0) == 1) {
        std::cout << "Kernel driver active" << std::endl;
        if (libusb_kernel_driver_active(dev_handle, 0) == 0) {
            std::cout << "Kernel driver detached" << std::endl;
        }
    }
    return_value = libusb_claim_interface(dev_handle, 0);
    if (return_value < 0) {
        std::cout << "Cannot claim interface" << std::endl;
        return false;
    }
    std::cout << "Claimed interface!" << std::endl;
    return true;
}

void usb_controller::close_device_handle() {
    libusb_close(device_handle);
    std::cout << "Handle Closed" << std::endl;
}

void usb_controller::free_device_list() {
    libusb_free_device_list(devs, 1);
    std::cout << "Freeing Device Complete" << std::endl;
}

void usb_controller::exit_context() {
    libusb_exit(ctx);
    std::cout << "Exit Context Complete" << std::endl;
}

bool usb_controller::controller_exist() {
    return !no_index;
}

std::vector<unsigned char> usb_controller::get_controller_output() {
    if (!no_index) {
        unsigned char controller_input[buffer_size];
        int return_value = libusb_bulk_transfer(device_handle, endpoint_address,
                                                controller_input, buffer_size,
                                                &input_data_size, 0);
        if (!(return_value == 0 &&
              input_data_size == static_cast<int>(buffer_size))) {
            std::cout << "Read error" << std::endl;
        } else {
            for (unsigned int i = 0; i < buffer_size; i++) {
                input_vector[i] = controller_input[i];
            }
        }
    }
    return input_vector;
}
