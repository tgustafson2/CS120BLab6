/*	Author: Thomas Gustafson
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum states{SM_Init,SM_PB0,SM_PB1,SM_PB2}state;
unsigned char temp;
void Tick(){
	switch (state){
		case SM_Init:
			state=SM_PB0;
			temp=0x01;
			break;
		case SM_PB0:
			state=SM_PB1;
			temp=0x02;
			break;
		case SM_PB1:
			state=SM_PB2;
			temp=0x04;
			break;
		case SM_PB2:
			state=SM_PB0;
			temp=0x01;
			break;
		default:
			state=SM_Init;
			temp=0x00;
			break;
	}
	PORTB=temp;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB=0xFF; PORTB=0x00;
    DDRA=0x00; PORTA=0xFF;
    TimerSet(1000);
    TimerOn();
    state=SM_Init;
    /* Insert your solution below */
    while (1) {
	while (!TimerFlag);
	TimerFlag=0;
	Tick();
    }
    return 1;
}
