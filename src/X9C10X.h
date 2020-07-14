#ifndef __X9C10X__
#define __X9C10X__

#include <Arduino.h>

class X9C10X
{
private:
    uint8_t cs__;
    uint8_t inc__;
    uint8_t up_dow__;
public:
    X9C10X(uint8_t cs, uint8_t inc, uint8_t up_dow);
    void begin();
    void wiperUp(uint8_t step=1);
    void wiperDow(uint8_t step=1);
    void toStandby(bool storeWiper=false);
    bool isInStandby();

private:
};

#endif