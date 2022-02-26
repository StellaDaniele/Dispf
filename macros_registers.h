#pragma once

#ifndef MACROS_REGISTERS_H_
#define MACROS_REGISTERS_H_

////////////////////////////////////////////////
/*Set up LCD on Arduino UNO:

        The numbers of the pins are referred to the digital pins of the Arduino board
        VSS : GND
        VDD : 5V
        VE : Connected to a 10k potentiometer in order to adjust screen contrast
        RS : 9
        RW : GND
        E : 8
        D0 :
        D1 :
        D2 :
        D3 :
        D4 : 10
        D5 : 11
        D6 : 12
        D7 : 13
        A : 220 ohm resistor to set the backlight brightness
        K : GND
*/

#define CONF 0  // Used as a parameter to tell to display() function that we are calling it for setting the display
#define DATA 1  // Used as a parameter to tell to display() function that we are calling it for displaying something

// This preprocessor directive has the function of setting up the masks of the registers for the Arduino MEGA and UNO
#ifndef __AVR_ATmega2560__  // If it isn't defined it means that we are using the Arduino UNO

#define PORT_EN PORTB
#define DDR_EN DDRB
#define EN 0

#define PORT_RS PORTB
#define DDR_RS DDRB
#define RS 1

#define PORT_DISP PORTB
#define DDR_DISP DDRB
#define MASK_DISP (0x0F << 2)

#define WR_DISP(n)           \
    PORT_DISP &= ~MASK_DISP; \
    PORT_DISP |= ((n << 2) & MASK_DISP)

#else  // If its defined it means that we are using the Arduino MEGA

#define PORT_EN PORTH
#define DDR_EN DDRH
#define EN 5

#define PORT_RS PORTH
#define DDR_RS DDRH
#define RS 6

#define PORT_DISP PORTB
#define DDR_DISP DDRB
#define MASK_DISP (0xF0)

#define WR_DISP(n)           \
    PORT_DISP &= ~MASK_DISP; \
    PORT_DISP |= ((n << 4) & MASK_DISP)
#endif

// These macros have the function of setting up the values during the start_lcd() function
#define SET_EN PORT_EN |= (1 << EN)
#define RES_EN PORT_EN &= ~(1 << EN)
#define SET_RS PORT_RS |= (1 << RS)
#define RES_RS PORT_RS &= ~(1 << RS)

#endif