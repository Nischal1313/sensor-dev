#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/usb_serial_jtag.h"
#include "nvs_flash.h"
#include "isd-nvs.h"
#include "console.h"

extern "C" void app_main(void) {
    Storage::initNVS();

    usb_serial_jtag_driver_config_t config = {1024, 1024};
    usb_serial_jtag_driver_install(&config);

    ConsoleTask console;  // runs once, exits if no USB
    // next task here, runs regardless
    
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}