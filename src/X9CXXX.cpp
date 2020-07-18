#include <Arduino.h>
#include "X9CXXX.h"

X9CXXX::X9CXXX(uint8_t cs, uint8_t inc, uint8_t up_dow)
{
    cs__ = cs;
    inc__ = inc;
    up_dow__ = up_dow;
    initied__=false;
}

void X9CXXX::begin()
{
    pinMode(cs__, OUTPUT);
    pinMode(inc__, OUTPUT);
    pinMode(up_dow__, OUTPUT);
    digitalWrite(cs__, HIGH);
}

void X9CXXX::wiperUp(uint8_t step, bool save)
{
    if(!initied__){
        this->begin();
        initied__=true;
    }
    digitalWrite(up_dow__, HIGH);
    digitalWrite(inc__, HIGH);
    delayMicroseconds(300);
    digitalWrite(cs__, LOW);
    for (int i = 0; i < step; i++)
    {
        digitalWrite(inc__, LOW);
        delayMicroseconds(3);
        digitalWrite(inc__, HIGH);
        delayMicroseconds(3);
    }
    if (save)
        digitalWrite(inc__, HIGH);
    else
        digitalWrite(inc__, LOW);
    delayMicroseconds(300);
    digitalWrite(cs__, HIGH);
    delayMicroseconds(300);
}

void X9CXXX::wiperDow(uint8_t step, bool save)
{
    if(!initied__){
        this->begin();
        initied__=true;
    }
    digitalWrite(up_dow__, LOW);
    digitalWrite(inc__, HIGH);
    delayMicroseconds(300);
    digitalWrite(cs__, LOW);
    for (int i = 0; i < step; i++)
    {
        digitalWrite(inc__, LOW);
        delayMicroseconds(3);
        digitalWrite(inc__, HIGH);
        delayMicroseconds(3);
    }
    if (save)
        digitalWrite(inc__, HIGH);
    else
        digitalWrite(inc__, LOW);
    delayMicroseconds(300);
    digitalWrite(cs__, HIGH);
    delayMicroseconds(300);
}