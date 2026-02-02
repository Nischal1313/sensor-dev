idf_component_register(
  SRCS  "main.cpp" "savingCalibration.cpp" "isd-nvs.cpp"
INCLUDE_DIRS "."
REQUIRES nvs_flash 
)