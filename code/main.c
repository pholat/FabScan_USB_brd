/*
 * main.c
 *
 *  Created on: 05-08-2014
 *      Author: pholat
 */

//////////////// includes		/////////////////////////
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "usbdrv/usbdrv.h"
#include <util/delay.h>
#include "fabscan.h"

uint8_t buff,fab_work_flag=0;

int  incomingByte = 0;
int  byteType = 1;
int  currStepper;

volatile uint8_t replyBuf[32] = "Hello, USB ***********! ********";
static uchar dataReceived = 0, dataLength = 0; // for USB_DATA_IN
//////////////// Output LED macro	/////////////////////

// this gets called when custom control message is received
USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{

	usbRequest_t *rq = (void *)data; // cast data to correct type
	incomingByte=rq->bRequest;
	fab_work_flag=1;
	return 1;

//    return 0; // should not get here
}

// This gets called when data is sent from PC to the device
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
	uchar i;
	for(i = 0; dataReceived < dataLength && i < len; i++, dataReceived++)
	replyBuf[dataReceived] = data[i];
    return (dataReceived == dataLength); // 1 if we received it all, 0 if not
}

int main()
{
	fabscan_setup();
	uchar i;
//    wdt_enable(WDTO_1S); // enable 1s watchdog timer
    usbInit();
    usbDeviceDisconnect(); // enforce re-enumeration
    for(i = 0; i<250; i++) { // wait 500 ms
//        wdt_reset(); // keep the watchdog happy
        _delay_ms(2);
    }
    usbDeviceConnect();
    sei(); // Enable interrupts after re-enumeration

    while(1)
    {
//    		wdt_reset(); // keep the watchdog happy
    		usbPoll();

    		if(fab_work_flag)	// if there is new data for fabscan → let it work
    		{
    			fab_work_flag=0;
    			fabscan_work(1,incomingByte);
    		}
    }
    return 0;
}
