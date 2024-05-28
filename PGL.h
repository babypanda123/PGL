#ifndef PGL_h
#define PGL_h

#include <Arduino.h>
#include <HardwareSerial.h>

class PGL : public Stream {
public:
    PGL();
    ~PGL();

    void begin(String name);
    void end();

    virtual int available();
    virtual int read();
    virtual int peek();
    virtual size_t write(uint8_t data);
    virtual void flush();

    using Print::write;

    operator bool() {
        return true;
    }

private:
    HardwareSerial *serial;
};

extern PGL PGL_BT;

#endif
