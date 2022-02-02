	
	/*Source: http://www.rjhcoding.com/avr-asm-delay-subroutine.php */
	
	.equ	iVal 	= 39998		; inner loop value

	.cseg
	.org	0x00
	
	/* Initializing The Stack Pointer */
	ldi	r16,LOW(RAMEND)		; initialize
	out	SPL,r16			; stack pointer
	ldi	r16,HIGH(RAMEND)	; to RAMEND
	out	SPH,r16			; "

	clr	ledR			; clear led register
	ldi	mask,(1<<PIND0)		; load 00000001 into mask register
	out	DDRD, mask		; set PIND0 to output

start:	
        eor	ledR,mask		; toggle PIND0 in led register
	out	PORTD,ledR		; write led register to PORTD

	ldi	loopCt,50		; initialize delay multiple for 0.5 sec
	rcall	delay10ms		; call delay subroutine

	rjmp	start			; jump back to start

delay10ms:
	ldi	iLoopRl,LOW(iVal)	; intialize inner loop count in inner
	ldi	iLoopRh,HIGH(iVal)	; loop high and low registers
 /* 
     innerLoopCount = iVal*(2 + 2) - 1
		    = 39998*4 - 1
		    = 159991 cycles 
     
*/
iLoop:	
        sbiw	iLoopRl,1		; decrement inner loop registers
	brne	iLoop			; branch to iLoop if iLoop registers != 0

	dec	loopCt			; decrement outer loop register
	brne	delay10ms		; branch to oLoop if outer loop register != 0

	nop				; no operation

	ret				; return from subroutine