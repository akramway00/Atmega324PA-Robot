#include <util/crc16.h>
#include <stdint.h>

void pmw40KHZ()
{
  DDRD |= (1 << PD5);     

  TCCR1B |= (1 << WGM12); 

  TCCR1B |= (1 << CS10);

  OCR1A = 104; 
}

class Emitter
{
public:
    Emitter()    
    {
        pmw40KHZ();
    }

    void sendLongPulsion()
    {
        TCCR1A |= (1 << COM1A0); 
        _delay_us(1200);
        stopPulsion();
    }

    void sendShortPulsion()
    {
        TCCR1A |= (1 << COM1A0);
        _delay_us(600);
        stopPulsion();
    }

    void sendFull()
    {
        TCCR1A |= (1 << COM1A0);
    }

    void sendGap()
    {
        _delay_ms(GAP);
    }

    void sendBits(bool bitVal)
    {
        if (bitVal) 
        {
            sendLongPulsion();
            sendGap();
        }
        else
        {
            sendShortPulsion();
            sendGap();
        }
    }

    void stopPulsion()
    {    
        TCCR1A &= ~(1 << COM1A0);
    }

    void startPulsion()
    {
        TCCR1A |= (1 << COM1A0); 
        _delay_us(2400);
        stopPulsion();
        sendGap();
    }

    uint8_t  calculerCRC ( uint8_t sequence)
    {
        uint16_t crc = 0xFFFF;
        crc = _crc16_update(crc,sequence);
        return (uint8_t)(crc);
    }

    uint16_t makeSequence(uint8_t sequence)
    {
        uint8_t instruction7bits = sequence & 0x7F;
        uint8_t sequence_crc = calculerCRC(instruction7bits);
        sequence_crc = sequence_crc >> 3;
        uint16_t resultat = (uint16_t)(instruction7bits) << 5 | sequence_crc;
        return resultat;
    }

    void sendSequence(uint8_t sequence) 
    {
        uint16_t newSequence = makeSequence(sequence);
        for (int i = 11; i >= 0; i--) 
        {
            bool bitValue = (newSequence >> i) & 1;
            sendBits(bitValue);
        }
    }

private:
    static constexpr double SHORT_PULSE = 0.6; // Durée pour un bit 0
    static constexpr double LONG_PULSE = 1.2; // Durée pour un bit 1
    static constexpr double START = 2.4; // Durée de la pause entre les paquets
    static constexpr double  GAP = 0.6; // Durée de la pause entre les paquets
};


