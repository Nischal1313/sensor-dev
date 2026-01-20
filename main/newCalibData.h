#pragma once

#include "esp_err.h"
#include <cstddef>
#include <cstdint>

class BmeStateStorage {
public:
  static constexpr size_t STATE_SIZE = 201;
  esp_err_t save(const uint8_t *state);
  esp_err_t load(uint8_t *state);
private:
  static constexpr const char *NAMESPACE = "bme690";
  static constexpr const char *KEY = "state";
};
