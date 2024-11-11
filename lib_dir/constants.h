/*
 * Nom: Akram Lourhmati, Ayoub Marfouk, Fares Laadjel, Chems-Eddine Kardoussi
 *
 * Groupe 121122
 * 
 * lib_dir constants.h
 * 
 * Description: Contient toutes les constantes necessaires aux autres fichiers, qui dependent donc de celle-ci
 * 
 * Identifications matérielles : Aucune
 * 
 */


#pragma once

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "memoire_24.h"

const uint8_t DEBOUNCE_DELAY_MS = 10;
const uint8_t AMBER_LIGHT_DELAY_MS = 1;
const uint16_t CYCLES_FOR_50_MS = 390;

const uint8_t LEFT = DDB6; // configuration de la roue gauche sur DDR6
const uint8_t RIGHT = DDB1; // configuration de la roue droite sur DDR7

const uint8_t PWM_TOPVALUE_8b = 255;
const uint8_t PWM_BOTTOMVALUE_8b = 0;

const uint8_t SWITCH_TIME = 15;
const uint8_t BITSHIFT_TWO = 2;

const uint8_t MAX_INTERVAL = 230;
const uint8_t MIN_INTERVAL = 170;
const uint8_t POSITION = 0;

const uint8_t DELAY_MULTIPLIER = 16;
const uint8_t BITSHIFT_FOUR = 4;
const uint8_t TRANSMISSION_DELAY = 5;
const uint16_t AMBERLIGHT_TIME_MS = 2000;
const uint16_t AMBER_ADC = 1000;

const uint16_t ONE_SECOND_DELAY_MS = 1000;

// Constantes pour les sons

const uint16_t SOUND_PRESCALER = 256;
const uint8_t NUMBER_OF_NOTES = 37;
const double NOTE_NOT_FOUND = 0.0;

const int NOTES[37] =
{
    45,46,47,48,49,50,51,52,53, 
    54,55,56,57,58,59,60,61,62,
    63,64,65,66,67,68,69,70,71,
    72,73,74,75,76,77,78,79,80,
    81
};

const double FREQUENCIES[37] = 
{
    110,116.54,123.47,130.81,138.59,146.83,
    155.56,164.81,174.61,185.00,196.00,207.65,
    220,233.08,246.94,261.63,277.18,293.66,311.13,
    329.63,349.23,369.99,392.00,415.30,440,
    466.16,493.88,523.25,554.37,587.33,622.25,
    659.26,698.46,739.99,783.99,830.61,880
};

// Constantes pour les instructions

const uint16_t START_ADDRESS = 0x0000;
const uint8_t DEFAULT_ITERATIONS = 1;
const uint8_t WAIT_INSTRUCTION_DELAY_MS = 25;
const uint8_t GREEN_OPERAND = 1;
const uint8_t RED_OPERAND = 2;

// Constantes pour R1 

const uint8_t MEASURING_REHEARSALS = 10;
const uint8_t MEASURING_DELAY_MS = 10;
const uint8_t POS = 0;
const uint8_t MOVING_POURCENTAGE_R1 = 55;
const int8_t DIFFERENCE_MAX = 15;
const int8_t DIFFERENCE_MAX_NEGATIVE = -15;
const uint8_t COUNTER_DELAY_MS = 2;
const uint8_t STOP_ROBOT_DELAY_MS = 70;
const uint8_t COUNTER_VALUE_TURN180 = 25;
const uint8_t FLASH_GREENLIGHT_5HZ_DELAY_MS = 125;
const uint8_t ROBOT_SIZE = 80;
const uint8_t HIGH_PITCHED_SOUND = 80;
const uint8_t HIGH_PITCHED_SOUND_REHEARSALS = 3;
const int HIGH_PITCHED_SOUND_DURATION_MS = 50;
const uint8_t LOW_PITCHED_SOUND = 47;
const uint8_t LOW_PITCHED_SOUND_REHEARSALS = 1;
const int LOW_PITCHED_SOUND_DURATION_MS = 1000;


