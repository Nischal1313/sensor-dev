#include "isd-nvs.h"
#include "esp_log.h"
#include "esp_check.h"
#include <cstdio>
#include <sstream>
#include <iomanip>

NVSStorage::NVSStorage(const char* ns, const char* log_tag) 
    : namespace_name(ns), tag(log_tag), verbose_logging(true) {}

esp_err_t NVSStorage::initNVS() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(tag, "NVS partition was truncated and needs to be erased");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    return err;
}

std::string NVSStorage::valueToString(nvs_type_t type, const void* value) {
    std::ostringstream oss;
    
    switch(type) {
        case NVS_TYPE_I8:
            oss << static_cast<int>(*static_cast<const int8_t*>(value));
            break;
        case NVS_TYPE_U8:
            oss << static_cast<unsigned int>(*static_cast<const uint8_t*>(value));
            break;
        case NVS_TYPE_I16:
            oss << *static_cast<const int16_t*>(value);
            break;
        case NVS_TYPE_U16:
            oss << *static_cast<const uint16_t*>(value);
            break;
        case NVS_TYPE_I32:
            oss << *static_cast<const int32_t*>(value);
            break;
        case NVS_TYPE_U32:
            oss << *static_cast<const uint32_t*>(value);
            break;
        case NVS_TYPE_I64:
            oss << *static_cast<const int64_t*>(value);
            break;
        case NVS_TYPE_U64:
            oss << *static_cast<const uint64_t*>(value);
            break;
        default:
            oss << "Unsupported type: " << type;
            break;
    }
    
    return oss.str();
}


// write Int8

esp_err_t NVSStorage::writeInt8(const char* key, int8_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_i8(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote int8 to NVS %s.%s: %d", 
                 namespace_name, key, static_cast<int>(value));
    }
    
    return err;
}


// write UInt8


esp_err_t NVSStorage::writeUInt8(const char* key, uint8_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_u8(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote uint8 to NVS %s.%s: %u", 
                 namespace_name, key, static_cast<unsigned int>(value));
    }
    
    return err;
}

// write Int16

esp_err_t NVSStorage::writeInt16(const char* key, int16_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_i16(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote int16 to NVS %s.%s: %d", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeUInt16(const char* key, uint16_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_u16(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote uint16 to NVS %s.%s: %u", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeInt32(const char* key, int32_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_i32(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote int32 to NVS %s.%s: %d", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeUInt32(const char* key, uint32_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_u32(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote uint32 to NVS %s.%s: %u", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeInt64(const char* key, int64_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_i64(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote int64 to NVS %s.%s: %lld", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeUInt64(const char* key, uint64_t value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_u64(handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote uint64 to NVS %s.%s: %llu", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeFloat(const char* key, float value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    // Store as blob to preserve exact binary representation
    err = nvs_set_blob(handle, key, &value, sizeof(float));
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write float to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote float to NVS %s.%s: %.6f", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeDouble(const char* key, double value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    // Store as blob to preserve exact binary representation
    err = nvs_set_blob(handle, key, &value, sizeof(double));
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write double to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote double to NVS %s.%s: %.10lf", 
                 namespace_name, key, value);
    }
    
    return err;
}

esp_err_t NVSStorage::writeString(const char* key, const std::string& value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_str(handle, key, value.c_str());
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write string to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote string to NVS %s.%s: %s", 
                 namespace_name, key, value.c_str());
    }
    
    return err;
}

esp_err_t NVSStorage::writeBlob(const char* key, const void* data, size_t length) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    if (data == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to write NULL data!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_set_blob(handle, key, data, length);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to write blob to NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully wrote blob to NVS %s.%s (%zu bytes)", 
                 namespace_name, key, length);
    }
    
    return err;
}

