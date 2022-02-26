
#include <avr/io.h>

#include "dispf.h"

int main(void) {
    start_lcd();
    while (1) {
        /*
                dispf(x, y, "%dataType", data);

                if used to display a float, after the %f, inside the double quotes, indicate the precision (from 0 to 4) default = 2

        */

        dispf(1, 1, "%d", -10);
        dispf(1, 2, "%c", 'c');
        dispf(1, 3, "%s", "Hi, what's up?");
        dispf(1, 4, "%f5", 3.15984);
        dispf(11, 4, "%f", 3.15984);
        dispf(10, 1, "%d", 36500);
        dispf(10, 2, "%u", 36500);
    }
}
