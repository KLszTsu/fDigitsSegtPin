/* Library 4Digit7Seg12Pin by KLsz Studio
 * For more info please visit "https://github.com/KuangLei/4Digit7Seg12Pin/"
 * This Library is protected under GPLv3, CopyLeft KLsz Studio
 */

#include <fDigitsSegtPin.h>

// Connect the 4 Digit 7 Segment Display to Arduino like this
/* Arduino Pin   33 32 31 30 29 28
 *               |  |  |  |  |  |
 * Resistor      |  R  R  |  |  R
 *               |  |  |  |  |  |
 *             +------------------+
 * Display     |    8. 8. 8. 8.   |
 *             +------------------+
 *               |  |  |  |  |  |
 * Resistor      R  R  R  R  R  |
 *               |  |  |  |  |  |
 * Arduino Pin   22 23 24 25 26 27
 */
/* FUNCTION: fDigitsSegtPin(Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7, Pin8, Pin9, Pin10, Pin11, Pin12):
 *   Usage: Create a Display and set the pins,
            Put it before the setup() function;
 *   Arguments: Pin1~Pin12: (int) 4 Digit 7 segment display's pins from 1 to 12;
 */
fDigitsSegtPin Display(22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33);

void setup() {
// Init and config the display here
/* FUNCTION: begin():
 *   Usage: Init the Pins,
 *          Put it in the setup() function;
 * PARAMETER: doPrint_lastDot:
 *   Usage: Print the dot in the last digit when the number is over 1000;
 *   Options: (int) 0, 1;
 *   Default: 0;
 *   Example: When printing 1024,
 *            if this parameter is set to 0, it will print "1 0 2 4 ",
 *            if this parameter is set to 1, it will print "1 0 2 4.";
 * PARAMETER: doPrint_firstZero:
 *   Usage: Print the first zero when the number is less than 10;
 *   Option: (int) 0, 1;
 *   Default: 0;
 *   Example: Whenl printing 3.14,
 *            if this parameter is set to 0, it will print "  3.1 4 ",
 *            if this parameter is set to 1, it will print "0 3.1 4 ";
 *   Notice: Because the size of a float or double or anything is only 4 in Arduino,
 *           it can only keep two decimal places;
 * PARAMETER: doReport_overRange:
 *   Usage: Report when the value is larger than 10000 or is smaller than 0;
 *   Option: (int) 0, 1;
 *   Default: 1;
 *   Example: When printing 10001,
 *            if this parameter is set to 0, nothing will happen,
 *            if this parameter is set to 1 and the Serial is available, an error message will be sent through Serial;
 */
    Display.begin();
    Display.doPrint_lastDot = 1;
    Display.doPrint_firstZero = 1;
    Display.doReport_overRange = 0;
}

void loop() {
// Print the value here
/* FUNCTION: print(Value)"
 *   Usage: Print value;
 *   Arguments: Value: (float) The value to print;
 *   Notice: This kind of display cannot display a value for long;
 *           If you call this function not frequently enough, it will start blinking;
 *           If you want a continous one, consider those display with a chip on it like 595;
 */
    for(float i = 0.01; i < 10000; i += 0.01) Display.print(i);
}

