#include <Arduino.h>
#include "X9CXXX.h"

void stateMachine(char in);
uint8_t arrayToInteger(char *in);

#define CS 2
#define INC 25
#define UP_DOW 17
X9CXXX digitalPot(CS, INC, UP_DOW);
bool save=false;
void setup()
{
    Serial.begin(115200);
}

void loop()
{
    if (Serial.available() > 0)
        stateMachine(Serial.read());
}

enum state
{
    Sidle,
    Sready,
    Sset,
    Sget,
    Sinterger,
    Sgetstandby,
    Ssetstandby
};

void stateMachine(char in)
{
    static char reg;
    static char val[3];
    static uint8_t cont = 0;
    static enum state state = Sidle;
    switch (state)
    {
    case Sidle:
        state = (in == '#') ? Sready : Sidle;
        break;
    case Sready:
        switch (in)
        {
        case 'g':
        case 'G':
            state = Sget;
            break;
        case 's':
        case 'S':
            state = Sset;
            break;
        default:
            state = Sidle;
        }
        break;
    case Sget:
        reg = in;
        switch (in)
        {
        case 's':
        case 'S':
            state = Sgetstandby;

            break;
        default:
            state = Sidle;
        };
        break;
    case Sset:
        reg = in;
        switch (in)
        {
        case 'u':
        case 'U':
        case 'd':
        case 'D':
            state = Sinterger;
            break;
        case 's':
        case 'S':
            state = Ssetstandby;
            break;
        default:
            state = Sidle;
            break;
        }
        break;
    case Sgetstandby:
        if (in == ';')
        {
            if (save)
                Serial.println("Salvando");
            else
                Serial.println("Esquecendo");
        }
        state = Sidle;
        break;
    case Ssetstandby:
        switch (in)
        {
        case ';':
            state = Sidle;
            if (val[0] == '1')
                save=true;
            else
                save=false;
        case '1':
        case '0':
            val[0] = in;
            break;
        default:
            state = Sidle;
        }
        break;
    case Sinterger:
        if ('0' <= in && in <= '9')
        {
            cont = (cont == 3) ? cont = 0 : cont;
            val[cont++] = in;
        }
        else
        {
            state = Sidle;
            cont = 0;
            if (in == ';')
            {
                switch (reg)
                {
                case 'd':
                case 'D':
                    digitalPot.wiperDow(arrayToInteger(val),save);
                    Serial.print("DOW:");
                    Serial.println(arrayToInteger(val));
                    break;
                case 'u':
                case 'U':
                    digitalPot.wiperUp(arrayToInteger(val),save);
                    Serial.print("UP: ");
                    Serial.println(arrayToInteger(val));
                    break;

                default:
                    break;
                }
            }
        }
        break;
    }
}

uint8_t arrayToInteger(char *in)
{
    return ((uint8_t)in[0] - 48) * 100 + ((uint8_t)in[1] - 48) * 10 + ((uint8_t)in[2] - 48);
}