#include "newCalibData.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

extern "C" void app_main(void) {
  uint8_t state_buffer[BmeStateStorage::STATE_SIZE] = {0};

  BmeStateStorage storage;

  esp_err_t err = storage.load(state_buffer);

  if (err == ESP_OK) {
    ESP_LOGI(TAG, "BME state loaded from NVS");
    // Pass state_buffer to BME690 library
  } else if (err == ESP_ERR_NVS_NOT_FOUND) {
    ESP_LOGI(TAG, "No stored BME state, starting fresh");
    // Let sensor generate initial state
  } else {
    ESP_LOGE(TAG, "Failed to load BME state (%s)", esp_err_to_name(err));
  }

  err = storage.save(state_buffer);
  if (err == ESP_OK) {
    ESP_LOGI(TAG, "BME state saved to NVS");
  } else {
    ESP_LOGE(TAG, "Failed to save BME state (%s)", esp_err_to_name(err));
  }
}