esp_err_t NVSStorage::readInt8(const char* key, int8_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_i8(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read int8 from NVS %s.%s: %d", 
                 namespace_name, key, static_cast<int>(out_value));
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t NVSStorage::readUInt8(const char* key, uint8_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_u8(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read uint8 from NVS %s.%s: %u", 
                 namespace_name, key, static_cast<unsigned int>(out_value));
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t NVSStorage::readInt16(const char* key, int16_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_i16(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read int16 from NVS %s.%s: %d", 
                 namespace_name, key, out_value);
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t NVSStorage::readUInt16(const char* key, uint16_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_u16(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read uint16 from NVS %s.%s: %u", 
                 namespace_name, key, out_value);
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t NVSStorage::readInt32(const char* key, int32_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_i32(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read int32 from NVS %s.%s: %d", 
                 namespace_name, key, out_value);
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}


esp_err_t NVSStorage::readUInt32(const char* key, uint32_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_u32(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read uint32 from NVS %s.%s: %u", 
                 namespace_name, key, out_value);
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}


esp_err_t NVSStorage::readInt64(const char* key, int64_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_i64(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read int64 from NVS %s.%s: %lld", 
                 namespace_name, key, out_value);
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t NVSStorage::readUInt64(const char* key, uint64_t& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_get_u64(handle, key, &out_value);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read uint64 from NVS %s.%s: %llu", 
                 namespace_name, key, out_value);
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}


esp_err_t NVSStorage::readFloat(const char* key, float& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    size_t length = sizeof(float);
    err = nvs_get_blob(handle, key, &out_value, &length);
    nvs_close(handle);
    
    if (err == ESP_OK) {
        if (length != sizeof(float)) {
            ESP_LOGE(tag, "Invalid float size in NVS %s.%s: expected %zu, got %zu", 
                     namespace_name, key, sizeof(float), length);
            return ESP_ERR_INVALID_SIZE;
        }
        if (verbose_logging) {
            ESP_LOGI(tag, "Successfully read float from NVS %s.%s: %.6f", 
                     namespace_name, key, out_value);
        }
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}


esp_err_t NVSStorage::readDouble(const char* key, double& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    size_t length = sizeof(double);
    err = nvs_get_blob(handle, key, &out_value, &length);
    nvs_close(handle);
    
    if (err == ESP_OK) {
        if (length != sizeof(double)) {
            ESP_LOGE(tag, "Invalid double size in NVS %s.%s: expected %zu, got %zu", 
                     namespace_name, key, sizeof(double), length);
            return ESP_ERR_INVALID_SIZE;
        }
        if (verbose_logging) {
            ESP_LOGI(tag, "Successfully read double from NVS %s.%s: %.10lf", 
                     namespace_name, key, out_value);
        }
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
    } else {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t NVSStorage::readString(const char* key, std::string& out_value) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    // Get required size
    size_t required_size = 0;
    err = nvs_get_str(handle, key, nullptr, &required_size);
    if (err != ESP_OK) {
        nvs_close(handle);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
        } else {
            ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                     namespace_name, key, esp_err_to_name(err));
        }
        return err;
    }
    
    // Resize string and read
    out_value.resize(required_size);
    err = nvs_get_str(handle, key, &out_value[0], &required_size);
    nvs_close(handle);
    
    if (err == ESP_OK) {
        // Remove null terminator from string
        if (required_size > 0) {
            out_value.resize(required_size - 1);
        }
        if (verbose_logging) {
            ESP_LOGI(tag, "Successfully read string from NVS %s.%s: %s", 
                     namespace_name, key, out_value.c_str());
        }
    } else {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

esp_err_t NVSStorage::readBlob(const char* key, std::vector<uint8_t>& out_data) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to read value: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    // Get required size
    size_t required_size = 0;
    err = nvs_get_blob(handle, key, nullptr, &required_size);
    if (err != ESP_OK) {
        nvs_close(handle);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            ESP_LOGW(tag, "Value %s.%s is not initialized yet", namespace_name, key);
        } else {
            ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                     namespace_name, key, esp_err_to_name(err));
        }
        return err;
    }
    
    // Resize vector and read
    out_data.resize(required_size);
    err = nvs_get_blob(handle, key, out_data.data(), &required_size);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully read blob from NVS %s.%s (%zu bytes)", 
                 namespace_name, key, required_size);
    } else if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to read from NVS %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
    }
    
    return err;
}

