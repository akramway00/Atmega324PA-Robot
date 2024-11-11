#include "robot.h"

uint16_t Robot::measureDistance()
{
    uint16_t measure = 0;
    for (uint8_t i = 0; i < MEASURING_REHEARSALS; i++)
    {
        measure += can1.lecture(POS) >> BITSHIFT_TWO;
        _delay_ms(MEASURING_DELAY_MS);
    }
    return (measure/MEASURING_REHEARSALS);
}

uint16_t Robot::calculateDistance(Facing& facing)
{
    uint16_t firstDistance = measureDistance();
    _delay_ms(500);
    motor.turn180();
    _delay_ms(500);
    uint16_t secondDistance = measureDistance();
    if (firstDistance < secondDistance)
        facing = INSIDE;
    else 
        facing = OUTSIDE;
    return (firstDistance + secondDistance - ROBOT_SIZE)/2;
}

Position Robot::findPosition(Facing facing, bool is180Done)
{
    if (facing == INSIDE && is180Done == false)
        return TOP_SOUTH;
    else if (facing == INSIDE && is180Done == true)
        return BOTTOM_NORTH;
    else if (facing == OUTSIDE && is180Done == false)
        return TOP_NORTH;
    else
        return BOTTOM_SOUTH;
}

void Robot::playSounds(uint8_t note, uint8_t repetitions, int delay)
{
    double noteFrequency = sound.convertFrequency(note);
    uint8_t soundDuration = sound.convertSound(noteFrequency);
    for (int i = 0; i < repetitions; i++)
    {
            timer.timerT2_256(soundDuration);
            utile.createDelayMs(delay);
            timer.stopTimer2();
            utile.createDelayMs(delay);
    }
}

void Robot::flashGreenLight5Hz()
{
    led.greenLight();
    _delay_ms(FLASH_GREENLIGHT_5HZ_DELAY_MS);
    led.lightOff();
    _delay_ms(FLASH_GREENLIGHT_5HZ_DELAY_MS);
}
