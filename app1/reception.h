#include <robot.h>
#include <stdint.h>
#include <util/crc16.h>

const int DEVIATION = 2;

class Recepteur
{
public:
    comUART com;
    uint8_t timer = 0;
    int step=0;
    int message=0;
    bool startReceive = false;

    int index = 0;
    uint16_t messageVerifier = 0;
    uint8_t tableau[100];

    bool isCompromised = false;
    bool isStateEnd = false;

    Recepteur()
    {
        DDRA &= ~(1 << PA3);
    }

    bool checkPin()
    {
        return !(PINA & (1 << PA3));
    }

    bool verificationCRC16(uint16_t message)  // verification du message recu avec le protocole CRC-16
    {
        uint8_t instruction7bits = message >> 5;
        uint8_t adress5bits = message & 0x1f;
        uint16_t crc = 0xFFFF;
        uint8_t crc_inst = _crc16_update(crc,instruction7bits);
        crc_inst = crc_inst >> 3;
        return adress5bits == crc_inst;
    }

    void addZero(int& message)
    {
        message<<=1;
    }

    void addOne(int& message)
    {
        message<<=1;
        message|=1;
    }

    void readSignal() 
    {
        message = 0;
        step=0;
        while (!checkPin()) {}; //on reste en standby le temps que c'est eteint
            while(true)
            {
                while(checkPin())
                {
                    _delay_us(120);
                    timer++;
                }
                if (timer<=7 && timer >=5)
                {
                    timer=0;
                    addZero(message);
                }

                if (timer<=13 && timer >=11)
                {
                    timer=0;
                    addOne(message);
                }
                step++;
                if (step==12)
                {
                    break;
                }
                while (!checkPin());
        }

        if(verificationCRC16(message))
        {
            messageVerifier = message >> 5;
              
            if(messageVerifier == 0)
            {
                isStateEnd = true;
            }

            else
            {
                tableau[index++] = messageVerifier;
            }
        }

        else
        {
            messageVerifier = 0;
            index = 0;
            isStateEnd = true;
            isCompromised = true;
        }
    }    
};




