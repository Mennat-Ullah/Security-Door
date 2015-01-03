#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef PWM_H_
#define PWM_H_

#define	SingleTimerCycle 64		// this is the periodic time of the timer as we are using pre-scalar 1024

// This function generates a wave with specific periodic time and duty cycle
// Param Period : <Input> this parameters defines the periodic time for the required wave in (us)
// Param iDutyPercentage: <Input> this parameters defines the percentage of the High part : restriction range from 1 to 99
void StartWaveGeneration(int Period, int iDutyPercentage)
{
	DDRD |= 0b00100000;		// set OC0B as Output pin.
	
	TCCR0A = 0b00100011;	// WGM0[2..0] = 7	(fast PWM mode)
	TCCR0B = 0b00001101;	// CS0[2..0] = 5    (f/1024)
							// COM0A[1,0] = 0	(do not compare with A)		
							// COM0B[1,0] = 2   (compare with B and clear on match and set on bottom)
	
	// we need to set the proper value for OCR0A now to be half of the Periodic Time
	OCR0A = Period / SingleTimerCycle;
	OCR0B = OCR0A * iDutyPercentage / 100;
}

void StopWaveGeneration()
{
	TCCR0B &= 0xF8;
}

void PWMInti ()
{	
	 // enable Interrupt 
	   // 3amaten ay interrupt 
		  sei(); 
		  
       // enable Interrupt for timer 1
	   // 3alshan ye5ale timer1 yeb3at interrupt
          TIMSK1 |= (1 << TOIE1);

       // Start timer at Fcpu/16
       // bash3'alo we a7aded el frecunce 
          TCCR1B |= ((1 << CS12) | (1 << CS10)); 

       //Initialize Counter , 2^ 16 - 16000 = 49536 
	   // 3alshan howa be yo2f uk] max beta3o 2^16
		  TCNT1 = (2^16 - 1000); //0x0000C180; //49536
		  
}
#endif /* PWM_H_ */