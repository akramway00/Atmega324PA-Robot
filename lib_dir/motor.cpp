#include "motor.h"

#define VAL_F 0xFF

void Motor::directionUpdate(bool direction, uint8_t robotWheel)  // configuration sur le PORT D , robotWheel -> correspond a la roue droite ou la roue gauche
{
    if (direction)
    {
        PORTB &= VAL_F ^ (1 << robotWheel);
    }
    else
    {
        PORTB |= (1 << robotWheel);
    }
}

double Motor::adjustCompareValue(uint8_t power)
{
    double pourcentage = power / 100.0;
    double duration = PWM_TOPVALUE_8b - PWM_TOPVALUE_8b * pourcentage;
    return duration;
}

void Motor::adjustPwm_8b (uint8_t powerA, uint8_t powerB)
{
    DDRB |= (1 << DDB1) | (1 << DDB3) | (1 << DDB4) | (1 << DDB6);
    OCR0A = adjustCompareValue(powerA);
    OCR0B = adjustCompareValue(powerB);
    TCCR0A = (1 << WGM00) | (0 << WGM01) | (1 << COM0A0) | (1 << COM0A1) | (1 << COM0B0) | (1 << COM0B1);
    TCCR0B = (0 << WGM02) | (0 << CS02) | (1 << CS01) | (0 << CS00);
}

void Motor::moveForward(uint8_t power)  // active les 2 roues , ce qui va faire avancer le robot vers l'avant
{
    directionUpdate(true,RIGHT);
    directionUpdate(true,LEFT);
    adjustPwm_8b (0.97 * power, power);
}

void Motor::moveBack(uint8_t power)
{
    directionUpdate(false, RIGHT);
    directionUpdate(false, LEFT);
    adjustPwm_8b (power, 0.97 * power);
}

void Motor::moveForwardR1(uint8_t power)  
{
    directionUpdate(true,RIGHT);
    directionUpdate(true,LEFT);
    adjustPwm_8b (power, 0.73*power);
}

void Motor::moveBackR1(uint8_t power)
{
    directionUpdate(false, RIGHT);
    directionUpdate(false, LEFT);
    adjustPwm_8b (power, 0.60*power);
}

void Motor::turnLeft90()
{
    stopRobot();
    _delay_ms(500);
    directionUpdate(true, RIGHT);
    directionUpdate(false, LEFT);
    adjustPwm_8b(0.97*50, 50);
    _delay_ms(1200); // A VÉRIFIER AVEC LE ROBOT
    stopRobot();
}

void Motor::turnRight90()
{
    stopRobot();
    _delay_ms(500);
    directionUpdate(false, RIGHT);
    directionUpdate(true, LEFT);
    adjustPwm_8b(0.97*50, 50);
    _delay_ms(1200); // A VÉRIFIER AVEC LE ROBOT
    stopRobot();
}

void Motor::turn180()
{
    turnRightR1();
    _delay_ms(2250);
    stopRobot();
}

void Motor::turnRightR1() // Sur place
{
    directionUpdate(false, RIGHT);
    directionUpdate(true, LEFT);
    adjustPwm_8b (55, 55);
}

void Motor::turnLeftR1() // Sur place
{
    directionUpdate(true, RIGHT);
    directionUpdate(false, LEFT);
    adjustPwm_8b (55, 55);
}

void Motor::turnRightR2() // Turn right en reculant
{
    directionUpdate(false, RIGHT);
    directionUpdate(false, LEFT);
    adjustPwm_8b(55, 0);
}

void Motor::turnLeftFrontR2() // Turn Left en reculant
{
    directionUpdate(true, RIGHT);
    directionUpdate(true, LEFT);
    adjustPwm_8b(55, 0);
}

void Motor::turnLeftBackR2() // Turn Left en reculant
{
    directionUpdate(false, RIGHT);
    directionUpdate(false, LEFT);
    adjustPwm_8b(0, 55);
}

void Motor::adjustCenter()
{
    moveForward(50);
    _delay_ms(1750); // À modifier
    stopRobot();
}

void Motor::stopRobot()
{
    TCCR0A = 0;
    TCCR0B = 0;
}

void Motor::adjustMovement()
{
    directionUpdate(true,RIGHT);
    directionUpdate(true,LEFT);
    switch(PINA & 0b01111100)
    {
            case S1:
                adjustPwm_8b(50, 30);
                break;

            case S1_S2:
                adjustPwm_8b(50, 35);
                break;

            case S2:
                adjustPwm_8b(50, 40);
                break;

            case S2_S3:
                adjustPwm_8b(50, 48);
                break;

            case S3:
                moveForward(50);
                break;

            case S3_S4:
                adjustPwm_8b(45, 50);
                break;

            case S4:
                adjustPwm_8b(40, 50);
                break;

            case S4_S5:
                adjustPwm_8b(35, 50);
                break;

            case S5:
                adjustPwm_8b(30, 50);
                break;
    }
}



