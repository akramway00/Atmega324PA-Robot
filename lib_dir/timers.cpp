#include "timers.h"

void Timer::timerT0_1024(uint8_t duree)
{
    TCNT0 = 0;

    OCR0A = duree;

    TCCR0A = (0 << WGM00) | (1 << WGM11);

    TCCR0B = (1 << FOC0A) | (0 << WGM02) | (0 << CS02) | (1 << CS01) | (0 << CS00);
    
    TIMSK0 = (1 << OCIE0A);
}

void Timer::timerT0_256(uint8_t duree)
{
    TCNT0 = 0;

    OCR0A = duree;

    TCCR0A |= (1 << WGM01) | (1 << COM0A0);

    TCCR0B |= (1 << CS00) | (1 << CS02);
}

void Timer::timerT1_1024(uint16_t duration)
{
    TCNT1 = 0;

    OCR1A = duration;

    TCCR1A |= (1 << COM1A0) | (1 << COM1A1);

    TCCR1B |= (1 << WGM12);

    TCCR1B |= (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A);
}

void Timer::timerT2_256(uint8_t duration)
{
    TCNT2 = 0;

    OCR2A = duration;

    TCCR2A |= (1 << WGM21) | (1 << COM2A0);

    TCCR2B |= (1 << CS21) | (1 << CS22); // Prescaler de 256
}

void Timer::stopTimer0()
{
    TCCR0A &= ~(1 << COM0A0);
}

void Timer::stopTimer1()
{
    TCCR1A = 0; 
    TCCR1B = 0;
}

void Timer::stopTimer2()
{
    TCCR2A = 0;
    TCCR2B = (0 << CS22) | (0 << CS21) | (0 << CS20);
}

void Timer::startTimer1_64(uint16_t duration) 
{
    TCNT1 = 0;
    OCR1A = duration;
    TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
    TCCR1B &= ~(1 << WGM13);
    TCCR1B |= (1 << WGM12); 
    // prescaler de 64
    TCCR1B &= ~(1 << CS12);
    TCCR1B |= (1 << CS10) | (1 << CS11);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

void Timer::stopTimer1_64() 
{
    TIMSK1 &= ~(1 << OCIE1B);
    cli();
}

