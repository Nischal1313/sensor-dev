#ifndef CALIB_DATA_H
#define CALIB_DATA_H

#include "nvs_flash.h"
#include "nvs.h"
#include <string>

// There is a test.cpp where you can see how to use this and then test it by
// writing and reading 

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

class CalibData {
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

private:
    // Track whether NVS has been initialized
    static bool nvs_initialized;
};

#endif