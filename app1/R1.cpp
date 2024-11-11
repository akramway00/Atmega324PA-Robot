#include "reception.h"

volatile bool gIsButtonPressed = false;
volatile bool gIsTimerExpired = false;

ISR (INT0_vect) 
{
    _delay_ms(DEBOUNCE_DELAY_MS);
    if (INT0_vect)
    {
        gIsButtonPressed = !gIsButtonPressed; 
    }
    EIFR |= (1 << INTF0);
}

ISR (TIMER1_COMPA_vect) 
{
    gIsTimerExpired = !gIsTimerExpired;
}

enum class State
{
    MOVING,
    WAITING,
    RECEIVING,
    SENDING
};

int main()
{
    Robot robot;
    Recepteur recep;
    robot.utile.interruptButtonInitialization(ANY);

    bool isMovingDone = false;
    bool is180Done = false;
    bool isSendingCompleted = false;

    Position position = TOP_NORTH;
    Facing facing;
    uint8_t distance;
    uint16_t secondMeasure = 0;
    int16_t measureDifference = 0;
    uint16_t counter = 0;

    State currentState = State::MOVING;

    distance = robot.measureDistance();
    if (distance < 57)
        facing = INSIDE;
    else
        facing = OUTSIDE;

    while (true)
    {
        switch (currentState)
        {
            case State::MOVING :
                while (!isMovingDone)
                {
                    distance = robot.measureDistance();
                    if (distance < 57)
                    {
                        robot.motor.moveForwardR1(55);
                    }
                    else if (distance > 57)
                    {
                        robot.motor.moveBackR1(55);
                    }
                    else
                    {
                        robot.motor.stopRobot();
                        isMovingDone = true;
                    }
                }
                
                distance = robot.measureDistance();
                while (measureDifference > -30 && measureDifference < 30)
                {
                    robot.motor.directionUpdate(false, RIGHT);
                    robot.motor.directionUpdate(true, LEFT);
                    robot.motor.adjustPwm_8b (50, 50);
                    secondMeasure = robot.measureDistance();
                    measureDifference = secondMeasure - distance;
                    distance = secondMeasure;
                    counter++;
                    _delay_ms(2);
                }
                robot.motor.turnLeftR1();
                _delay_ms(100);
                robot.motor.stopRobot();

                if (counter > COUNTER_VALUE_TURN180)
                {
                    is180Done = true;
                }
                position = robot.findPosition(facing, is180Done);
                _delay_ms(2000);
                currentState = State::WAITING;
                break;

            case State::WAITING :
                recep.isCompromised = false;
                recep.isStateEnd = false;
                robot.led.redLight();
                while (!gIsButtonPressed) {}
                robot.playSounds(HIGH_PITCHED_SOUND, HIGH_PITCHED_SOUND_REHEARSALS, HIGH_PITCHED_SOUND_DURATION_MS);
                currentState = State::RECEIVING;
                break;

            case State::RECEIVING :
                robot.led.lightOff();
                recep.isCompromised = false;
                recep.isStateEnd = false;
                recep.readSignal();

                if (recep.isCompromised == true)
                {
                    robot.playSounds(LOW_PITCHED_SOUND, LOW_PITCHED_SOUND_REHEARSALS, LOW_PITCHED_SOUND_DURATION_MS);
                    recep.isCompromised=false;
                    currentState = State::WAITING;
                }
                if (recep.isStateEnd == true)
                {
                    recep.isStateEnd=false;
                    currentState = State::SENDING;
                }

                break;

            case State::SENDING :
                robot.led.greenLight();
                _delay_ms(2000);
                while (!gIsButtonPressed) {}
                for (int i=0; i < recep.index; i++)
                {
                    robot.drawer.com.transmissionUART(recep.tableau[i]);
                }
                while (!isSendingCompleted)
                {
                    robot.drawer.drawMapR1(position, isSendingCompleted, recep.tableau);
                }
                break;
        }
    }
    return 0;
}