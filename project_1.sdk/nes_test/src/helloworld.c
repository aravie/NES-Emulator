#include <stdio.h>
#include "xparameters.h"
#include "platform.h"
#include "xvtc.h"
#include "xil_cache.h"
#include "xaxivdma.h"
#include "xgpiops.h"

int main() {
	init_platform();
	int switches = *((unsigned int *) 0x41220000);
	int data = 0;
	/*
	(*((unsigned int *) 0x41230000)) |= 0x2;
	*((unsigned int *) 0x41230000) &= ~(0x1);
	int latch = 0;
	int clock = 1;
	int serial_in = 0; //input
	int count = 0;
	int data = 0;
	latch  = 1;
	*((unsigned int *) 0x41230000) |= 0x1;
	usleep(12);
	latch = 0;
	*((unsigned int *) 0x41230000) &= ~(0x1);
	usleep(6);

	while (count < 16){
		data |= ((*((unsigned int *) 0x41230000) & 0x4) << 2) >> count;
		clock = 0;
		*((unsigned int *) 0x41230000) &= ~(0x2);
		usleep(6);
		clock = 1;
		(*((unsigned int *) 0x41230000)) |= 0x2;
		usleep(6);
		count++;
	}
	*/
	//display data on LEDs
	while(switches & 0x1){
		switches = *((unsigned int *) 0x41220000);
		data = *((unsigned int *) 0x40000000); //0x40000000 means reading from AXI register, 0x41230000 for reading from GPIO
		*((unsigned int *) 0x41200000) = data;
	}
	cleanup_platform();
	return 0;

}
