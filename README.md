# ADC-ISR-Manipulation-Analyzing-Performance-Variation

**Project Description: **

This project used a breadboarded 8-bit ATMEGA328P microprocessor and was developed  in MPLABX using a mix of C and assembler. The project implements three different routines/methods to output a in response to moving a potentiometer or button. This project’s focus is to compare routines in C versus assembler in terms of efficiency and functionality, as well as comparing hardware and software methods of receiving an input value. This project also shows the use of assembler functions, special registers and internal hardware specifically relating to the AVR instruction set.

<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152078545-409ecfed-6b2b-4fd0-b453-8d43c33b97bc.png" />
</p>

**Technical Requirement/Specifications: **

The system/application is broken into four distinct sections: Breadboarding and Setup, Using the ADC, ISR versus Manual Delays, C versus Assembler each with their own specifications:
1. Breadboarding and Setup: The ATMEGA328P is breadboarded and connected to the SNAP programmer. There are also additional connections like a potentiometer connected to ADC 5 and 8 LEDs, 4 of which are connected to the lower pins of PortB and 4 are connected to the upper pins of PortD. The chip can run the program without being connected to the SNAP programmer so all it needs to run is a connection to power over USB. There are also two other LEDs setup to blink in response to a manual delay function and an interrupt service routine using delay constants based on the value of the potentiometer.

2. Using the ADC: In the program the ADC is set to receive analog signals from the potentiometer (ADC pin 5) and converts to a digital signal. When there is a physical change to the potentiometer it senses that change and converts it into an equivalent analog electrical signal. This analog signal is converted into a digital signal using the analog to digital converter (on ATMEGA328P) and the signal is then fed to the microprocessor and processes it accordingly. The processed signal has a 10-bit resolution implying that there is 2^10 = 1024 possible values. The board uses 5V as reference and so any analog value in between 0 and 5V is converted into its equivalent ADC value as shown below. The 0-5V range is divided into 2^10 = 1024 steps which is then used a value of 10-bit integer. The program itself also sets up reference voltage AVCC, the ADC clock pre-scaler and enables the ADC in free running mode where the ADC is triggered automatically at every rising edge of clock pulse.

<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152079279-a56b77f6-1476-4471-88c3-3434f2a4749c.png" />
</p>


**Components List: **

In terms of the hardware used for this project the some of the parts were used for to breadboard the microprocessor and others were needed for my program these include:

•	ATMEGA328P: 8-bit microprocessor used to run the program; the parts associated with breadboarding the microprocessor include:
o	Breadboard: Used to put together all the parts for the microprocessor.
o	16 MHz Crystal: Used as a clock for the microprocessor keeping time to prevent processes from jumping ahead or lagging.
o	2x 39pF Load Capacitor: Used to ground the crystal.
o	Button: Used to ground pin 1 of the microprocessor to reset it.
o	Voltage Regulator: Used to provide power (5V) to circuit using USB.

•	SNAP Programmer: Used as a debugger/programmer to upload programs from MPLABX to ATMEGA328.
•	8x Blue 3mm LED: Used to show the 8-bit value of the potentiometer where each LED represents a bit.
•	Potentiometer: Analog source used to control the frequency of an LED using a manual delay.
•	Red 3mm LED: Blinks at the frequency of a manual delay based on the value of the potentiometer.
•	Blue 3mm LED: Blinks at the frequency of a timer, turned on and off by an interrupt service routine

<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152078795-f6a04385-58cb-4487-ba04-586f83ba5a35.png" />
</p>

**Conclusion: **

Overall, my goal was to develop a project that uses the ADC on the ATMEGA328P in unison with timers and a ISR routine to test the performance of mixing C and assembler. This project gave me a chance to apply and expand the my knowledge on the AVR architecture.I have plans to expand my project use the analog to digital converter, timers and interrupt service routines using the MIPS architecture.

Video Link:  https://youtu.be/f8g5cmFL4UA  


