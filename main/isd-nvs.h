#ifndef NVS_STORAGE_H
#define NVS_STORAGE_H

#include "nvs.h"
#include "nvs_flash.h"
#include <string>
#include <vector>
#include <cstdint>

class NVSStorage {
public:
    /**
     * Create NVS handler for a specific namespace
     * @param ns Namespace name (max 15 characters)
     * @param tag Optional logging tag (defaults to "NVS")
     */
    NVSStorage(const char* ns, const char* log_tag = "NVS");  
    // write methods
    
    esp_err_t writeInt8(const char* key, int8_t value);
    esp_err_t writeUInt8(const char* key, uint8_t value);
    esp_err_t writeInt16(const char* key, int16_t value);
    esp_err_t writeUInt16(const char* key, uint16_t value);
    esp_err_t writeInt32(const char* key, int32_t value);
    esp_err_t writeUInt32(const char* key, uint32_t value);
    esp_err_t writeInt64(const char* key, int64_t value);
    esp_err_t writeUInt64(const char* key, uint64_t value);
    
    //no precision loss
    esp_err_t writeFloat(const char* key, float value);
    
    //no precision loss
    esp_err_t writeDouble(const char* key, double value);
    
    // write string 
    esp_err_t writeString(const char* key, const std::string& value);
    
    // write binary blob
    esp_err_t writeBlob(const char* key, const void* data, size_t length);

    
    // read methods 
    
    esp_err_t readInt8(const char* key, int8_t& out_value);
    esp_err_t readUInt8(const char* key, uint8_t& out_value);
    esp_err_t readInt16(const char* key, int16_t& out_value);
    esp_err_t readUInt16(const char* key, uint16_t& out_value);
    esp_err_t readInt32(const char* key, int32_t& out_value);
    esp_err_t readUInt32(const char* key, uint32_t& out_value);
    esp_err_t readInt64(const char* key, int64_t& out_value);
    esp_err_t readUInt64(const char* key, uint64_t& out_value);
    
    //no precision loss
    esp_err_t readFloat(const char* key, float& out_value);
    esp_err_t readDouble(const char* key, double& out_value);

    esp_err_t readString(const char* key, std::string& out_value);
    esp_err_t readBlob(const char* key, std::vector<uint8_t>& out_data);


    // read methods with default values
    
    int8_t readInt8(const char* key, int8_t default_value = 0);
    uint8_t readUInt8(const char* key, uint8_t default_value = 0);
    int16_t readInt16(const char* key, int16_t default_value = 0);
    uint16_t readUInt16(const char* key, uint16_t default_value = 0);
    int32_t readInt32(const char* key, int32_t default_value = 0);
    uint32_t readUInt32(const char* key, uint32_t default_value = 0);
    int64_t readInt64(const char* key, int64_t default_value = 0);
    uint64_t readUInt64(const char* key, uint64_t default_value = 0);
    float readFloat(const char* key, float default_value = 0.0f);
    double readDouble(const char* key, double default_value = 0.0);

    
    // Utility methods
    
    // Check if a key exists 
    bool exists(const char* key);
    
    // Delete a key 
    esp_err_t erase(const char* key);
    
    // Clear all data in this namespace
    esp_err_t eraseAll();
    
    // Get namespace name
    const char* getNamespace() const { return namespace_name; }
    
    // Enable/disable verbose logging
    void setVerbose(bool enable) { verbose_logging = enable; }

private:
    const char* namespace_name;
    const char* tag;
    bool verbose_logging;
    
    esp_err_t initNVS();
    
    
    std::string valueToString(nvs_type_t type, const void* value);
};

#endif // NVS_STORAGE_H