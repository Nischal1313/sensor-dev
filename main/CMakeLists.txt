idf_component_register(
  SRCS "newCalibData.cpp" "calibData.cpp" "main.cpp" "savingCalibration.cpp" "write.c"
INCLUDE_DIRS "."
REQUIRES nvs_flash 
)