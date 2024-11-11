#include "can.h"
#include "constants.h"
#include "LED.h"
#include "memoire_24.h"
#include "motor.h"
#include "sound.h"
#include "timers.h"
#include "utilities.h"
#include "draw.h"

class Robot
{

public :

    uint16_t measureDistance();
    uint16_t calculateDistance(Facing& facing);
    Position findPosition(Facing facing, bool is180Done);
    void playSounds(uint8_t note, uint8_t repetitions, int delay);
    void flashGreenLight5Hz();
    void followLine(bool& isMovingDone);
    // void convertSizesToType(uint8_t sizes[]);
    // void convertDistancesToCaracters(uint8_t locations[]);
    // void createMessage(uint8_t nSegments, uint8_t locations[]);

    can can1;
    LED led;
    Memoire24CXXX memory;
    Motor motor;
    Sound sound;
    Timer timer;
    Utilities utile;
    DrawMap drawer;
    
};