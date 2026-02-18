idf_component_register(
<<<<<<< HEAD
  SRCS  "main.cpp" "isd-nvs.cpp" "tasks/tasks.cpp" "device/device_setup.cpp"
INCLUDE_DIRS "." "tasks" "device"
REQUIRES nvs_flash cjson
PRIV_REQUIRES
    esp_driver_uart
=======
  SRCS  "main.cpp" "isd-nvs.cpp"
INCLUDE_DIRS "."
REQUIRES nvs_flash esp_driver_usb_serial_jtag esp_timer
>>>>>>> upstream/main
)