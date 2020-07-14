#include <Arduino.h>
#include "X9CXXX.h"

X9CXXX::X9CXXX(uint8_t cs, uint8_t inc, uint8_t up_dow)
{
    cs__ = cs;
    inc__ = inc;
    up_dow__ = up_dow;
}

void X9CXXX::begin()
{
    pinMode(cs__, OUTPUT);
    pinMode(inc__, OUTPUT);
    pinMode(up_dow__, OUTPUT);
    this->toStandby();
}

void X9CXXX::wiperUp(uint8_t step)
{
    digitalWrite(up_dow__, HIGH);
    digitalWrite(inc__, HIGH);
    delay(1);
    digitalWrite(cs__, LOW);
    for (int i = 0; i < step; i++)
    {
        digitalWrite(inc__, LOW);
        delayMicroseconds(1);       
        digitalWrite(inc__, HIGH);
        delayMicroseconds(1);       
    }
}

void X9CXXX::wiperDow(uint8_t step)
{
    digitalWrite(up_dow__, LOW);
    digitalWrite(inc__, HIGH);
    delay(1);
    digitalWrite(cs__, LOW);
    for (int i = 0; i < step; i++)
    {
        digitalWrite(inc__, LOW);
        delayMicroseconds(1);       
        digitalWrite(inc__, HIGH);
        delayMicroseconds(1);       
    }
}

void X9CXXX::toStandby(bool storeWiper)
{
    delayMicroseconds(1);       
    digitalWrite(inc__, HIGH);
    delayMicroseconds(1);       
    digitalWrite(cs__, LOW);
    delayMicroseconds(1);       
    if (storeWiper)
    {
        Serial.println("HIGH");
        digitalWrite(inc__, HIGH);
    }
    else
    {
        Serial.println("LOW");
        digitalWrite(inc__, LOW);
    }
    delayMicroseconds(100);       
    digitalWrite(cs__, HIGH);
    delayMicroseconds(100);       
    digitalWrite(inc__, HIGH);
    delayMicroseconds(100);       
}

bool X9CXXX::isInStandby()
{
    return true;
};