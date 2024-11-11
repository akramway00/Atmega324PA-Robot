#include "comUART.h"
#include "constants.h"

comUART::comUART()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;

    UCSR0A |= (1 << UDRE0);

    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void comUART::transmissionUART(uint8_t data) // Du USART vers le PC
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

uint8_t comUART::receptionUART()
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void comUART::sendMessage(const char* message)
{
    int i=0;
    while(message[i] != '\0')
    {
        comUART::transmissionUART(message[i++]);
    }
}
