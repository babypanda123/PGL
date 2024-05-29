#ifndef PGL_H
#define PGL_H

#include "sdkconfig.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"
#include "esp_log.h"
#include "esp_system.h"
#include <cstring>

class SimpleBluetoothSerial {
public:
    SimpleBluetoothSerial();
    
    bool begin(const char* deviceName);
    size_t write(uint8_t c);
    int available();
    int read();
    
private:
    static void spp_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
    
    static std::string _spp_data;
    static uint32_t _spp_client;
};

#endif // PGL_H
