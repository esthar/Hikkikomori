/*
 * hikkikomori.c
 *
 * Created: 12/7/2012 15:15:05
 *  Author: Andre Lucas
 
 This is the program for a little robot that will:
 Avoid lighted environments by probing two CDS resistors through the ADC channels;
 Turn towards darker regions and stop when colliding with a wall (most likely under a table).
 Hence its name: Hikkikomori.

 */ 

#include "hikkikomori.h"


int main(void){
	ioinit();
	analoginit();
	
	while(1){
		char direction = whereDark(); //whereDark returns 0 for light lower than threshold, 1 for right darker or 2 for left darker.
		
		if (direction==1){
			PORTD |= 1<<1;
			Motor_driveClockwise();
			_delay_ms(TIME_TURNING);
			
			Motor_driveForward();
			_delay_ms(TIME_EXPLORE);
			
		} else if (direction==2){
			PORTD &= ~(1<<1);
			Motor_driveCounterClockwise();
			_delay_ms(TIME_TURNING);
			
			Motor_driveForward();
			_delay_ms(TIME_EXPLORE);
			
		}
		_delay_ms(10);
	}

}

//Set outputs and inputs
void ioinit(void){
	DDRD |= 1<<1; //Debug LED PD1
	DDRB |= 1<<3; //Motor
	DDRD |= ((1<<5)|(1<<6)|(1<<3)); //Motor
}

//Configure ADC
void analoginit(void){
		
	ADMUX |= (1<<REFS0); //Set High voltage reference to pin AVcc with external cap at ARef pin.
	
	ADMUX |= 1<<ADLAR; //Left adjust the result so we only need to look at one register for the ADC result (Makes the 12bit value 8bit).
	
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN); //Set ADC clock (1/1024 of main clock) and enable the peripheral.
	
	ADCSRA |= 1<<ADSC; //Request start conversion to initialize the ADC and have it ready.
	
}

char whereDark(void){
	char left = 0;
	char right = 0;
	
	ADMUX &= 0xF0;   //Clear the older channel that was read. 0xF0 = 0b11110000.
	ADMUX |= LeftCDS; 
	ADCSRA |= (1<<ADSC); //Starts a new conversion.
	while(ADCSRA & (1<<ADSC)); //Wait until the conversion is done.
	left = ADCH;
	
	ADMUX &= 0xF0;   //Clear the older channel that was read.
	ADMUX |= RightCDS;
	ADCSRA |= (1<<ADSC); //Starts a new conversion.
	while(ADCSRA & (1<<ADSC)); //Wait until the conversion is done.
	right = ADCH;
	
	if ((left+right)<LIGHT_THRESHOLD){
		
		return 0;
		
	} else if (right<left){
		
		return 1;
		
	} else {
	
		return 2;
	}				
}