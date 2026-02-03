#include <cstdio>
#include <cstring>
#include <cassert>
#include "savingCalibration.h"

#define WRITE_MODE 0   // 1 = WRITE, 0 = READ

extern "C" void app_main(void)
{
    CalibData calib;
    //ns meaning name space
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

    printf("Writing values to NVS:\n");
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

    ESP_ERROR_CHECK(calib.writeValue(ns, "i8",  NvsDataType::I8,  &i8,  sizeof(i8)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "u8",  NvsDataType::U8,  &u8,  sizeof(u8)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "i16", NvsDataType::I16, &i16, sizeof(i16)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "u16", NvsDataType::U16, &u16, sizeof(u16)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "i32", NvsDataType::I32, &i32, sizeof(i32)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "u32", NvsDataType::U32, &u32, sizeof(u32)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "i64", NvsDataType::I64, &i64, sizeof(i64)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "u64", NvsDataType::U64, &u64, sizeof(u64)));
    ESP_ERROR_CHECK(calib.writeValue(ns, "str", NvsDataType::STR, str_w, 0));
    ESP_ERROR_CHECK(calib.writeValue(ns, "blob",NvsDataType::BLOB,blob_w,sizeof(blob_w)));

    printf("\nWRITE COMPLETE.\n");
    printf("POWER OFF THE DEVICE NOW.\n");
    printf("Then set WRITE_MODE = 0 and reflash.\n");

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

    ESP_ERROR_CHECK(calib.readValue(ns, "i8",  NvsDataType::I8,  &i8_r,  nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "u8",  NvsDataType::U8,  &u8_r,  nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "i16", NvsDataType::I16, &i16_r, nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "u16", NvsDataType::U16, &u16_r, nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "i32", NvsDataType::I32, &i32_r, nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "u32", NvsDataType::U32, &u32_r, nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "i64", NvsDataType::I64, &i64_r, nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "u64", NvsDataType::U64, &u64_r, nullptr));
    ESP_ERROR_CHECK(calib.readValue(ns, "str", NvsDataType::STR, str_r, &str_len));
    ESP_ERROR_CHECK(calib.readValue(ns, "blob",NvsDataType::BLOB,blob_r,&blob_len));

    printf("Read values from NVS:\n");
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

    printf("\nREAD COMPLETE.\n");
    printf("If values match WRITE output, NVS persistence PASSED.\n");

#endif
}
