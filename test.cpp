#include <cstdio>
#include <cstring>
#include "storage.h"

#define WRITE_MODE 0   // 1 = WRITE, 0 = READ

extern "C" void app_main(void)
{
    Storage storage;
    // ns meaning namespace
    const char* ns = "storage_test";

    printf("\n==============================\n");
#if WRITE_MODE
    printf("NVS TEST MODE: WRITE\n");
#else
    printf("NVS TEST MODE: READ\n");
#endif
    printf("==============================\n");

    /* ---------- Test values ---------- */
    int8_t   i8  = -42;
    uint8_t  u8  = 42;
    int16_t  i16 = -1234;
    uint16_t u16 = 1234;
    int32_t  i32 = -123456;
    uint32_t u32 = 123456;
    int64_t  i64 = -12345678;
    uint64_t u64 = 12345678;

    const char* str_w = "ESP32 power cycle test";
    uint8_t blob_w[6] = {1, 2, 3, 4, 5, 6};

    // State buffer (197 bytes)
    uint8_t state_buffer[] = {
        0x00, 0x01, 0x02, 0x03, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB1, 0x00, 0x00, 0x00,
        0x5A, 0x00, 0x01, 0x00, 0x06, 0x26, 0x95, 0x40, 0x2E, 0x26, 0x95, 0x40, 0xAA, 0x4D, 0x95, 0x40,
        0x2B, 0x69, 0x91, 0x40, 0x5B, 0x51, 0x91, 0x40, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x01, 0x01, 0x01,
        0x14, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00,
        0x00, 0x03, 0x00, 0x3F, 0xAE, 0xE4, 0x3E, 0x14, 0x00, 0x00, 0xE1, 0x44, 0x00, 0x00, 0xE1, 0x44,
        0x00, 0x00, 0x61, 0x45, 0x01, 0x00, 0xA7, 0xB0, 0x90, 0x40, 0xBE, 0x63, 0x8D, 0x40, 0xE6, 0xE6,
        0x85, 0x3F, 0xCE, 0xE6, 0x91, 0x3F, 0x42, 0x60, 0x65, 0x3C, 0x18, 0x00, 0x02, 0x00, 0xC6, 0x98,
        0x90, 0x42, 0x16, 0x92, 0x98, 0x42, 0x50, 0x3A, 0xBD, 0x44, 0x4F, 0x57, 0x21, 0x3C, 0x84, 0x1C,
        0x4B, 0xBF, 0x10, 0x00, 0x03, 0x00, 0xBE, 0x63, 0x8D, 0x40, 0x50, 0x9D, 0x0C, 0x42, 0x07, 0xBA,
        0x0A, 0x42, 0x1B, 0x00, 0x05, 0x00, 0x00, 0x07, 0x0A, 0x3A, 0xA4, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x7E, 0xDE, 0xE5, 0x51, 0x01, 0x01, 0x00, 0xD6, 0x93, 0xD1, 0x53, 0x0C, 0x00, 0x09,
        0x00, 0x00, 0x07, 0x0A, 0x3A, 0xA4, 0x01, 0x00, 0x00, 0x08, 0x00, 0x0A, 0x00, 0x4D, 0x15, 0x0D,
        0x42, 0x00, 0x00, 0x00, 0x00, 0xCF, 0xA4, 0x00, 0x00
    };

    // LoRa key (17 bytes)
    uint8_t lora_key[] = {'A', 'B', 'C', '1', '2', '3', 'D', 'E', 'F', '4', '5', '6', 'G', 'H', 'I', '7', '8'};

#if WRITE_MODE
    /* ================= WRITE ================= */

    printf("\nWriting values to NVS:\n");
    printf("I8   = %d\n", i8);
    printf("U8   = %u\n", u8);
    printf("I16  = %d\n", i16);
    printf("U16  = %u\n", u16);
    printf("I32  = %ld\n", i32);
    printf("U32  = %lu\n", u32);
    printf("I64  = %lld\n", (long long)i64);
    printf("U64  = %llu\n", (unsigned long long)u64);
    printf("STR  = %s\n", str_w);
    printf("BLOB = {1,2,3,4,5,6}\n");
    printf("STATE_BUFFER = 197 bytes\n");
    printf("LORA_KEY = 17 bytes\n");

    // Write all values
    esp_err_t err;
    
    err = storage.writeValue(ns, "i8", NvsDataType::I8, &i8);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i8: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "u8", NvsDataType::U8, &u8);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u8: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "i16", NvsDataType::I16, &i16);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i16: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "u16", NvsDataType::U16, &u16);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u16: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "i32", NvsDataType::I32, &i32);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i32: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "u32", NvsDataType::U32, &u32);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u32: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "i64", NvsDataType::I64, &i64);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i64: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "u64", NvsDataType::U64, &u64);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u64: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "str", NvsDataType::STR, str_w);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write str: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "blob", NvsDataType::BLOB, blob_w, sizeof(blob_w));
    if (err != ESP_OK) {
        printf("ERROR: Failed to write blob: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "state_buffer", NvsDataType::BLOB, state_buffer, sizeof(state_buffer));
    if (err != ESP_OK) {
        printf("ERROR: Failed to write state_buffer: %d\n", err);
        return;
    }

    err = storage.writeValue(ns, "lora_key", NvsDataType::BLOB, lora_key, sizeof(lora_key));
    if (err != ESP_OK) {
        printf("ERROR: Failed to write lora_key: %d\n", err);
        return;
    }

    printf("\n*** WRITE COMPLETE ***\n");
    printf("All values written successfully!\n");
    printf("\nNEXT STEPS:\n");
    printf("1. POWER OFF THE DEVICE NOW\n");
    printf("2. Set WRITE_MODE = 0 in test code\n");
    printf("3. Reflash and power on to verify persistence\n");

#else
    /* ================= READ ================= */

    int8_t   i8_r;
    uint8_t  u8_r;
    int16_t  i16_r;
    uint16_t u16_r;
    int32_t  i32_r;
    uint32_t u32_r;
    int64_t  i64_r;
    uint64_t u64_r;

    char str_r[64];
    size_t str_len = sizeof(str_r);

    uint8_t blob_r[6];
    size_t blob_len = sizeof(blob_r);

    uint8_t state_buffer_r[197];
    size_t state_buffer_len = sizeof(state_buffer_r);

    uint8_t lora_key_r[17];
    size_t lora_key_len = sizeof(lora_key_r);

    printf("\nReading values from NVS...\n");

    esp_err_t err;
    bool all_passed = true;

    err = storage.readValue(ns, "i8", NvsDataType::I8, &i8_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i8: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "u8", NvsDataType::U8, &u8_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u8: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "i16", NvsDataType::I16, &i16_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i16: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "u16", NvsDataType::U16, &u16_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u16: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "i32", NvsDataType::I32, &i32_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i32: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "u32", NvsDataType::U32, &u32_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u32: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "i64", NvsDataType::I64, &i64_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i64: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "u64", NvsDataType::U64, &u64_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u64: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "str", NvsDataType::STR, str_r, &str_len);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read str: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "blob", NvsDataType::BLOB, blob_r, &blob_len);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read blob: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "state_buffer", NvsDataType::BLOB, state_buffer_r, &state_buffer_len);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read state_buffer: %d\n", err);
        all_passed = false;
    }

    err = storage.readValue(ns, "lora_key", NvsDataType::BLOB, lora_key_r, &lora_key_len);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read lora_key: %d\n", err);
        all_passed = false;
    }

    if (!all_passed) {
        printf("\n*** READ FAILED ***\n");
        printf("Some values could not be read. See errors above.\n");
        return;
    }

    printf("\n--- Read Values ---\n");
    printf("I8   = %d\n", i8_r);
    printf("U8   = %u\n", u8_r);
    printf("I16  = %d\n", i16_r);
    printf("U16  = %u\n", u16_r);
    printf("I32  = %ld\n", i32_r);
    printf("U32  = %lu\n", u32_r);
    printf("I64  = %lld\n", (long long)i64_r);
    printf("U64  = %llu\n", (unsigned long long)u64_r);
    printf("STR  = %s\n", str_r);

    printf("BLOB = {");
    for (size_t i = 0; i < blob_len; i++) {
        printf("%u", blob_r[i]);
        if (i < blob_len - 1) printf(",");
    }
    printf("}\n");

    printf("STATE_BUFFER = {");
    for (size_t i = 0; i < state_buffer_len; i++) {
        printf("0x%02X", state_buffer_r[i]);
        if (i < state_buffer_len - 1) printf(",");
        if ((i + 1) % 16 == 0 && i < state_buffer_len - 1) printf("\n                ");
    }
    printf("}\n");

    printf("LORA_KEY = {");
    for (size_t i = 0; i < lora_key_len; i++) {
        printf("'%c'", lora_key_r[i]);
        if (i < lora_key_len - 1) printf(",");
    }
    printf("}\n");

    // Verify values match
    bool verification_passed = true;
    
    if (i8_r != i8) {
        printf("FAIL: I8 mismatch (expected %d, got %d)\n", i8, i8_r);
        verification_passed = false;
    }
    if (u8_r != u8) {
        printf("FAIL: U8 mismatch (expected %u, got %u)\n", u8, u8_r);
        verification_passed = false;
    }
    if (i16_r != i16) {
        printf("FAIL: I16 mismatch (expected %d, got %d)\n", i16, i16_r);
        verification_passed = false;
    }
    if (u16_r != u16) {
        printf("FAIL: U16 mismatch (expected %u, got %u)\n", u16, u16_r);
        verification_passed = false;
    }
    if (i32_r != i32) {
        printf("FAIL: I32 mismatch (expected %ld, got %ld)\n", i32, i32_r);
        verification_passed = false;
    }
    if (u32_r != u32) {
        printf("FAIL: U32 mismatch (expected %lu, got %lu)\n", u32, u32_r);
        verification_passed = false;
    }
    if (i64_r != i64) {
        printf("FAIL: I64 mismatch (expected %lld, got %lld)\n", (long long)i64, (long long)i64_r);
        verification_passed = false;
    }
    if (u64_r != u64) {
        printf("FAIL: U64 mismatch (expected %llu, got %llu)\n", (unsigned long long)u64, (unsigned long long)u64_r);
        verification_passed = false;
    }
    if (strcmp(str_r, str_w) != 0) {
        printf("FAIL: STR mismatch (expected '%s', got '%s')\n", str_w, str_r);
        verification_passed = false;
    }
    if (blob_len != sizeof(blob_w) || memcmp(blob_r, blob_w, blob_len) != 0) {
        printf("FAIL: BLOB mismatch\n");
        verification_passed = false;
    }
    if (state_buffer_len != sizeof(state_buffer) || memcmp(state_buffer_r, state_buffer, state_buffer_len) != 0) {
        printf("FAIL: STATE_BUFFER mismatch\n");
        verification_passed = false;
    }
    if (lora_key_len != sizeof(lora_key) || memcmp(lora_key_r, lora_key, lora_key_len) != 0) {
        printf("FAIL: LORA_KEY mismatch\n");
        verification_passed = false;
    }

    printf("\n==============================\n");
    if (verification_passed) {
        printf("*** NVS PERSISTENCE TEST PASSED ***\n");
        printf("All values matched expected values!\n");
    } else {
        printf("*** NVS PERSISTENCE TEST FAILED ***\n");
        printf("Some values did not match. See errors above.\n");
    }
    printf("==============================\n");

#endif
}