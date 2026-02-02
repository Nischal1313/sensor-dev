#include <inttypes.h> // needed for linux to because of the long-int error
#include "isd-nvs.h"
#include <vector>
#include <string>
#include <cstdio>


extern "C" void app_main() {
    // Create storage in namespace "test_ns"
    NVSStorage storage("test_ns");

    // --- WRITE EXAMPLES ---
    
    // write integers
    storage.writeInt32("int_val", 12345);
    storage.writeFloat("float_val", 3.14159f);

    // write string
    std::string my_string = "Hello ESP32!";
    storage.writeString("my_string", my_string);

    // write blob
    std::vector<uint8_t> my_blob = {0xDE, 0xAD, 0xBE, 0xEF};
    storage.writeBlob("my_blob", my_blob.data(), my_blob.size());

    // --- READ EXAMPLES ---
    
    int32_t int_val = storage.readInt32("int_val", 0);
    float float_val = storage.readFloat("float_val", 0.0f);

    std::string read_string;
    if (storage.readString("my_string", read_string) != ESP_OK) {
        read_string = "default";
    }

    std::vector<uint8_t> read_blob;
    if (storage.readBlob("my_blob", read_blob) != ESP_OK) {
        read_blob.clear();
    }

    // --- PRINT RESULTS ---
    printf("Read int_val   : %d\n", int_val);
    printf("Read float_val : %.5f\n", float_val);
    printf("Read string    : %s\n", read_string.c_str());

    printf("Read blob      : ");
    for (auto b : read_blob) {
        printf("%02X ", b);
    }
    printf("\n");

    // --- OPTIONAL CLEANUP ---
    // storage.eraseAll(); // Uncomment to clear namespace after test
}
