#ifndef CALIB_DATA_H
#define CALIB_DATA_H

#include "nvs_flash.h"
#include "nvs.h"
#include <string>

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
    static esp_err_t initNVS();

    // Write a value to NVS.
    // Parameters:
    // - ns: Namespace to open.
    // - key: Name of the stored key.
    // - type: Type of data being written.
    // - value: Pointer to the value being written.
    // - length: Only used for STR or BLOB. Ignored for numeric types.
    static esp_err_t writeValue(
        const char* ns,
        const char* key,
        NvsDataType type,
        const void* value,
        size_t length = 0
    );

    // Read a value from NVS.
    // Parameters:
    // - ns: Namespace to open.
    // - key: Key name.
    // - type: Expected type to read.
    // - out_value: Pointer where result is stored.
    // - length: For STR/BLOB this must be provided to know buffer size.
    static esp_err_t readValue(
        const char* ns,
        const char* key,
        NvsDataType type,
        void* out_value,
        size_t* length = nullptr
    );
};

#endif
