#include "nvs_flash.h"
#include "nvs.h"
#include <string>
#include <stdio.h>
#include "esp_system.h"

extern "C" void app_main() {
    // Initialize NVS (must always do this at startup)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Open the NVS namespace "storage" in read-only mode
    nvs_handle_t my_handle;
    ret = nvs_open("storage", NVS_READONLY, &my_handle);
    if (ret != ESP_OK) {
        printf("Error opening NVS handle!\n");
        return;
    }

    // Read the previously stored string
    size_t required_size = 0;
    ret = nvs_get_str(my_handle, "my_key", nullptr, &required_size);
    if (ret != ESP_OK || required_size == 0) {
        printf("No value found in NVS!\n");
        nvs_close(my_handle);
        return;
    }

    char* read_value = new char[required_size];
    ret = nvs_get_str(my_handle, "my_key", read_value, &required_size);
    if (ret == ESP_OK) {
        printf("Read from NVS after power cycle: %s\n", read_value);
    } else {
        printf("Error reading NVS!\n");
    }

    delete[] read_value;
    nvs_close(my_handle);
}
