#include "newCalibData.h"
#include "calibData.h"  // make sure this is included
#include <vector>
#include <cstring>      // for memcpy

esp_err_t BmeStateStorage::save(const uint8_t *state) {
    // Pass namespace to CalibData constructor
    CalibData nvs(NAMESPACE);

    // writeBlob expects 3 arguments: key, pointer, length
    return nvs.writeBlob(KEY, state, STATE_SIZE);
}

esp_err_t BmeStateStorage::load(uint8_t *state) {
    CalibData nvs(NAMESPACE);

    // readBlob fills a std::vector
    std::vector<uint8_t> buffer;
    esp_err_t err = nvs.readBlob(KEY, buffer);

    if (err != ESP_OK || buffer.size() != STATE_SIZE) {
        return ESP_FAIL;
    }

    // copy vector into raw pointer
    memcpy(state, buffer.data(), STATE_SIZE);
    return ESP_OK;
}
