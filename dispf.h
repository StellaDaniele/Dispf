#pragma once

#ifndef _DISPF_H
#define _DISPF_H

// Functions:
void dispf(unsigned char x, unsigned char y, const char *fmt, ...);  // This is the main function, takes coordinates, a specifier that identifies the type, and print the given variable
void start_lcd(void);                                                // Starts up the LCD before using it
void display(unsigned char car, unsigned char stat);                 // Displays a character on the display, first it writes the 4 bits
void clrscr(void);                                                   // Clears the entire display
void gotoxy(unsigned char x, unsigned char y);                       // Moves the cursor to the given x and y coordinates
void disp_pos(unsigned int num);                                     // Displays the given 16 bit positive number on the display
void disp_num(int num);                                              // Displays the given number (both positive and negative) on the display
void disp_float(float num, unsigned char prec);                      // Displays the given float number on the display

// Other functions:
void float_to_int(float number, char digits, int *integer_part, int *floating_part);  // Converts the float number to 2 int numbers containing the whole part and the floating part
int power(int base, int exponent);                                                    // Returns the power of the given number to the given exponent

#endif