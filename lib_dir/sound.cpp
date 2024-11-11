#include "sound.h"

Sound::Sound()
{
    DDRD |= (1 << PD6) | (1 << PD7);
    PORTD |= (1 << PD6) | (1 << PD7);
}

double Sound::convertFrequency(uint8_t note)
{
    for (uint8_t i = 0; i < NUMBER_OF_NOTES; i++)
    {
        if (note == NOTES[i])
        {
            return FREQUENCIES[i];
        }
    }
    return NOTE_NOT_FOUND;
}

uint8_t Sound::convertSound(double frequency)
{
    uint8_t duration = F_CPU / (2 * SOUND_PRESCALER * frequency) - 1;
    return duration;
}