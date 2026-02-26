#include <stdio.h>
#include <string.h>
#include "driver/usb_serial_jtag.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "storage.h"
#include "config_storage.h"

#define RX_BUF_SIZE 128

static char device_name[64] = "ESP32-S3-Device"; // Simple device name variable
static char key_name[64] = "key";   // Simple key variable
static int com_freq = 10; // Sensor communication frequency


// ---- Command Handler ----
void handle_command(char *cmd){
    if (strcmp(cmd, "help") == 0) {
        printf("\nAvailable commands:\n");
        printf("help               - Show this message\n");
        printf("name               - Show current device name\n");
        printf("setname <value>    - Set new device name\n\n");
        printf("Setkey <value>    - Set new key value\n\n");
        printf("Setfrequency <value>   - Set new device frequency\n\n");
    }

    else if (strcmp(cmd, "name") == 0) {
        printf("Device name: %s\n", device_name);
    }

    else if (strncmp(cmd, "setname ", 8) == 0) {
        char *new_name = cmd + 8;

        if (strlen(new_name) < sizeof(device_name)) {
            strcpy(device_name, new_name);
            printf("Device name updated to: %s\n", device_name);
        } else {
            printf("Error: name too long (max %d chars)\n",
                   (int)(sizeof(device_name) - 1));
        }
    }
    else if (strncmp(cmd, "setkey ", 7) == 0) {     //setting lora key
        char *new_key = cmd + 7;
        new_key[strcspn(new_key, "\r\n")] = 0;  //trim newline characters

        if (strlen(new_key) < sizeof(key_name)) {
            strcpy(key_name, new_key);

            err = storage.writeValue("lora_key", "key", NvsDataType::STR, &key_name);
            if (err != ESP_OK) {
                printf("ERROR: Failed to write: %d\n", err);
                return;
            }
            printf("LoRa key stored: %s\n ", key_name);
        } else {
            printf("Error: key too long (max %d chars)\n",
                   (int)(sizeof(key_name) - 1));
        }
    }
    else if (strncmp(cmd, "setfrequency ", 13) == 0) {      // set sensor communication frequency
        char *new_freq = cmd + 13;
        new_freq[strcspn(new_freq, "\r\n")] = 0;

        char *end;
        long value = strtol(new_freq, &end, 10);
        if (*end != '\0') {
            printf("Invalid frequency value\n");
            return;
        }
        com_freq = (int)value;

        err = storage.writeValue("com_frequency", "freq", NvsDataType::INT, &com_freq);
        if (err != ESP_OK) {
            printf("ERROR: Failed to write: %d\n", err);
            return;
        }
        printf("Communication frequency stored: %s\n ", com_freq);
    }

    else {
        printf("Unknown command. Type 'help'\n");
    }
}

// ---- USB Console Task ----
void usb_console_task(void *arg){
    char rx_buffer[RX_BUF_SIZE];
    int idx = 0;

    printf("\nUSB Command Interface Ready\n");
    printf("Type 'help'\n\n");

    while (true) {

        uint8_t c;
        int len = usb_serial_jtag_read_bytes(&c, 1, 10 / portTICK_PERIOD_MS);

        if (len > 0) {

            if (c == '\r' || c == '\n') {
                rx_buffer[idx] = '\0';

                if (idx > 0) {
                    handle_command(rx_buffer);
                    idx = 0;
                }
            }
            else {
                if (idx < RX_BUF_SIZE - 1) {
                    rx_buffer[idx++] = c;
                }
            }
        }

        vTaskDelay(1);
    }
}

bool is_usb_connected(void) {
    return usb_serial_jtag_is_connected
    ();
}

extern "C" void app_main(void){

    storage.initNVS();
    loadConfigFromNVS();

    // Install USB Serial JTAG driver
    usb_serial_jtag_driver_config_t config = {1024, 1024}; // rx_buffer_size, tx_buffer_size
    usb_serial_jtag_driver_install(&config);

    xTaskCreate(
        usb_console_task,
        "usb_console",
        4096,
        NULL,
        5,
        NULL
    );
}
