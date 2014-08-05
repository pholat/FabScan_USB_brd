/*
 * fabscan.c
 *
 *  Created on: 18-07-2014
 *      Author: pholat
 */

#include "fabscan.h"

void direction_cw()
{
    if(currStepper == TURNTABLE_STEPPER) PORT_STEP|=(1<<DIR_PIN_0);
    else if(currStepper == LASER_STEPPER) PORT_STEP|=(1<<DIR_PIN_1);
}

void direction_ccw()
{
    if(currStepper == TURNTABLE_STEPPER) PORT_STEP&=~(1<<DIR_PIN_0);
      else if(currStepper == LASER_STEPPER) PORT_STEP&=~(1<<DIR_PIN_1);
}

void stepper_on()
{
    if(currStepper == TURNTABLE_STEPPER) PORT_STEP&=~(1<<ENABLE_PIN_0);
    else if(currStepper == LASER_STEPPER) PORT_STEP&=~(1<<ENABLE_PIN_1);
}

void stepper_off()
{
    if(currStepper == TURNTABLE_STEPPER) PORT_STEP|=(1<<ENABLE_PIN_0);
    else if(currStepper == LASER_STEPPER) PORT_STEP|=(1<<ENABLE_PIN_1);
}
//current motor: turn a single step
void single_step()
{
	if(currStepper == TURNTABLE_STEPPER)
 	{
		 PORT_STEP&=~(1<<STEP_PIN_0);
 	}else if(currStepper == LASER_STEPPER)
 	{
		 PORT_STEP&=~(1<<STEP_PIN_1);
 	}
	_delay_ms(5);

 	if(currStepper == TURNTABLE_STEPPER)
 	{
		 PORT_STEP|=(1<<STEP_PIN_0);
 	}else if(currStepper == LASER_STEPPER)
 	{
		 PORT_STEP|=(1<<STEP_PIN_1);
 	}
 	_delay_ms(5);
}

void step(int count) { for(int i=0; i<count; i++) single_step(); };

void fabscan_setup()
{
  // initialize the serial port
	DDRD|=(1<<LASER_PIN);
	DDRB|=(1<<LIGHT_PIN);
//	DDRB|=(1<<MS_PIN);;
//		PORT_STEP|=(1<<MS_PIN); //HIGH for 16microstepping, LOW for no microstepping
	DDRB|=(1<<ENABLE_PIN_0);
	DDRB|=(1<<DIR_PIN_0);
	DDRB|=(1<<STEP_PIN_0);

  DDRB|=(1<<ENABLE_PIN_1);
  DDRB|=(1<<DIR_PIN_1);
  DDRB|=(1<<STEP_PIN_1);

 //disable all steppers at startup
  PORT_STEP|=(ENABLE_PIN_0);  //HIGH to turn off
  PORT_STEP|=(ENABLE_PIN_1);  //HIGH to turn off
  PORT_CONTROL|=(LIGHT_PIN); //turn light off
  PORTD|=(LASER_PIN); //turn laser on

  //TODO acknowledgement
  // Soft for big_driver - Pin Mapping and a bit of code

 currStepper = TURNTABLE_STEPPER;  //turntable is default stepper
}

uint8_t fabscan_typAction(int action)
{
	uint8_t data_to_send=0;
    switch(action)
    {    //this switch always handles the first byte
      //Laser
      case TURN_LASER_OFF: 	PORTD&=~(1<<LASER_PIN);	// turn the LASER off
      	break;
      case TURN_LASER_ON:		PORTD|=(1<<LASER_PIN);   // turn the LASER on
      	break;
      case ROTATE_LASER:		byteType = LASER_ROTATION;		//unused
      	break;

      //TurnTable
      case PERFORM_STEP: byteType = TURN_TABLE_STEPS;
      	break;
      case SET_DIRECTION_CW: direction_cw();
      	break;
      case SET_DIRECTION_CCW: direction_ccw();
      	break;
      case TURN_STEPPER_ON: stepper_on();
      	break;
      case TURN_STEPPER_OFF: stepper_off();
      	break;
      case TURN_LIGHT_ON: byteType = LIGHT_INTENSITY;
      	break;
      case TURN_LIGHT_OFF: PORT_CONTROL&=~(1<<LIGHT_PIN);
      	break;
      case FABSCAN_PING:
    	  _delay_ms(1);
    	  data_to_send=FABSCAN_PONG;
    	  break;
      case SELECT_STEPPER: byteType = STEPPER_ID;
      	break;
      }
    return data_to_send;
}

uint8_t fabscan_work(int check,int action)
{
	uint8_t data_to_pc=0;
	// Check - cheks if there is data available
	// action - is incoming data
	  if(check > 0)
	  {
	    switch(byteType)
	    {
	    	case ACTION_BYTE: data_to_pc=fabscan_typAction(action);
	    		break;
	    	case LIGHT_INTENSITY:       //after this point we take care of the second byte if one is sent
	    	   // TODO
	    	   // analogWrite(LIGHT_PIN, incomingByte);
	    		byteType = ACTION_BYTE;  //reset byteType
	    		break;
	        case TURN_TABLE_STEPS:
	        	step(incomingByte);
	        	byteType = ACTION_BYTE;
	        	break;
	        case STEPPER_ID:
	        	// TODO
	        	data_to_pc=incomingByte;
	        	currStepper = incomingByte;
	        	byteType = ACTION_BYTE;
	        	break;
	    }
	  }
	  return data_to_pc;
}
