/*
 * CFile1.c
 *
 * Created: 2/14/2013 9:45:08 PM
 *  Author: Andre Lucas
 */ 

 /*Truth table for each motor:
 1 1 - Brake
 0 1 - Forward
 1 0 - Reverse
 0 0 - Coast
 Mode 0-Coast; 1-Forward; 2-Reverse; 3-Brake
 */
 
 #include <avr/io.h>
 
 
 void Motor_leftMode_(char mode){
	switch (mode){
	case 0:
		PORTD &= ~((1<<5)|(1<<6));
		break;
	case 1:
		PORTD &= ~(1<<5);
		PORTD |= 1<<6;
		break;
	case 2:
		PORTD &= ~(1<<6);
		PORTD |= 1<<5;
		break;
	case 3:
		PORTD |= (1<<5)|(1<<6);
		break;
	default:	//Brake
		PORTD &= ~(1<<5);
		PORTD |= 1<<6;
		break;
	}
 }
 
 void Motor_rightMode_(char mode){
	  switch (mode)
	  {
	 case 0:
		  PORTD &= ~(1<<3);
		  PORTB &= ~(1<<3);
		  break;
	  case 1:
		  PORTD &= ~(1<<3);
		  PORTB |= 1<<3;
		  break;
	  case 2:
		  PORTB &= ~(1<<3);
		  PORTD |= 1<<3;
		  break;
	  case 3:
		  PORTD |= (1<<3);
		  PORTB |= (1<<3);
		  break;
	  default:		//brake
		  PORTD &= ~(1<<5);
		  PORTD |= 1<<6;
		  break;
	  }
  }


void Motor_driveForward(void){
	Motor_leftMode_(1);
	Motor_rightMode_(1);	
}


void Motor_driveReverse(void){
	Motor_leftMode_(2);
	Motor_rightMode_(2);
}


void Motor_driveCoast(void){
	Motor_leftMode_(0);
	Motor_rightMode_(0);
}

void Motor_driveStop(void){
	Motor_leftMode_(3);
	Motor_rightMode_(3);
}

void Motor_driveClockwise(void){
	Motor_leftMode_(1);
	Motor_rightMode_(2);
}

void Motor_driveCounterClockwise(void){
	Motor_leftMode_(2);
	Motor_rightMode_(1);
}