/*
 * Nom: Akram Lourhmati, Ayoub Marfouk, Fares Laadjel, Chems-Eddine Kardoussi
 *
 * Groupe 121122
 * 
 * lib_dir motor.h
 * 
 * Description: Declaration de la classe Motor, qui contient plusieurs methodes servant a la 
 *              gestion des roues, ou plus precisement du PWM qui controle la puissance
 *              d'execution de chacune des roues.
 * 
 * Identifications matérielles : broches du PORT D et la paire de roues
 */

#include "constants.h"

class Motor
{
public:
    void directionUpdate(bool direction, uint8_t robotWheel);
    double adjustCompareValue(uint8_t power);
    void adjustPwm_8b (uint8_t powerA, uint8_t powerB);

    void moveForward(uint8_t power);
    void moveBack(uint8_t power);
    void moveForwardR1(uint8_t power);
    void moveBackR1(uint8_t power);

    void turnRight90();
    void turnLeft90();
    void turn180();
    void turnRightR1();
    void turnLeftR1();
    void turnRightR2();
    void turnLeftBackR2();
    void turnLeftFrontR2();

    void adjustCenter();
    void adjustMovement();

    void stopRobot();
};


