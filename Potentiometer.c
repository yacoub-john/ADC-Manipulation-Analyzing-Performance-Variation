/*
 * File:   Potentiometer.c
 * Author: John_Yacoub
 *
 * Created on December 5, 2021, 1:16 AM
 */


// ------- Preamble -------- //
#define F_CPU 16000000UL 
#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pinDefines.h"

#define	DELAY_CONST	(120)	/* Constant for manual delay  */	
#define ISR_TIMER0_RELOAD (10) /* Constant for ISR  */		

volatile uint8_t gResult = 0; // unsigned 8 bit global variable.

void delay_function(volatile int32_t);
//extern void asmFunction();

uint16_t readADC(uint8_t channel) {
    
 ADMUX = (0xf0 & ADMUX) | channel;
 ADCSRA |= (1 << ADSC);
 loop_until_bit_is_clear(ADCSRA, ADSC);
 return (ADC);
 
}
int main(void) {
    
 // -------- Initialization --------- //
 uint16_t potentiometer;
 uint8_t run = 1;
 
 // Set up ISR
 TCCR0A |= (1 << WGM01); // Set the Timer0's Timer Mode to CTC
 OCR0A = 255; // Set the value that you want to count to from zero.
 TIMSK0 |= (1 << OCIE0A); // Set up Timer 0 to have an Interrupt Service Request on 'COMPA'
 asm("sei");  // Enable interrupts 
 TCCR0B |= (1 << CS00) | (1 << CS02); // CS00 CS01 CS02: 1 0 1: set prescaler to 1024 and start the timer.

 // Set up ADC
 ADMUX |= (1 << REFS0); /* reference voltage on AVCC */
 ADCSRA |= (1 << ADPS1) | (1 << ADPS0); /* ADC clock pre-scaler /8 */
 ADCSRA |= (1 << ADEN); /* enable ADC */
 DDRB = (1UL << PORT5); //	bit	5	is	an	out.	
 
 //ASM Function
 //asmFunction();
 
 
 // ------ Event loop ------ //
 while (1) {
 potentiometer = readADC(POT);
 run = potentiometer >> 2; //right shifted value
 
 PORTD &= 0x0F;
 PORTB &= 0xF0;
 
 PORTD |= ((run & 0x0F) << 4); // Send the lower four bits of run to pin on port D.
 PORTB |= ((run & 0xF0) >> 4); // Send the higher four bits of run to pin on port B.
  

 if(run == 0)
 {
    PORTB |= (1UL << PORT5); // Turn on the LED attached to Port B Pin 5. 
    PORTD |= (1UL << PORT4); // Turn on the LED attached to Port D Pin 4. 
 }
 
 else
 {
    delay_function(DELAY_CONST * run); //	wait
    PORTB |= (1UL << PORT5); // Turn on the LED attached to Port B Pin 5. 
    delay_function(DELAY_CONST * run); //	wait
    PORTB &= ~(1UL << PORT5); // Turn off the LED attached to Port B Pin 5.
     
     
     
 }
         
 } /* End event loop */
 
 return (0); /* This line is never reached */
}


// Interrupt Service routine for Timer 0.
ISR (TIMER0_COMPA_vect) // timer0 overflow interrupt
{
    
 static int8_t isr_count = ISR_TIMER0_RELOAD;

 // run the internal counter, once per ISR call
 if (isr_count > 0) // write a check here for isr_count being greater than zero
 {
    isr_count --;  // takes the variable isr_count and decrements it
 }
 else // we counted enough. time to toggle the LED on PB5
 {
   isr_count = ISR_TIMER0_RELOAD; // reset isr_count to its original value for next round.
   PORTD ^= (1 << 4);// toggle PORTB Bit 5 here.

 }


}

void delay_function(volatile int32_t x) {

    
    gResult = (uint8_t) x;
    
    while (x > 0) {
        
       asm("LDS r16, (gResult)");
       asm("DEC r16");
       asm("STS (gResult), r16"); //store contents of r16 into global variable

       x = x - 1;
    }

    

}
