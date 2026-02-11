#include <stdio.h>
#include <stdbool.h>
#include "driver/usb_serial_jtag.h"
#include "sdkconfig.h"
#include "freertos/task.h"
#include "freertos/FreeRTOS.h"


bool is_usb_connected(void) {
    return usb_serial_jtag_is_connected();

while (true) {
    printf("usb connection status: %d\n", usb_serial_jtag_is_connected() ? 1 : 0);
    vTaskDelay(1000);
}