idf_component_register(

  SRCS  "main.cpp" "isd-nvs.cpp" "tasks/tasks.cpp" "device/device_setup.cpp" "console.cpp"
  
  INCLUDE_DIRS "." "tasks" "device" 
REQUIRES nvs_flash cjson
REQUIRES nvs_flash esp_driver_usb_serial_jtag esp_timer
PRIV_REQUIRES
    esp_driver_uart
)