#include "device/device_setup.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "tasks.h"



#if 0

#endif

extern "C" void app_main(void)
{
    if (!uart_init()) {
        ESP_LOGE("MAIN", "UART init failed");
        return;
    }

    xTaskCreate(uart_task, "uart_task", 4096, nullptr, 10, nullptr);

}
