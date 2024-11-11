#include "constants.h"

class Sound
{
public:
    Sound();
    double convertFrequency(uint8_t note);
    uint8_t convertSound(double frequency);
};