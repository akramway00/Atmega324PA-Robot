/*
 * Nom: Akram Lourhmati, Ayoub Marfouk, Fares Laadjel, Chems-Eddine Kardoussi
 *
 * Groupe 121122
 * 
 * lib_dir draw.h
 * 
 * Description: declaration de la classe DrawMap, contenant plusieurs methodes permettant
 *              la cartographie. Les deux robots utilisent les deux fonctions de transmission
 *              vers le RS232 en UTF-8 a l'aide de la recurrence des
 * 
 * Identifications matérielles : Utilisation de la PD2 pour les methodes utilisant le bouton-poussoir
 * 
 *
 */
// #include <reception.h>
#include "constants.h"
#include "comUART.h"
// Recepteur recepteur;
class DrawMap {
public:
    void printSimpleLine(uint8_t data);
    void printDoubleLine(uint8_t data);
    void drawMapR2(uint8_t sizes[], uint8_t messages[], bool& isSendingCompleted);
    void writeName();
    void drawMapR1(Position robotPos, bool& isSendingCompleted, uint8_t table[]);
    comUART com;
};