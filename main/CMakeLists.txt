idf_component_register(
  SRCS  "main.cpp" "isd-nvs.cpp"
INCLUDE_DIRS "."
REQUIRES nvs_flash 
)