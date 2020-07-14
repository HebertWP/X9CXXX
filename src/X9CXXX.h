#ifndef __X9CXXX__
#define __X9CXXX__

#include <Arduino.h>

class X9CXXX
{
private:
    uint8_t cs__;
    uint8_t inc__;
    uint8_t up_dow__;
public:
    X9CXXX(uint8_t cs, uint8_t inc, uint8_t up_dow);
    void begin();
    void wiperUp(uint8_t step=1);
    void wiperDow(uint8_t step=1);
    void toStandby(bool storeWiper=false);
    bool isInStandby();

private:
};

#endif