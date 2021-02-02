/*	Author: Thomas Gustafson
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab #6  Exercise #3
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
enum states{SM_Start, SM_Wait, SM_Increment, SM_Reset, SM_Decrement}state;
unsigned char temp;
unsigned char count;
void Tick(){
	switch(state){
		case SM_Start:
			state=SM_Wait;
			temp=0x07;
			break;
		case SM_Wait:
			if ((~PINA&0x03)==0x01){
				state=SM_Increment;
				if (temp<9)temp++;
				}
			else if ((~PINA&0x03)==0x02){
				state= SM_Decrement;
				if (temp>0)temp--;
				}
			else if ((~PINA&0x03)==0x03){
				state = SM_Reset;
				temp=0x00;
				}
			count=0;
			break;
		case SM_Increment:
			if ((~PINA&0x03)==0x01){if((temp<9)&&(count%10)==9)temp++;}
			else if ((~PINA&0x03)==0x00){
				state = SM_Wait;
				}
			else if ((~PINA&0x03)==0x03){
				state = SM_Reset;
				temp=0x00;
				count=0;
				}
			else if ((~PINA&0x03)==0x02){
				state= SM_Decrement;
				if (temp>0)temp--;
				count=0;
				}
			count++;
			break;
		case SM_Decrement:
                        if ((~PINA&0x03)==0x02){if((temp>0)&&(count%10)==9)temp--;}
                        else if ((~PINA&0x03)==0x00){
                                state = SM_Wait;
                                }
                        else if ((~PINA&0x03)==0x03){
                                state = SM_Reset;
                                temp=0x00;
                                }
                        else if ((~PINA&0x03)==0x01){
                                state= SM_Increment;
                                if (temp<9)temp++;
                                }
			count++;
                        break;
		case SM_Reset:

			state = SM_Wait;
                        break;
		default:
			state=SM_Start;
			break;
	}
	PORTB=temp;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB=0xFF; PORTB=0x00;
    DDRA=0x00; PORTA=0xFF;
    TimerSet(100);
    TimerOn();
    state=SM_Start;
    /* Insert your solution below */
    while (1) {
	while (!TimerFlag);
	TimerFlag=0;
	Tick();
    }
    return 1;
}
