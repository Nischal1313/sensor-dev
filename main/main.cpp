#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "esp_system.h"
#include "nvs_flash.h"
#include "isd-nvs.h"

#include "driver/usb_serial_jtag.h"


#define BUF_SIZE 256
#define IDLE_TIMEOUT_MS 60000 //60seconds

// Persistent variables
char g_app_key[32] = {0};
uint8_t g_com_freq = 0;

static TimerHandle_t idleTimer = NULL;
static TaskHandle_t consoleTaskHandle = NULL;

void idle_timeout_callback(TimerHandle_t xTimer) {
    printf("\nNo ENTER pressed for 60 seconds\n");
    if (consoleTaskHandle != NULL) {
        xTaskNotify(consoleTaskHandle, 1, eSetValueWithOverwrite);
    }
}

/* ---------------------------------------------------------- */
/* Load config from NVS */
/* ---------------------------------------------------------- */
void loadConfig() {
    size_t len;

    len = sizeof(g_app_key);
    if (Storage::readValue("config", "appkey",
                           NvsDataType::STR,
                           g_app_key,
                           &len) != ESP_OK) {
        strcpy(g_app_key, "not_set");
    }

    if (Storage::readValue("config", "comfreq",
                           NvsDataType::I64,
                           &g_com_freq,
                           nullptr) != ESP_OK) {
        g_com_freq = 0;
    }

    printf("\nLoaded config:\n");
    printf("app key: %s\n", g_app_key);
    printf("communication frequency: %" PRId8 "\n\n", g_com_freq);
}

/* ---------------------------------------------------------- */
/* Save functions */
/* ---------------------------------------------------------- */
void saveAppKey(const char *value) {
    strncpy(g_app_key, value, sizeof(g_app_key) - 1);
    g_app_key[sizeof(g_app_key) - 1] = '\0';

    Storage::writeValue("config",
                        "appkey",
                        NvsDataType::STR,
                        g_app_key,
                        0);

    printf("app key saved.\n");
}

void saveFreq(uint8_t value) {
    g_com_freq = value;

    Storage::writeValue("config",
                        "comfreq",
                        NvsDataType::I64,
                        &g_com_freq,
                        0);

    printf("frequency saved.\n");
}


bool processCommand(char *cmd) {
    cmd[strcspn(cmd, "\r\n")] = 0;

    if (strncmp(cmd, "set-appkey ", 10) == 0) {
        long len = strlen(cmd);
        if (len == 32) {
            saveAppKey(cmd + 10);
        } else {
            printf("Invalid key \n");
        }
    } else if (strncmp(cmd, "set-freq ", 8) == 0) {
        char *end;
        long val = strtol(cmd + 8, &end, 10);
        if (end == cmd + 8 || *end != '\0' || val < 0 || val > 255) {
            // input validation
            printf("Invalid input\n");
        } else {
            saveFreq(val);
        }

    } else if (strcmp(cmd, "show") == 0) {
        printf("app key: %s\n", g_app_key);
        printf("communication frequency: %" PRId8 " minutes\n", g_com_freq);
    } else if (strcmp(cmd, "help") == 0) {
        printf("\nAvailable commands:\n");
        printf("  set-appkey <value>    : Set appkey string\n");
        printf("  set-freq <value>   : Set communication frequency (in minutes)\n");
        printf("  show               : Show current stored values\n");
        printf("  help               : Show this help message\n");
        printf("  end                : Exit console task\n\n");
    } else if (strcmp(cmd, "end") == 0) {
        printf("Ending command session.\n");
        return false;
    } else {
        printf("Unknown command.\n");
    }

    return true;
}

void consoleTask(void *arg) {
    uint32_t notif;

    uint8_t rx_byte;
    char line_buffer[BUF_SIZE];
    int index = 0;

    printf("Console ready.\n> ");
    printf("\nAvailable commands:\n");
    printf("  set-appkey <value>    : Set appkey string\n");
    printf("  set-freq <value>      : Set communication frequency (in minutes)\n");
    printf("  show                  : Show current stored values\n");
    printf("  help                  : Show this help message\n");
    printf("  end                   : Exit console task\n\n");

    while (true) {
        if (xTaskNotifyWait(0, 0, &notif, 0) == pdTRUE) {
            printf("Console timeout\n");
            break;
        }

        int len = usb_serial_jtag_read_bytes(
            &rx_byte,
            1,
            pdMS_TO_TICKS(100)
        );

        if (len > 0) {
            char c = (char) rx_byte;

            // Handle Enter
            if (c == '\r' || c == '\n') {
                printf("\r\n");

                line_buffer[index] = '\0';

                if (index > 0) {
                    if (!processCommand(line_buffer))
                        break;
                }

                index = 0;
                printf("> ");
                xTimerReset(idleTimer, 0);
            }
            // Handle Backspace
            else if (c == 0x7F || c == 0x08) {
                if (index > 0) {
                    index--;
                    printf("\b \b");
                }
            }
            // Normal character
            else {
                if (index < BUF_SIZE - 1) {
                    line_buffer[index++] = c;
                    printf("%c", c); // echo
                }
            }
        }
    }

    printf("\nConsole task ended.\n");
    xTimerStop(idleTimer, 0);
    vTaskDelete(NULL);
}

/* ---------------------------------------------------------- */
/* app_main */
/* ---------------------------------------------------------- */
extern "C" void app_main(void) {
    Storage::initNVS();
    loadConfig();

    usb_serial_jtag_driver_config_t config = {1024, 1024};
    usb_serial_jtag_driver_install(&config);

    xTaskCreate(consoleTask, "consoleTask", 4096, NULL, 5, &consoleTaskHandle);

    idleTimer = xTimerCreate(
        "IdleTimer", pdMS_TO_TICKS(IDLE_TIMEOUT_MS), pdFALSE, NULL, idle_timeout_callback);

    xTimerStart(idleTimer, 0);

    // Prevent app_main from returning
    while (true) {
        vTaskDelay(portMAX_DELAY);
    }
}
