
#include "dispf.h"  // Contains the forward declarations of all the functions

#include <stdarg.h>  // Contains the macros in order to use the variatic function

#include "macros_registers.h"  // Contains all the registers' macros (UNO and MEGA ones) and other macros

void dispf(unsigned char x, unsigned char y, const char* fmt, ...) {
    gotoxy(x, y);  // Move the cursor to the given coordinates

    va_list args;         // Indicate that args is where variadic function arguments are
    va_start(args, fmt);  // Enables access to variadic function arguments via fmt pointer

    fmt++;  // When initialized it actually contains the address of the '%' character in the passed string, then it must be incremented
    switch (*fmt) {
        case 'd':
        case 'i':
            // If the given format specifier is 'd' or 'i', the variable is an int
            int i = va_arg(args, int);  // Access the argument inside the variadic function arguments list (with the data-type given)

            disp_num(i);
            break;
        case 'c':
            // If the given format specifier is 'c', the variable is a char
            int c = va_arg(args, int);  // Chars are stored as integers. 'char' is promoted to 'int' when passed through a variadic function

            display(c, DATA);
            break;
        case 'f':

            // If the given format specifier is 'f', the variable is a float
            double d = va_arg(args, double);

            unsigned int prec = (*++fmt == '\0') ? 2 : *fmt - '0';  // The precision is given after the specifier. If it wasn't given the precision is set to 2, otherwise it's converted to the actual number.

            disp_float(d, prec);
            break;
        case 's':
            // If the given format specifier is 's', the variable is a string
            const char* str = va_arg(args, const char*);
            // Print each character of the string until the NULL character
            for (; *str != 0; str++)
                display(*str, DATA);
            break;
        case 'u':
            // If the given format specifier is 'u', the variable is an unsigned int
            int i = va_arg(args, unsigned int);

            disp_pos(i);
            break;
    }

    va_end(args);
}
