#include "PGL.h"

PGL PGL_BT;

PGL::PGL() {
    serial = &Serial; // 기본 시리얼 포트를 사용합니다. 필요에 따라 변경할 수 있습니다.
}

PGL::~PGL() {
    // 아무 작업도 필요하지 않습니다.
}

void PGL::begin(String name) {
    // Bluetooth 시리얼 통신을 시작합니다.
    serial->begin(9600); // 기본 속도는 9600으로 설정됩니다. 필요에 따라 변경할 수 있습니다.
}

void PGL::end() {
    // Bluetooth 시리얼 통신을 종료합니다.
    serial->end();
}

int PGL::available() {
    // 수신 버퍼에 있는 바이트 수를 반환합니다.
    return serial->available();
}

int PGL::read() {
    // 다음 바이트를 읽고 반환합니다.
    return serial->read();
}

int PGL::peek() {
    // 다음 읽을 바이트를 확인합니다.
    return serial->peek();
}

size_t PGL::write(uint8_t data) {
    // 데이터를 보냅니다.
    return serial->write(data);
}

void PGL::flush() {
    // 송신 버퍼를 비웁니다.
    serial->flush();
}
