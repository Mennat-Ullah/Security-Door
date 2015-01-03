#include "lcd.h"
#include "KeyPad.h"
#include "PWM.h"
#include "Music.h"
#include <avr/io.h>
#include <avr/interrupt.h>

char Userpassword[3] ;
char SysPASSWORD[3] = "123" ;
uint8_t pass[]="pass:";
uint8_t wpass[]="Wrong password ";

//PWM
int i=0;
int melody[] = {  CNote,  bNote,  gNote,  CNote,  bNote, eNote,  RNote,  CNote,  cNote,  gNote, aNote, CNote };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
int MAX_COUNT = sizeof(melody) / sizeof(int); // Melody length, for looping.
long tempo = 100;   // Set overall tempo
int pause = 10;     // Set length of pause between notes
// end PWM

void checkpass() ;

int main(void)
{
	uint8_t keys[]="D#0*C987B654A321";
	lcd_init_4d();                                 
	lcd_write_string_4d(pass);
	int countpass = 0 ;	
	while(1)
	{
		uint8_t index =GetKeyPressed();				
		if(index==12)
		{
			lcd_write_instruction_4d(lcd_Clear);
			lcd_write_string_4d(pass);
			_delay_us(20000);
			countpass = 0;
		}
		else if(index!=20)
		{
				lcd_write_character_4d( keys[3]);
				Userpassword[countpass] = keys[index] ;
				countpass = countpass +1;
				if (countpass == 3)
				{
					checkpass();
					countpass = 0;
				}
				//_delay_us(1000000);
				_delay_us(20000);
		}
	}	
	//lcd_write_instruction_4d(lcd_SetCursor | lcd_LineTwo);
	_delay_us(80);   
	return 0;
}

void checkpass() 
{
	lcd_write_instruction_4d(lcd_Clear);
			
			
			int p , boolen = 1 ;
			for( p = 0 ; p < 3 ; ++ p )
			{
				if(Userpassword[p] != SysPASSWORD[p] )
					boolen = 0 ;
			}
			
			if (boolen)
			{
				PWMInti();
				DDRB |= 0b000011 ;
				DDRD |= 0b00110000 ;
				
				PORTB &= 0b111101 ;
				PORTB |= 0b000001 ;
				PORTD |= 0b00010000 ;
				
				while( i!= MAX_COUNT-1 )
				{
				StartWaveGeneration(melody[i], 50);
				_delay_us(10000);
	            StopWaveGeneration();
				}		
				
			}
			else
			{
				lcd_write_string_4d(wpass);
				_delay_us(10000);
				//_delay_us(1000);
				//lcd_write_string_4d(pass);
				DDRB |= 0b000011 ;
				DDRD |= 0b01010000 ;
				
				PORTB &= 0b111110 ;
				PORTB |= 0b000010 ;
				PORTD |= 0b01010000 ;
				//PORTD6 = 1; // for buzeel 
				
			}
			lcd_write_instruction_4d(lcd_Clear);
				lcd_write_string_4d(pass);
	
}


ISR(TIMER1_OVF_vect)
{
    TCNT1 = (2^16 - 1000) ; //0x0000C180;
	i++ ;
	if( i == MAX_COUNT )
	    i=0;		
		
}