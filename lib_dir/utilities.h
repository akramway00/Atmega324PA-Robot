/*
 * Nom: Akram Lourhmati, Ayoub Marfouk, Fares Laadjel, Chems-Eddine Kardoussi
 *
 * Groupe 121122
 * 
 * lib_dir utilities.h
 * 
 * Description: declaration d'une enumeration Edge, servant a un switch case a implementer dans la
 *              fonction utilisant un parametre du meme type. Declaration de la classe Utilities
 *              qui possede trois fonctions a implementer.
 * 
 * Identifications matérielles : Utilisation de la PD2 pour les methodes utilisant le bouton-poussoir
 * 
 *
    Tableau a etat :

    | État Courant | Sortie 2 - ISC01 | Sortie 1 - ISC00 | Prochain état |
    |:------------:|:----------------:|:----------------:|:-------------:|
    |      LOW     |         0        |         0        |       -       |
    |      ANY     |         0        |         1        |       -       |
    |    FALLING   |         1        |         0        |       -       |
    |    RAISING   |         1        |         1        |       -       |

 */

#include "constants.h"

enum Edge { LOW, ANY, FALLING, RISING };



class Utilities {
public: 
    void createDelayMs(int delay);
    bool isButtonPressed();
    void interruptButtonInitialization(Edge edge);
    void whiteButtonInitialization(Edge edge);


};