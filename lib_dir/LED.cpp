#include "LED.h"
#include "constants.h"

LED::LED()
{
    DDRC |= (1 << PC2) | (1 << PC3);
}

void LED::greenLight() const
{
    PORTC |= (1 << PC2);
    PORTC &= ~(1 << PC3);
}

void LED::redLight() const
{
    PORTC &= ~(1 << PC2);
    PORTC |= (1 << PC3);    
}

void LED::lightOff() const 
{
    PORTC &= ~(1 << PC2);
    PORTC &= ~(1 << PC3);
}

void LED::amberLight(uint16_t AMBERLIGHT_TIME_MS) const 
{
    uint16_t rehearsal = AMBERLIGHT_TIME_MS/(SWITCH_TIME*2);
    for (uint16_t i=0; i < rehearsal; i++)
    {
        redLight();
        _delay_ms(SWITCH_TIME);
        greenLight();
        _delay_ms(SWITCH_TIME);
    }
}

