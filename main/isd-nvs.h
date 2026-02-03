#ifndef STORAGE_H
#define STORAGE_H

#include "nvs_flash.h"
#include "nvs.h"

// Supported data types for read/write.
// These directly map to NVS typed APIs.
enum class NvsDataType {
    I8,
    U8,
    I16,
    U16,
    I32,
    U32,
    I64,
    U64,
    STR,
    BLOB
};

// Constants for data sizes
#define STATE_BUFFER_SIZE 197
#define LORA_KEY_SIZE 17

class Storage {
public:

    // Initializes NVS flash (erase if corrupted newer/older version detected).
    // This is called automatically by writeValue/readValue, but can be called
    // explicitly if early initialization is desired.
    // Returns ESP_OK on success.
    static esp_err_t initNVS();

    // Write a value to NVS.
    // Parameters:
    // - ns: Namespace to open (must not be nullptr).
    // - key: Name of the stored key (must not be nullptr).
    // - type: Type of data being written.
    // - value: Pointer to the value being written (must not be nullptr).
    // - length: Only used for BLOB type. Ignored for numeric types and STR.
    // Returns ESP_OK on success, error code otherwise.
    static esp_err_t writeValue(
        const char* ns,
        const char* key,
        NvsDataType type,
        const void* value,
        size_t length = 0
    );

    // Read a value from NVS.
    // Parameters:
    // - ns: Namespace to open (must not be nullptr).
    // - key: Key name (must not be nullptr).
    // - type: Expected type to read.
    // - out_value: Pointer where result is stored (must not be nullptr).
    // - length: For STR/BLOB this must be provided to know buffer size.
    // Returns ESP_OK on success, error code otherwise.
    static esp_err_t readValue(
        const char* ns,
        const char* key,
        NvsDataType type,
        void* out_value,
        size_t* length = nullptr
    );

    // Convenience function to write state buffer
    // Parameters:
    // - ns: Namespace to open
    // - key: Key name (e.g., "state_buffer")
    // - buffer: Pointer to state buffer (must be STATE_BUFFER_SIZE bytes)
    static esp_err_t writeStateBuffer(
        const char* ns,
        const char* key,
        const uint8_t* buffer
    );

    // Convenience function to read state buffer
    // Parameters:
    // - ns: Namespace to open
    // - key: Key name (e.g., "state_buffer")
    // - buffer: Pointer to output buffer (must be at least STATE_BUFFER_SIZE bytes)
    static esp_err_t readStateBuffer(
        const char* ns,
        const char* key,
        uint8_t* buffer
    );

    // Convenience function to write LoRa key
    // Parameters:
    // - ns: Namespace to open
    // - key: Key name (e.g., "lora_key")
    // - lora_key: Pointer to LoRa key (must be LORA_KEY_SIZE bytes)
    static esp_err_t writeLoRaKey(
        const char* ns,
        const char* key,
        const uint8_t* lora_key
    );

    // Convenience function to read LoRa key
    // Parameters:
    // - ns: Namespace to open
    // - key: Key name (e.g., "lora_key")
    // - lora_key: Pointer to output buffer (must be at least LORA_KEY_SIZE bytes)
    static esp_err_t readLoRaKey(
        const char* ns,
        const char* key,
        uint8_t* lora_key
    );

private:
    // Track whether NVS has been initialized
    static bool nvs_initialized;
};

#endif