#include "newCalibData.h"
#include "calibData.h"

esp_err_t BmeStateStorage::save(const uint8_t *state) {
  if (state == nullptr) {
    return ESP_ERR_INVALID_ARG;
  }

  CalibData nvs;

  return nvs.writeBlob(NAMESPACE, KEY, state, STATE_SIZE);
}

esp_err_t BmeStateStorage::load(uint8_t *state) {
  if (state == nullptr) {
    return ESP_ERR_INVALID_ARG;
  }

  CalibData nvs;

  return nvs.readBlob(NAMESPACE, KEY, state, STATE_SIZE);
}
