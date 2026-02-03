#include "isd-nvs.h"
#include <cstdio>

// Static member initialization
bool CalibData::nvs_initialized = false;

esp_err_t CalibData::initNVS() {
    // Only initialize once
    if (nvs_initialized) {
        return ESP_OK;
    }

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    
    if (err == ESP_OK) {
        nvs_initialized = true;
    }
    
    return err;
}

esp_err_t CalibData::writeValue(
        const char* ns,
        const char* key,
        NvsDataType type,
        const void* value,
        size_t length)
{
    // Argument validation
    if (!ns || !key || !value) {
        printf("writeValue: Invalid arguments (nullptr)\n");
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t err = initNVS();
    if (err != ESP_OK) {
        printf("Failed to initialize NVS: %d\n", err);
        return err;
    }

    nvs_handle_t handle;
    err = nvs_open(ns, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        printf("Failed to open NVS namespace %s: %d\n", ns, err);
        return err;
    }

    // Switch case to select the correct nvs_set_* call.
    switch (type) {
        case NvsDataType::I8:
            err = nvs_set_i8(handle, key, *reinterpret_cast<const int8_t*>(value));
            break;

        case NvsDataType::U8:
            err = nvs_set_u8(handle, key, *reinterpret_cast<const uint8_t*>(value));
            break;

        case NvsDataType::I16:
            err = nvs_set_i16(handle, key, *reinterpret_cast<const int16_t*>(value));
            break;

        case NvsDataType::U16:
            err = nvs_set_u16(handle, key, *reinterpret_cast<const uint16_t*>(value));
            break;

        case NvsDataType::I32:
            err = nvs_set_i32(handle, key, *reinterpret_cast<const int32_t*>(value));
            break;

        case NvsDataType::U32:
            err = nvs_set_u32(handle, key, *reinterpret_cast<const uint32_t*>(value));
            break;

        case NvsDataType::I64:
            err = nvs_set_i64(handle, key, *reinterpret_cast<const int64_t*>(value));
            break;

        case NvsDataType::U64:
            err = nvs_set_u64(handle, key, *reinterpret_cast<const uint64_t*>(value));
            break;

        case NvsDataType::STR:
            // length can be ignored because nvs_set_str calculates size itself
            err = nvs_set_str(handle, key, reinterpret_cast<const char*>(value));
            break;

        case NvsDataType::BLOB:
            if (length == 0) {
                printf("writeValue: BLOB requires non-zero length\n");
                err = ESP_ERR_INVALID_ARG;
            } else {
                err = nvs_set_blob(handle, key, value, length);
            }
            break;

        default:
            printf("writeValue: Unknown NvsDataType\n");
            err = ESP_ERR_INVALID_ARG;
            break;
    }

    if (err != ESP_OK) {
        printf("Failed to write key %s: %d\n", key, err);
        nvs_close(handle);
        return err;
    }

    // Only commit if write was successful
    err = nvs_commit(handle);
    if (err != ESP_OK) {
        printf("Failed to commit NVS changes for key %s: %d\n", key, err);
    }
    
    nvs_close(handle);
    return err;
}

esp_err_t CalibData::readValue(
        const char* ns,
        const char* key,
        NvsDataType type,
        void* out_value,
        size_t* length)
{
    // Argument validation
    if (!ns || !key || !out_value) {
        printf("readValue: Invalid arguments (nullptr)\n");
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t err = initNVS();
    if (err != ESP_OK) {
        printf("Failed to initialize NVS: %d\n", err);
        return err;
    }

    nvs_handle_t handle;
    err = nvs_open(ns, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        printf("Failed to open NVS namespace %s: %d\n", ns, err);
        return err;
    }

    // For STR/BLOB user must pass length pointer so we know buffer size.
    switch (type) {
        case NvsDataType::I8:
            err = nvs_get_i8(handle, key, reinterpret_cast<int8_t*>(out_value));
            break;

        case NvsDataType::U8:
            err = nvs_get_u8(handle, key, reinterpret_cast<uint8_t*>(out_value));
            break;

        case NvsDataType::I16:
            err = nvs_get_i16(handle, key, reinterpret_cast<int16_t*>(out_value));
            break;

        case NvsDataType::U16:
            err = nvs_get_u16(handle, key, reinterpret_cast<uint16_t*>(out_value));
            break;

        case NvsDataType::I32:
            err = nvs_get_i32(handle, key, reinterpret_cast<int32_t*>(out_value));
            break;

        case NvsDataType::U32:
            err = nvs_get_u32(handle, key, reinterpret_cast<uint32_t*>(out_value));
            break;

        case NvsDataType::I64:
            err = nvs_get_i64(handle, key, reinterpret_cast<int64_t*>(out_value));
            break;

        case NvsDataType::U64:
            err = nvs_get_u64(handle, key, reinterpret_cast<uint64_t*>(out_value));
            break;

        case NvsDataType::STR:
            if (!length) {
                printf("readValue: STR requires length pointer\n");
                err = ESP_ERR_INVALID_ARG;
            } else {
                err = nvs_get_str(handle, key, reinterpret_cast<char*>(out_value), length);
            }
            break;

        case NvsDataType::BLOB:
            if (!length) {
                printf("readValue: BLOB requires length pointer\n");
                err = ESP_ERR_INVALID_ARG;
            } else {
                err = nvs_get_blob(handle, key, out_value, length);
            }
            break;

        default:
            printf("readValue: Unknown NvsDataType\n");
            err = ESP_ERR_INVALID_ARG;
            break;
    }

    if (err != ESP_OK) {
        printf("Failed to read key %s: %d\n", key, err);
    }

    nvs_close(handle);
    return err;
}