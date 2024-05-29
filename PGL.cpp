#include "PGL.h"

std::string PGL::_spp_data = "";
uint32_t PGL::_spp_client = 0;

PGL::PGL() : _spp_client(0) {}

bool PGL::begin(const char* deviceName) {
    if (!btStart()) {
        return false;
    }
    
    esp_bluedroid_init();
    esp_bluedroid_enable();
    
    esp_spp_register_callback(spp_callback);
    esp_spp_init(ESP_SPP_MODE_CB);
    
    esp_bt_dev_set_device_name(deviceName); // 변경: Scan mode 설정 대신에 device name 설정
    // 변경: Scan mode 설정 대신에 device name 설정
    //esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
    
    return true;
}

size_t PGL::write(uint8_t c) {
    if (_spp_client) {
        esp_spp_write(_spp_client, 1, &c);
    }
    return 1;
}

size_t PGL::print(const int &val) {
    size_t len = 0;
    if (_spp_client) {
        char buffer[20]; // 정수를 문자열로 변환하기 위한 버퍼 크기
        len = snprintf(buffer, sizeof(buffer), "%d", val);
        esp_spp_write(_spp_client, len, (uint8_t*)buffer);
    }
    return len;
}

size_t PGL::print(const std::string &str) {
    size_t len = str.length();
    if (_spp_client) {
        esp_spp_write(_spp_client, len, (uint8_t*)str.c_str());
    }
    return len;
}

size_t PGL::println(const std::string &str) {
    size_t len = print(str);
    if (_spp_client) {
        esp_spp_write(_spp_client, 1, (uint8_t*)"\n");
    }
    return len + 1;
}

int PGL::available() {
    return _spp_data.length();
}

int PGL::read() {
    if (_spp_data.length() > 0) {
        char c = _spp_data[0];
        _spp_data.erase(0, 1);
        return c;
    }
    return -1;
}

void PGL::spp_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    if (event == ESP_SPP_DATA_IND_EVT) {
        _spp_data.append((char*)param->data_ind.data, param->data_ind.len);
    } else if (event == ESP_SPP_SRV_OPEN_EVT) {
        _spp_client = param->srv_open.handle;
    }
}
