/*
 * Nom: Akram Lourhmati, Ayoub Marfouk, Fares Laadjel, Chems-Eddine Kardoussi
 *
 * Groupe 121122
 * 
 * lib_dir timers.h
 * 
 * Description: Declaration de la classe Timer, qui possede deux horloges et deux methodes par horloge a implementer.
 *              Une pour creer le timer, avec un parametre dependant d'un prescale de 1024, et une deuxieme pour
 *              arreter le timer.
 * 
 * Identifications matérielles : Aucune
 */

#include "constants.h"


class Timer
{
public:

    void timerT0_256(uint8_t duree);
    void timerT0_1024(uint8_t duration);
    void timerT1_1024(uint16_t duration);
    void timerT2_256(uint8_t duration);

    void stopTimer0();
    void stopTimer1();
    void stopTimer2();

    void startTimer1_64(uint16_t duration);
    void stopTimer1_64();



};
