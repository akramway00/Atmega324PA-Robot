#include <robot.h>
#include <transmission.h>

volatile bool gIsInterruptButtonPressed = false;
volatile bool gIsWhiteButtonPressed = false;
volatile bool gIsTimerExpired = false;


ISR (INT0_vect) 
{
    _delay_ms(DEBOUNCE_DELAY_MS);
    if (INT0_vect)
    {
        gIsInterruptButtonPressed = !gIsInterruptButtonPressed; 
    }
    EIFR |= (1 << INTF0);
}

ISR (INT2_vect) 
{
    _delay_ms(DEBOUNCE_DELAY_MS);
    if (INT2_vect)
    {
        gIsWhiteButtonPressed = !gIsWhiteButtonPressed; 
    }
    EIFR |= (1 << INTF2);
}

ISR (TIMER1_COMPA_vect) 
{
    gIsTimerExpired = !gIsTimerExpired;
}

enum class State
{
    MOVING,
    WAITING,
    SENDING_IR,
    SENDING_RS232
};

int main()
{
    DDRA = 0x00;
    Robot robot;
    robot.utile.interruptButtonInitialization(ANY);
    robot.utile.whiteButtonInitialization(ANY);

    Emitter emit;
    uint8_t measureCounter = 0;
    uint8_t distanceCounter = 0;

    uint8_t nCorners = 0;
    uint8_t nSegments = 0;

    uint8_t sizes[6] = {};
    uint8_t locations[6] = {};
    uint8_t sides[6] = {};
    uint8_t messages[6] = {};
    uint8_t message = 0b00000000;

    bool isMovingDone = false;
    bool isSendingIRCompleted = false;
    bool isSendingRS232Completed = false;

    while (!isMovingDone)
    {
         switch (PINA & 0b01111100)
         {
            case S1_S3:
            case S1_S3_S4:
            case S1_S2_S3:
            case S1_S2_S3_S4:
                robot.motor.adjustCenter();
                gIsTimerExpired = false; 
                robot.timer.timerT1_1024(7812); 
                while (gIsTimerExpired == false)
                {
                    robot.motor.turnLeftBackR2();
                } 
                while((PINA & 0b01111100) != S1)
                {
                    robot.motor.turnLeftBackR2();
                }
                robot.motor.moveForward(100);
                _delay_ms(100);
                while((PINA & 0b01111100) != sensorsAllOff)
                {
                    robot.motor.adjustMovement();
                }
                robot.motor.stopRobot();
                isMovingDone = true;
                break;

            case S3_S5:
            case S2_S3_S5:
            case S3_S4_S5:
            case S2_S3_S4_S5:
                robot.led.redLight();
                robot.motor.adjustCenter();
                if ((PINA & 0b01111100) == sensorsAllOff)
                {
                    nCorners++;
                    distanceCounter = 0;
                    while ((PINA & 0b01111100) != S5)
                    {
                        robot.motor.turnRightR2();
                    }
                    break;
                }
                else 
                {
                    locations[nSegments] = distanceCounter;
                    if (nCorners == 1)
                    {
                        sides[nSegments] = 0;
                    }
                    else if (nCorners > 1)
                    {
                        sides[nSegments] = 1;
                    }
                    gIsTimerExpired = false;
                    robot.timer.timerT1_1024(7812); 
                    while (gIsTimerExpired == false)
                    {
                        robot.motor.turnRightR2();
                    }
                    gIsTimerExpired = false;
                    robot.timer.timerT1_1024(10000);
                    while ((PINA & 0b01111100) != S5 && gIsTimerExpired == false)
                    {
                        robot.motor.turnRightR2();
                    }
                    gIsTimerExpired = false;
                    robot.motor.stopRobot();
                    _delay_ms(500);
                    if ((PINA & 0b01111100) == sensorsAllOff)
                    {
                        while((PINA & 0b01111100) != S1)
                        {
                            robot.motor.turnLeftFrontR2();
                        }
                        sizes[nSegments++] = 2;
                    }
                    else
                    {
                        robot.motor.moveForward(100);
                        _delay_ms(100);
                        while((PINA & 0b01111100) != sensorsAllOff)
                        {
                            robot.motor.adjustMovement();
                        }
                    }
        
                }
                break;
            case sensorsAllOff:
                robot.led.redLight();
                while ((PINA & 0b01111100) != sensorsAllOn)
                {
                    robot.motor.moveBack(50);
                    gIsTimerExpired = false;
                    robot.timer.timerT1_1024(781);
                    while (gIsTimerExpired == false) {}
                    measureCounter++;
                    gIsTimerExpired = false;
                }
                sizes[nSegments++] = measureCounter;
                measureCounter = 0;
                break;
            case sensorsAllOn:
                robot.motor.moveForward(50);
                _delay_ms(1450);
                robot.motor.stopRobot();
                _delay_ms(300);
                gIsTimerExpired = false;
                robot.timer.timerT1_1024(7812); 
                while (gIsTimerExpired == false)
                {
                    robot.motor.turnLeftFrontR2();
                }
                gIsTimerExpired = false;
                while((PINA & 0b01111100) != S1)
                    robot.motor.turnLeftFrontR2();
                robot.motor.stopRobot();
                _delay_ms(500);
                break;
            default:
                robot.led.greenLight();
                robot.motor.moveForward(100);
                _delay_ms(100);
                while ((PINA & 0b01111100) == S1 || (PINA & 0b01111100) == S1_S2 || (PINA & 0b01111100) == S2 ||
                (PINA & 0b01111100) == S2_S3 || (PINA & 0b01111100) == S3 || (PINA & 0b01111100) == S3_S4 ||
                (PINA & 0b01111100) == S4 || (PINA & 0b01111100) == S4_S5 || (PINA & 0b01111100) == S5)
                {
                    robot.motor.adjustMovement();
                    gIsTimerExpired = false;
                    robot.timer.timerT1_1024(781);
                    while (gIsTimerExpired == false) {}
                    distanceCounter++;
                    gIsTimerExpired = false;
                }
                robot.led.lightOff();
                break;
                
            }
        }
        _delay_ms(30000);
        for (uint8_t i = 0; i < nSegments; i++)
        {
            if (sizes[i] != 0 && sizes[i] < 24)
                sizes[i] = 2;
            else if (sizes[i] >= 24 && sizes[i] < 29)
                sizes[i] = 4;
            else if (sizes[i] >= 29)
                sizes[i] = 6;
            robot.drawer.com.transmissionUART(sizes[i]);
        }
        robot.drawer.com.transmissionUART(255);
        for (uint8_t i = 0; i < nSegments; i++)
        {
            locations[i] = locations[i] / 2;
           
            robot.drawer.com.transmissionUART(locations[i]);
        }
        robot.drawer.com.transmissionUART(255);
        for (uint8_t i = 0; i < nSegments; i++)
        {
            message = 0b00000000;
            if (sides[i] == 1)
            {
                message |= 0b01000000;
            }
            message |= locations[i];
            messages[i] = message;
            robot.drawer.com.transmissionUART(messages[i]);
        }
        while (true)
        {
            robot.led.redLight();

            while (gIsInterruptButtonPressed == false && gIsWhiteButtonPressed == false) {} // attente
            if (gIsInterruptButtonPressed == true) 
            {
                robot.playSounds(80, 3, 50);
                robot.led.lightOff();
                while (!isSendingIRCompleted)
                {         
                    for(int i = 0 ; i< nSegments ; i++)
                    {
                        emit.sendSequence(messages[i]);
                        emit.sendSequence(sizes[i]);
                    }
                    emit.sendSequence(0);

                    isSendingIRCompleted = true;
                }
            }
            else if (gIsWhiteButtonPressed == true)
            {
                robot.led.lightOff();
                robot.drawer.drawMapR2(sizes, messages, isSendingRS232Completed);
                robot.led.greenLight();
                _delay_ms(5000);
            }
        }       
}
