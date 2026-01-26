#include "nvs_flash.h"
#include "nvs.h"
#include <stdio.h>
#include "esp_system.h"

void app_main(void) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Open NVS namespace "storage" in read/write mode
    nvs_handle_t my_handle;
    ret = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (ret != ESP_OK) {
        printf("Error opening NVS handle!\n");
        return;
    }

    // Write a small string value
    const char* test_value = "HelloNVS";
    ret = nvs_set_str(my_handle, "my_key", test_value);
    if (ret != ESP_OK) {
        printf("Error writing to NVS!\n");
        nvs_close(my_handle);
        return;
    }

    // Commit the changes to flash
    ret = nvs_commit(my_handle);
    if (ret != ESP_OK) {
        printf("Error committing NVS changes!\n");
        nvs_close(my_handle);
        return;
    }

    printf("Write successful!\n");

    // Read the value back
    size_t required_size = 0;
    ret = nvs_get_str(my_handle, "my_key", NULL, &required_size);
    if (ret != ESP_OK || required_size == 0) {
        printf("Error reading NVS!\n");
        nvs_close(my_handle);
        return;
    }

    char read_value[required_size];
    ret = nvs_get_str(my_handle, "my_key", read_value, &required_size);
    if (ret == ESP_OK) {
        printf("Read back from NVS: %s\n", read_value);
    } else {
        printf("Error reading NVS!\n");
    }

    nvs_close(my_handle);
}
