#include "CalibData.h"
#include <cstdio>
#include <cstring>

CalibData::CalibData(const char *ns) : namespace_name(ns) {}

esp_err_t CalibData::initNVS() {
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
      err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  return err;
}

esp_err_t CalibData::writeValue(const char *key, NvsDataType type,
                                const void *value, size_t length) {
  initNVS();

  nvs_handle_t handle;
  esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &handle);
  if (err != ESP_OK)
    return err;

  switch (type) {
  case NvsDataType::I8:
    err = nvs_set_i8(handle, key, *reinterpret_cast<const int8_t *>(value));
    break;
  case NvsDataType::U8:
    err = nvs_set_u8(handle, key, *reinterpret_cast<const uint8_t *>(value));
    break;
  case NvsDataType::I16:
    err = nvs_set_i16(handle, key, *reinterpret_cast<const int16_t *>(value));
    break;
  case NvsDataType::U16:
    err = nvs_set_u16(handle, key, *reinterpret_cast<const uint16_t *>(value));
    break;
  case NvsDataType::I32:
    err = nvs_set_i32(handle, key, *reinterpret_cast<const int32_t *>(value));
    break;
  case NvsDataType::U32:
    err = nvs_set_u32(handle, key, *reinterpret_cast<const uint32_t *>(value));
    break;
  case NvsDataType::I64:
    err = nvs_set_i64(handle, key, *reinterpret_cast<const int64_t *>(value));
    break;
  case NvsDataType::U64:
    err = nvs_set_u64(handle, key, *reinterpret_cast<const uint64_t *>(value));
    break;

  case NvsDataType::STR:
    err = nvs_set_str(handle, key, reinterpret_cast<const char *>(value));
    break;

  case NvsDataType::BLOB:
    err = nvs_set_blob(handle, key, value, length);
    break;
  }

  if (err == ESP_OK)
    err = nvs_commit(handle);
  nvs_close(handle);
  return err;
}

esp_err_t CalibData::readValue(const char *key, NvsDataType type,
                               void *out_value, size_t *length) {
  initNVS();

  nvs_handle_t handle;
  esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
  if (err != ESP_OK)
    return err;

  switch (type) {
  case NvsDataType::I8:
    err = nvs_get_i8(handle, key, reinterpret_cast<int8_t *>(out_value));
    break;
  case NvsDataType::U8:
    err = nvs_get_u8(handle, key, reinterpret_cast<uint8_t *>(out_value));
    break;
  case NvsDataType::I16:
    err = nvs_get_i16(handle, key, reinterpret_cast<int16_t *>(out_value));
    break;
  case NvsDataType::U16:
    err = nvs_get_u16(handle, key, reinterpret_cast<uint16_t *>(out_value));
    break;
  case NvsDataType::I32:
    err = nvs_get_i32(handle, key, reinterpret_cast<int32_t *>(out_value));
    break;
  case NvsDataType::U32:
    err = nvs_get_u32(handle, key, reinterpret_cast<uint32_t *>(out_value));
    break;
  case NvsDataType::I64:
    err = nvs_get_i64(handle, key, reinterpret_cast<int64_t *>(out_value));
    break;
  case NvsDataType::U64:
    err = nvs_get_u64(handle, key, reinterpret_cast<uint64_t *>(out_value));
    break;

  case NvsDataType::STR:
    err = nvs_get_str(handle, key, reinterpret_cast<char *>(out_value), length);
    break;

  case NvsDataType::BLOB:
    err = nvs_get_blob(handle, key, out_value, length);
    break;
  }

  nvs_close(handle);
  return err;
}

// =====================================================================
// Automatic string sizing
// =====================================================================

esp_err_t CalibData::writeString(const char *key, const std::string &value) {
  return writeValue(key, NvsDataType::STR, value.c_str());
}

esp_err_t CalibData::readString(const char *key, std::string &out) {
  initNVS();

  nvs_handle_t handle;
  esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
  if (err != ESP_OK)
    return err;

  size_t required = 0;
  err = nvs_get_str(handle, key, nullptr, &required);
  if (err != ESP_OK) {
    nvs_close(handle);
    return err;
  }

  out.resize(required);
  err = nvs_get_str(handle, key, &out[0], &required);

  nvs_close(handle);
  return err;
}

// =====================================================================
// Blob helpers
// =====================================================================

esp_err_t CalibData::writeBlob(const char *key, const void *data, size_t len) {
  return writeValue(key, NvsDataType::BLOB, data, len);
}

esp_err_t CalibData::readBlob(const char *key, std::vector<uint8_t> &out) {
  initNVS();

  nvs_handle_t handle;
  esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &handle);
  if (err != ESP_OK)
    return err;

  size_t size = 0;
  err = nvs_get_blob(handle, key, nullptr, &size);
  if (err != ESP_OK) {
    nvs_close(handle);
    return err;
  }

  out.resize(size);
  err = nvs_get_blob(handle, key, out.data(), &size);

  nvs_close(handle);
  return err;
}

// =====================================================================
// Template API
// =====================================================================

template <typename T>
esp_err_t CalibData::write(const char *key, const T &value) {
  return writeValue(key, NvsDataType::BLOB, &value, sizeof(T));
}

template <typename T> esp_err_t CalibData::read(const char *key, T &out_value) {
  size_t len = sizeof(T);
  return readValue(key, NvsDataType::BLOB, &out_value, &len);
}

// Instantiate templates
template esp_err_t CalibData::write<uint8_t>(const char *, const uint8_t &);
template esp_err_t CalibData::write<uint16_t>(const char *, const uint16_t &);
template esp_err_t CalibData::write<uint32_t>(const char *, const uint32_t &);
template esp_err_t CalibData::write<uint64_t>(const char *, const uint64_t &);
template esp_err_t CalibData::write<int>(const char *, const int &);

template esp_err_t CalibData::read<uint8_t>(const char *, uint8_t &);
template esp_err_t CalibData::read<uint16_t>(const char *, uint16_t &);
template esp_err_t CalibData::read<uint32_t>(const char *, uint32_t &);
template esp_err_t CalibData::read<uint64_t>(const char *, uint64_t &);
template esp_err_t CalibData::read<int>(const char *, int &);
