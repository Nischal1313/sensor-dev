idf_component_register(SRCS "calibData.cpp" "basicNVS.cpp" "main.cpp" "savingCalibration.cpp" "write.c" "test.c"
INCLUDE_DIRS ".")

REQUIRES nvs_flash
