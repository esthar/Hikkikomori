/*
 * Motor_Driver.h
 *
 * Created: 2/14/2013 10:40:00 PM
 *  Author: Andre Lucas
 
 Contains the function prototypes for the Motor_Drive functions.
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_


void Motor_leftMode_(char mode); //Controls state of each motor: Mode 0-Coast; 1-Forward; 2-Reverse; 3-Brake
void Motor_rightMode_(char mode);

void Motor_driveForward(void);
void Motor_driveReverse(void);
void Motor_driveCoast(void);
void Motor_driveStop(void);
void Motor_driveClockwise(void);
void Motor_driveCounterClockwise(void);


#endif /* MOTOR_DRIVER_H_ */