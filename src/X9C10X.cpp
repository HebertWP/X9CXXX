#include <Arduino.h>
#include "X9C10X.h"

X9C10X::X9C10X(uint8_t cs, uint8_t inc, uint8_t up_dow)
{
}

void X9C10X::begin()
{
    Serial.println("Begin");
}
void X9C10X::wiperUp(uint8_t step)
{
    char data[10];
    sprintf(data, "Up %i \n", step);
    Serial.print(data);
}

void X9C10X::wiperDow(uint8_t step)
{
    char data[10];
    sprintf(data, "Dow %i \n", step);
    Serial.print(data);
}

void X9C10X::toStandby(uint8_t storeWiper)
{
    if(storeWiper)
        Serial.println("Value Stored");
    else
        Serial.println("Value forgotten");
}

bool X9C10X::isInStandby()
{
    return true;
};