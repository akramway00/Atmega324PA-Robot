#include "utilities.h"
#include "constants.h"


void Utilities::createDelayMs(int delay)
{
    int nIterations = delay >> BITSHIFT_FOUR;
    for (int i = 0; i < nIterations; i++)
    {
        _delay_ms(DELAY_MULTIPLIER);
    }
}

bool Utilities::isButtonPressed()
{
    int press = PIND & (1 << PD2);
    _delay_ms(DEBOUNCE_DELAY_MS);
    return press & PIND & (1 << PD2);
}

void Utilities::interruptButtonInitialization(Edge edge)
{
    cli ();
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    
    switch(edge)
    {
        case LOW:
            EICRA &= ~((1 << ISC01) | (1 << ISC00)); // Efface ISC01 et ISC00
            break;
        case ANY:
            EICRA = (EICRA & ~(1 << ISC01)) | (1 << ISC00); // Efface ISC01, met ISC00 à 1
            break;
        case FALLING:
            EICRA = (EICRA | (1 << ISC01)) & ~(1 << ISC00); // Met ISC01 à 1, efface ISC00
            break;
        case RISING:
            EICRA |= (1 << ISC01) | (1 << ISC00); // Met ISC01 et ISC00 à 1
            break;
    }
    sei ();

}

void Utilities::whiteButtonInitialization(Edge edge)
{
    cli ();
    DDRB &= ~(1 << PB2);
    EIMSK |= (1 << INT2);
    
    switch(edge)
    {
        case LOW:
            EICRA &= ~((1 << ISC21) | (1 << ISC20)); // Efface ISC01 et ISC00
            break;
        case ANY:
            EICRA = (EICRA & ~(1 << ISC21)) | (1 << ISC20); // Efface ISC01, met ISC00 à 1
            break;
        case FALLING:
            EICRA = (EICRA | (1 << ISC21)) & ~(1 << ISC20); // Met ISC01 à 1, efface ISC00
            break;
        case RISING:
            EICRA |= (1 << ISC21) | (1 << ISC20); // Met ISC01 et ISC00 à 1
            break;
    }
    sei ();
}
