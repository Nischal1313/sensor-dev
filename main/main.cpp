#pragma once
#include "nvs_flash.h"
#include "nvs.h"
#include <string>
#include "esp_log.h"

class NVSUtility {
public:
    NVSUtility(const char* namespace_name = "storage")
        : ns(namespace_name) {}

    void init() {
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);
    }

    bool writeStr(const char* key, const char* value) {
        nvs_handle_t handle;
        esp_err_t ret = nvs_open(ns, NVS_READWRITE, &handle);
        if (ret != ESP_OK) return false;

        ret = nvs_set_str(handle, key, value);
        if (ret == ESP_OK) nvs_commit(handle);

        nvs_close(handle);
        return ret == ESP_OK;
    }

    std::string readStr(const char* key) {
        nvs_handle_t handle;
        esp_err_t ret = nvs_open(ns, NVS_READONLY, &handle);
        if (ret != ESP_OK) return "";

        size_t required_size = 0;
        ret = nvs_get_str(handle, key, nullptr, &required_size);
        if (ret != ESP_OK || required_size == 0) {
            nvs_close(handle);
            return "";
        }

        char* buf = new char[required_size];
        ret = nvs_get_str(handle, key, buf, &required_size);
        std::string value;
        if (ret == ESP_OK) value = std::string(buf);
        delete[] buf;
        nvs_close(handle);
        return value;
    }

private:
    const char* ns;
};
