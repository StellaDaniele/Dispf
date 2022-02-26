
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#include "dispf.h"             // All the forward declarations are in this header
#include "macros_registers.h"  // All the registers' macros (UNO and MEGA ones) and other macros are in this header

void start_lcd(void) {
    DDR_DISP |= MASK_DISP;
    DDR_RS |= (1 << RS);
    DDR_EN |= (1 << EN);

    RES_RS;
    WR_DISP(0x03);
    _delay_us(100);
    RES_EN;
    _delay_us(100);
    SET_EN;
    _delay_us(100);
    RES_EN;
    _delay_ms(5);

    WR_DISP(0x03);
    _delay_us(100);
    RES_EN;
    _delay_us(100);
    SET_EN;
    _delay_us(100);
    RES_EN;
    _delay_us(1000);

    WR_DISP(0x03);
    _delay_us(100);
    RES_EN;
    _delay_us(100);
    SET_EN;
    _delay_us(100);
    RES_EN;
    _delay_us(1000);

    WR_DISP(0x02);
    _delay_us(100);
    RES_EN;
    _delay_us(100);
    SET_EN;
    _delay_us(100);
    RES_EN;
    _delay_us(1000);

    display(0x28, CONF); /* function set    [ 0010 1000 ] */
    _delay_us(1000);
    display(0x08, CONF); /* display off     [ 00001DCB ] */
    _delay_us(1000);
    display(0x01, CONF); /* display on   [ 00000001 ] */
    _delay_us(1000);
    display(0x06, CONF); /* entry mode set  [ 000001 I/D S ] */
    _delay_us(1000);
    display(0x0c, CONF); /* display on      [ 00001DCB ] */
    _delay_us(1000);
}

void display(unsigned char car, unsigned char stat) {
    if (stat)
        SET_RS;
    else
        RES_RS;

    WR_DISP(car >> 4);
    _delay_us(100);
    SET_EN;
    _delay_us(100);
    RES_EN;

    WR_DISP(car);
    _delay_us(100);
    SET_EN;
    _delay_us(100);
    RES_EN;

    _delay_ms(2);
}

void clrscr(void) {
    display(0x01, CONF);
    _delay_ms(2);
}

void gotoxy(unsigned char x, unsigned char y) {
    x = (x > 20) ? 20 : x;   // If x value is greater than 20, it set it to 20 (max 20 character per line)
    y = (y > 4) ? 4 : y;     // If y value is greater than 4, it set it to 4 (max 4 lines)
    x += (y - 1) * 20;       // Calculates the equivalent x
    if (x >= 21 && x <= 40)  // Second line
        x += 44;
    else if (x >= 41 && x <= 60)  // Third line
        x -= 20;
    else if (x >= 61 && x <= 80)  // Forth line
        x += 24;
    x -= 1;
    x |= 0x80;

    display(x, CONF);
    _delay_ms(2);
}

void disp_pos(unsigned int num) {
    unsigned char i, zeri, cifre[6];

    for (i = 0; i < 5; i++)  // Conversion from int to str
    {
        cifre[4 - i] = num % 10 + '0';
        num = num / 10;
    }
    cifre[5] = '\0';  // Null character after the 5 digits to terminate the string
    zeri = 0;
    for (i = 0; i < 4; i++)  // Counting of zeros before the number
    {
        if (cifre[0] != '0') break;
        if (cifre[i] == '0') zeri++;
        if (cifre[i + 1] != '0') break;
    }
    for (i = 0; i < 5; i++)  // Moving the string to the left
        cifre[i] = cifre[i + zeri];
    for (i = 0; cifre[i] != 0; i++)
        display(cifre[i], DATA);
}

int power(int base, int exponent) {
    int result = 1;
    for (; exponent > 0; exponent--)
        result *= base;
    return result;
}

void float_to_int(float number, char digits, int *integer_part, int *floating_part) {
    *integer_part = (int)number;                                           // Extract the whole part with an explicit typecasting
    *floating_part = (number - (float)*integer_part) * power(10, digits);  // Extract the floating part by subtracting the number with the whole part and then take the floating part multiplied for the power of 10 at the precision value
}

void disp_num(int num) {
    if (num < 0) {
        display('-', DATA);    // Displays the '-' sign
        disp_pos(num * (-1));  // Displays the given number, first turns it positive
        display(' ', DATA);
    } else
        disp_pos(num);  // If the number is positive it just let disp_pos() function to display it
}

void disp_float(float num, unsigned char prec) {
    int integer_part = 0, floating_part = 0;

    prec = (prec < 0) ? 2 : (prec > 4) ? 4
                                       : prec;  // Check that the precision variable is not negative (or is set to 2) or greater than 5 (it is blocked at 5)

    float_to_int(num, prec, &integer_part, &floating_part);

    disp_pos(integer_part);

    if (prec != 0) {
        display('.', DATA);
        disp_pos(floating_part);
    }
}
