#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define KEYPAD_PORT PORTD
#define KEYPAD_DDRR  DDRD
#define KEYPAD_DDRC  DDRB
#define KEYPAD_PIN  PIND
uint8_t  GetKeyPressed()
{
    uint8_t r,c;
    KEYPAD_PORT|= 0X0F;
    for(c=0;c<4;c++)
    {
        KEYPAD_DDRC&=~(0XFF);
        KEYPAD_DDRR&=~(0XFF);
        KEYPAD_DDRC|=(0X20>>c);
        for(r=0;r<4;r++)
        {
            if(!(KEYPAD_PIN & (0X08>>r)))
            {
                return r*4+c;
            }
        }
    }
	return 20;
}