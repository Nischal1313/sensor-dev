#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "nvs_flash.h"
#include "isd-nvs.h"

#include "driver/usb_serial_jtag.h"

#define BUF_SIZE 256

// Persistent variables
char g_dev_eui[32] = {0};
int64_t g_my_int64 = 0;

/* ---------------------------------------------------------- */
/* Load config from NVS */
/* ---------------------------------------------------------- */
void loadConfig()
{
    size_t len;

    len = sizeof(g_dev_eui);
    if (Storage::readValue("config", "dev_eui",
                           NvsDataType::STR,
                           g_dev_eui,
                           &len) != ESP_OK)
    {
        strcpy(g_dev_eui, "not_set");
    }

    if (Storage::readValue("config", "my_int64",
                           NvsDataType::I64,
                           &g_my_int64,
                           nullptr) != ESP_OK)
    {
        g_my_int64 = 0;
    }

    printf("\nLoaded config:\n");
    printf("dev_eui: %s\n", g_dev_eui);
    printf("my_int64: %" PRId64 "\n\n", g_my_int64);
}

/* ---------------------------------------------------------- */
/* Save functions */
/* ---------------------------------------------------------- */
void saveDevEui(const char* value)
{
    strncpy(g_dev_eui, value, sizeof(g_dev_eui) - 1);
    g_dev_eui[sizeof(g_dev_eui) - 1] = '\0';

    Storage::writeValue("config",
                        "dev_eui",
                        NvsDataType::STR,
                        g_dev_eui,
                        0);

    printf("dev_eui saved.\n");
}

void saveInt64(int64_t value)
{
    g_my_int64 = value;

    Storage::writeValue("config",
                        "my_int64",
                        NvsDataType::I64,
                        &g_my_int64,
                        0);

    printf("my_int64 saved.\n");
}


bool processCommand(char* cmd)
{
    cmd[strcspn(cmd, "\r\n")] = 0;

    if (strncmp(cmd, "set-dev ", 8) == 0)
    {
        saveDevEui(cmd + 8);
    }
    else if (strncmp(cmd, "set-int ", 8) == 0)
    {
        int64_t val = atoll(cmd + 8);
        saveInt64(val);
    }
    else if (strcmp(cmd, "show") == 0)
    {
        printf("dev_eui: %s\n", g_dev_eui);
        printf("my_int64: %" PRId64 "\n", g_my_int64);
    }
    else if (strcmp(cmd, "help") == 0)
    {
        printf("\nAvailable commands:\n");
        printf("  set-dev <value>   : Set DevEUI string\n");
        printf("  set-int <value>   : Set int64 value\n");
        printf("  show              : Show current stored values\n");
        printf("  help              : Show this help message\n");
        printf("  end               : Exit console task\n\n");
    }
    else if (strcmp(cmd, "end") == 0)
    {
        printf("Ending command session.\n");
        return false;
    }
    else
    {
        printf("Unknown command.\n");
    }

    return true;
}

void consoleTask(void* arg)
{
    uint8_t rx_byte;
    char line_buffer[BUF_SIZE];
    int index = 0;

    printf("Console ready.\n> ");
    printf("\nAvailable commands:\n");
        printf("  set-dev <value>   : Set DevEUI string\n");
        printf("  set-int <value>   : Set int64 value\n");
        printf("  show              : Show current stored values\n");
        printf("  help              : Show this help message\n");
        printf("  end               : Exit console task\n\n");

    while (true)
    {
        int len = usb_serial_jtag_read_bytes(
            &rx_byte,
            1,
            portMAX_DELAY
        );

        if (len > 0)
        {
            char c = (char)rx_byte;

            // Handle Enter
            if (c == '\r' || c == '\n')
            {
                printf("\r\n");

                line_buffer[index] = '\0';

                if (index > 0)
                {
                    if (!processCommand(line_buffer))
                        break;
                }

                index = 0;
                printf("> ");
            }
            // Handle Backspace
            else if (c == 0x7F || c == 0x08)
            {
                if (index > 0)
                {
                    index--;
                    printf("\b \b");
                }
            }
            // Normal character
            else
            {
                if (index < BUF_SIZE - 1)
                {
                    line_buffer[index++] = c;
                    printf("%c", c);  // echo
                }
            }
        }
    }

    printf("\nConsole task ended.\n");
    vTaskDelete(NULL);
}
/* ---------------------------------------------------------- */
/* app_main */
/* ---------------------------------------------------------- */
extern "C" void app_main(void)
{
    Storage::initNVS();
    loadConfig();

    usb_serial_jtag_driver_config_t config = {1024, 1024};
usb_serial_jtag_driver_install(&config);

    xTaskCreate(consoleTask, "consoleTask", 4096, NULL, 5, NULL);

    // Prevent app_main from returning
    while (true)
    {
        vTaskDelay(portMAX_DELAY);
    }
}