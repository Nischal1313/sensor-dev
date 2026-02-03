#include <cstdio>
#include <cstring>
#include "isd-nvs.h"

#define WRITE_MODE 0   // 1 = WRITE, 0 = READ

extern "C" void app_main(void)
{
    CalibData calib;
    // ns meaning namespace
    const char* ns = "calib_test";

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

    // Write all values - each write is independent
    esp_err_t err;
    
    err = calib.writeValue(ns, "i8", NvsDataType::I8, &i8);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i8: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "u8", NvsDataType::U8, &u8);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u8: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "i16", NvsDataType::I16, &i16);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i16: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "u16", NvsDataType::U16, &u16);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u16: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "i32", NvsDataType::I32, &i32);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i32: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "u32", NvsDataType::U32, &u32);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u32: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "i64", NvsDataType::I64, &i64);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write i64: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "u64", NvsDataType::U64, &u64);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write u64: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "str", NvsDataType::STR, str_w);
    if (err != ESP_OK) {
        printf("ERROR: Failed to write str: %d\n", err);
        return;
    }

    err = calib.writeValue(ns, "blob", NvsDataType::BLOB, blob_w, sizeof(blob_w));
    if (err != ESP_OK) {
        printf("ERROR: Failed to write blob: %d\n", err);
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

    printf("\nReading values from NVS...\n");

    esp_err_t err;
    bool all_passed = true;

    err = calib.readValue(ns, "i8", NvsDataType::I8, &i8_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i8: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "u8", NvsDataType::U8, &u8_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u8: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "i16", NvsDataType::I16, &i16_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i16: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "u16", NvsDataType::U16, &u16_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u16: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "i32", NvsDataType::I32, &i32_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i32: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "u32", NvsDataType::U32, &u32_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u32: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "i64", NvsDataType::I64, &i64_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read i64: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "u64", NvsDataType::U64, &u64_r, nullptr);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read u64: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "str", NvsDataType::STR, str_r, &str_len);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read str: %d\n", err);
        all_passed = false;
    }

    err = calib.readValue(ns, "blob", NvsDataType::BLOB, blob_r, &blob_len);
    if (err != ESP_OK) {
        printf("ERROR: Failed to read blob: %d\n", err);
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