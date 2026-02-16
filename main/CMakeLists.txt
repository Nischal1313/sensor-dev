idf_component_register(
  SRCS  "main.cpp" "isd-nvs.cpp" "tasks/tasks.cpp" "device/device_setup.cpp"
INCLUDE_DIRS "." "tasks" "device"
REQUIRES nvs_flash cjson
PRIV_REQUIRES
    esp_driver_uart
)