enum Facing
{
    INSIDE, OUTSIDE
};

enum Position 
{
    TOP_SOUTH, TOP_NORTH, BOTTOM_SOUTH, BOTTOM_NORTH
};

// Constantes pour le suivi de ligne

enum Instruction
{
    PRESS_BUTTON,
    GO_FRONT,
    CORNER,
    SEGMENT,
    REPLACE,
    WAIT,
    SEND
};

const uint8_t S1 = 0b00000100;            
const uint8_t S1_S2 = 0b00001100;         
const uint8_t S2 = 0b00001000;
const uint8_t S2_S3 = 0b00011000;         
const uint8_t S3 = 0b00010000;            
const uint8_t S3_S4 = 0b00110000;         
const uint8_t S4 = 0b00100000;              
const uint8_t S4_S5 = 0b01100000;         
const uint8_t S5 = 0b01000000;            

const uint8_t S1_S2_S3  = 0b00011100;      
const uint8_t S1_S3 = 0b00010100;         
const uint8_t S1_S3_S4 = 0b00110100;      
const uint8_t S1_S2_S3_S4 = 0b00111100;   

const uint8_t S3_S4_S5 = 0b01110000;      
const uint8_t S3_S5 = 0b01010000;         
const uint8_t S2_S3_S5 = 0b01011000;      
const uint8_t S2_S3_S4_S5 = 0b01111000;   
const uint8_t S1_S2_S4_S5 = 0b01101100;   

const uint8_t sensorsAllOff = 0b00000000; 
const uint8_t sensorsAllOn = 0b01111100;


// Constantes pour la cartographie

struct Line {
    uint8_t firstChar;
    uint8_t location;
    uint8_t lastChar;
};


// caracteres unicodes pour les roues du robot
const uint8_t wheels[] = {0xE2, 0x96, 0x93};
const uint8_t diagonalTopLeft = 0xB1;
const uint8_t diagonalTopRight = 0xB2;



// caracteres unicode pour le contour du dessin (linee simple mince)
const uint8_t borderTopLeft = 0x8C;
const uint8_t borderTopRight = 0x90;
const uint8_t borderBottomLeft = 0x94;
const uint8_t borderBottomRight = 0x98;
const uint8_t borderHorizontal = 0x80;
const uint8_t borderVertical = 0x82;

// caracteres unicode pour la boite (linee simple epaisse)
const uint8_t r1TopLeft = 0x8f;
const uint8_t r1TopRight = 0x93;
const uint8_t r1BottomLeft = 0x97;
const uint8_t r1BottomRight = 0x9b;
const uint8_t r1Horizontal = 0x81;
const uint8_t r1Vertical = 0x83;

// caracteres unicode pour le trajet de R2 (linee double)
const uint8_t r2TopLeft = 0x94;
const uint8_t r2TopRight = 0x97;
const uint8_t r2BottomLeft = 0x9A;
const uint8_t r2BottomRight = 0x9D;
const uint8_t r2Horizontal = 0x90;
const uint8_t r2Vertical = 0x91;
const uint8_t r2TopRightLeft = 0xA6;
const uint8_t r2BottomRightLeft = 0xA9;
const uint8_t r2VerticalLeft = 0xA3;


const uint8_t MATRIX_COL = 101;
const uint8_t MATRIX_LIG = 26;

// CONSTANTE bords des dessins

const uint8_t boxColumnLeft = 4;
const uint8_t boxColumnRight = 33;
const uint8_t boxLineUp = 2;
const uint8_t boxLineDown = 24;
const uint8_t boxOpeningLineUp = 11;
const uint8_t boxOpeningLineDown = 15;
const uint8_t r2ColumnLeft = 40;
const uint8_t r2ColumnRight = 95;
const uint8_t r2LineUp = 4;
const uint8_t r2LineDown = 22;
const uint8_t r2EndLine = 13;
const uint8_t r2EndLineColumn = 36;
