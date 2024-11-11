/*
 * Nom: Akram Lourhmati, Ayoub Marfouk, Fares Laadjel, Chems-Eddine Kardoussi

 * Groupe 121122
 * 
 * lib_dir comUART.h
 * 
 * Description: Declaration d'une classe comUART, qui possede un constructeur et les methodes necessaires a 
 *              la transmission et l'envoi de donnees.
 * 
 * Identifications matérielles : Nous aurons besoin de l'USART de l'ATmega324PA, a l'aide du protocole RS232
 *                               qui relie le PC au robot.
 * 
 */


#include "constants.h"

class comUART
{
public :

    comUART();
    void transmissionUART(uint8_t data);
    uint8_t receptionUART();
    void sendMessage(const char* message);
};

