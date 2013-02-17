/*
 * pins.h
 *
 * Created: 12/7/2012 16:45:29
 *  Author: Andre Lucas
 
 This Header file contains all the macros, includes, function prototypes and even pin information for the main hikkikomori.c
 */
 
 #ifndef PINS_H_
 #define PINS_H_
 
  
 #define F_CPU 20000000  //Define the clock rate of the uC, which is needed by some dependencies like delay.h. Our board runs at 20MHz
 #define LIGHT_THRESHOLD 130 //Threshold for low light environment. Range 0-255.
 #define TIME_TURNING 250	//Time in ms for turning the robot when looking for darker regions.
 #define TIME_EXPLORE 1000	//Time for moving forward after having turned before probing for darker region again.
 
 
 #include <avr/io.h>		//Include Input Output pins library e.g. DDRB and PORTB and PINB registers
 #include <util/delay.h>	//Delay functions _delay_ms(miliseconds) and _delay_(microseconds) which puts the IC into an idle calculation for that specific amount of time. (It is basically a for loop counting nothing relevant)
 #include <avr/interrupt.h> //Needed for the bumper switch which will make use of an external hardware interrupt routine.
 #include "Motor_Driver.h"	//Contains the functions for driving the robot defined in Motor_Driver.c
 
 
 //Function Prototypes
 void ioinit(void);
 void analoginit(void);
 char whereDark(void); //Returns 0 for light lower than threshold, 1 for right darker or 2 for left darker.
 
 
 /**Behold the pin definitions:

 For ADC:

 ADC6 - Left CDS
 ADC7 - Right CDS */
 #define LeftCDS 0x06
 #define RightCDS 0x07 
 //////////////////////////////
 
 /*For Motors:

 Left Motor:
 PD5 and PD6

 Right Motor:
 PD3 and PB3
 */
 /////////////////////////
 
 /*For bumper switch:

 PD2(INT0) trigger on low
 /////////////////////////
 //Debug LED - PD1
*/

#endif /* PINS_H_ */