int8_t NVSStorage::readInt8(const char* key, int8_t default_value) {
    int8_t value;
    return (readInt8(key, value) == ESP_OK) ? value : default_value;
}

uint8_t NVSStorage::readUInt8(const char* key, uint8_t default_value) {
    uint8_t value;
    return (readUInt8(key, value) == ESP_OK) ? value : default_value;
}

int16_t NVSStorage::readInt16(const char* key, int16_t default_value) {
    int16_t value;
    return (readInt16(key, value) == ESP_OK) ? value : default_value;
}

uint16_t NVSStorage::readUInt16(const char* key, uint16_t default_value) {
    uint16_t value;
    return (readUInt16(key, value) == ESP_OK) ? value : default_value;
}

int32_t NVSStorage::readInt32(const char* key, int32_t default_value) {
    int32_t value;
    return (readInt32(key, value) == ESP_OK) ? value : default_value;
}

uint32_t NVSStorage::readUInt32(const char* key, uint32_t default_value) {
    uint32_t value;
    return (readUInt32(key, value) == ESP_OK) ? value : default_value;
}

int64_t NVSStorage::readInt64(const char* key, int64_t default_value) {
    int64_t value;
    return (readInt64(key, value) == ESP_OK) ? value : default_value;
}

uint64_t NVSStorage::readUInt64(const char* key, uint64_t default_value) {
    uint64_t value;
    return (readUInt64(key, value) == ESP_OK) ? value : default_value;
}

float NVSStorage::readFloat(const char* key, float default_value) {
    float value;
    return (readFloat(key, value) == ESP_OK) ? value : default_value;
}

double NVSStorage::readDouble(const char* key, double default_value) {
    double value;
    return (readDouble(key, value) == ESP_OK) ? value : default_value;
}


// utility methods


bool NVSStorage::exists(const char* key) {
    if (key == nullptr) {
        return false;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    if (nvs_open(namespace_name, NVS_READONLY, &handle) != ESP_OK) {
        return false;
    }
    
    // Try to get the key - if it exists, this will succeed
    size_t length = 0;
    esp_err_t err = nvs_get_blob(handle, key, nullptr, &length);
    
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        int32_t temp;
        err = nvs_get_i32(handle, key, &temp);
    }
    
    nvs_close(handle);
    return (err == ESP_OK || err == ESP_ERR_NVS_INVALID_LENGTH);
}

esp_err_t NVSStorage::erase(const char* key) {
    if (key == nullptr) {
        ESP_LOGE(tag, "%s(): Failed to erase: key is NULL!", __func__);
        return ESP_ERR_INVALID_ARG;
    }
    
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_erase_key(handle, key);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to erase key %s.%s: %s", 
                 namespace_name, key, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully erased key %s.%s", namespace_name, key);
    }
    
    return err;
}

esp_err_t NVSStorage::eraseAll() {
    initNVS();
    
    nvs_handle_t handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "%s(): Error opening NVS namespace %s: %s", 
                 __func__, namespace_name, esp_err_to_name(err));
        return err;
    }
    
    err = nvs_erase_all(handle);
    if (err != ESP_OK) {
        ESP_LOGE(tag, "Failed to erase all in namespace %s: %s", 
                 namespace_name, esp_err_to_name(err));
        nvs_close(handle);
        return err;
    }
    
    err = nvs_commit(handle);
    nvs_close(handle);
    
    if (err == ESP_OK && verbose_logging) {
        ESP_LOGI(tag, "Successfully erased all data in namespace %s", namespace_name);
    }
    
    return err;
}