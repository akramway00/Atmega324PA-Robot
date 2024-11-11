/*
 * Nom: Akram Lourhmati, Ayoub Marfouk, Fares Laadjel, Chems-Eddine Kardoussi

 * Groupe 121122
 * 
 * lib_dir LED.h
 * 
 * Description: Declaration d'une classe LED, qui possede les methodes necessaires a allumer la led en vert, 
 *              en rouge, en ambre et l'eteindre.
 * 
 * Identifications matérielles : Nous allons connecter la DEL aux deux premieres broches du PORT B.
 * 
 */


#include "constants.h"

class LED 
{
public :
    
    LED();
    void redLight() const;
    void greenLight() const;
    void lightOff() const;
    void amberLight(uint16_t AMBERLIGHT_TIME_MS) const;
};