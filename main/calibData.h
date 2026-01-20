#ifndef CALIB_DATA_H
#define CALIB_DATA_H

#include "nvs.h"
#include "nvs_flash.h"
#include <string>
#include <vector>

enum class NvsDataType { I8, U8, I16, U16, I32, U32, I64, U64, STR, BLOB };

class CalibData {
public:
  explicit CalibData(const char *ns);

  static esp_err_t initNVS();

  // === LOW-LEVEL SWITCH-BASED API (supports all types) ===
  esp_err_t writeValue(const char *key, NvsDataType type, const void *value,
                       size_t length = 0);

  esp_err_t readValue(const char *key, NvsDataType type, void *out_value,
                      size_t *length = nullptr);

  // === TEMPLATE TYPE-SAFE API (automatic type mapping) ===
  template <typename T> esp_err_t write(const char *key, const T &value);

  template <typename T> esp_err_t read(const char *key, T &out_value);

  // String helper (automatic buffer sizing)
  esp_err_t writeString(const char *key, const std::string &value);
  esp_err_t readString(const char *key, std::string &out);

  // Blob helper
  esp_err_t writeBlob(const char *key, const void *data, size_t len);
  esp_err_t readBlob(const char *key, std::vector<uint8_t> &out);

private:
  const char *namespace_name;
};

#endif
