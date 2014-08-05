/*
 * fabscan.h
 *
 *  Created on: 18-07-2014
 *      Author: pholat
 */

#ifndef FABSCAN_H_
#define FABSCAN_H_

#include <avr/io.h>
#include <util/delay.h>

#define PORT_STEP		PORTB
#define PORT_CONTROL	PORTB
#define DDR_STEP		DDRB
#define DDR_CONTROL		DDRB

#define LIGHT_PIN PD5
#define LASER_PIN PD1
// Oh it's not used
// Microstepping is set in hardware
// #define MS_PIN    PC6

//Stepper 1 as labeled on Shield, Turntable
#define ENABLE_PIN_0  PB2
#define STEP_PIN_0    PB1
#define DIR_PIN_0     PB0

//Stepper 2, Laser Stepper
// Never used in simple_driver
#define ENABLE_PIN_1  PB3
#define STEP_PIN_1    PB1
#define DIR_PIN_1     PB0

#define TURN_LASER_OFF      200
#define TURN_LASER_ON       201
#define PERFORM_STEP        202
#define SET_DIRECTION_CW    203
#define SET_DIRECTION_CCW   204
#define TURN_STEPPER_ON     205
#define TURN_STEPPER_OFF    206
#define TURN_LIGHT_ON       207
#define TURN_LIGHT_OFF      208
#define ROTATE_LASER        209
#define FABSCAN_PING        210
#define FABSCAN_PONG        211
#define SELECT_STEPPER      212
#define LASER_STEPPER       11
#define TURNTABLE_STEPPER   10
//the protocol: we send one byte to define the action what to do.
//If the action is unary (like turnung off the light) we only need one byte so we are fine.
//If we want to tell the stepper to turn, a second byte is used to specify the number of steps.
//These second bytes are defined here below.
#define ACTION_BYTE         1    //normal byte, first of new action
#define LIGHT_INTENSITY     2
#define TURN_TABLE_STEPS    3
#define LASER1_STEPS        4
#define LASER2_STEPS        5
#define LASER_ROTATION      6
#define STEPPER_ID          7

int extern incomingByte;// = 0;
int extern byteType; //= 1;
int extern currStepper;

void direction_cw();
void direction_ccw();
void stepper_on();
void stepper_off();
void single_step(); //current motor: turn a single step
void step(int count); // current motor: turn a count step's

void fabscan_setup();
uint8_t fabscan_work(int check,int action);


#endif /* FABSCAN_H_ */
