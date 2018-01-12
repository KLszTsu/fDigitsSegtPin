[![Join the chat at https://gitter.im/fDigitsSegtPin/Lobby](https://badges.gitter.im/fDigitsSegtPin/Lobby.svg)](https://gitter.im/fDigitsSegtPin/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) 
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/003cd8dbf698401fb460a531808d1aae)](https://www.codacy.com/app/KuangLei/fDigitsSegtPin?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=KuangLei/fDigitsSegtPin&amp;utm_campaign=Badge_Grade)  

# fDigitsSegtPin (STF\_A\_4)
fDigitsSegtPin is a Arduino library used to drive a basic 4-digit display like 5461.  
If you are lack of pins, you can try to use 4-digit display with chips like 595.  

## Installation
You can install it through **Arduino Library Manager** by searching `fDigitsSegtPin`.  
You can also manually download it from the [releases page](https://github.com/KuangLei/fDigitsSegtPin/releases), or clone it with `git clone git@github.com:KuangLei/fDigitsSegtPin.git` and then copy it to your Arduino library folder.  
Check out Arduino's [library tutorial](https://www.arduino.cc/en/Guide/Libraries) for further guide.  

## Usage
The usage is also available in the [example](https://github.com/KuangLei/fDigitsSegtPin/blob/master/examples/counter/counter.ino).  
### First, connect your 4 digit display to Arduino
Connect the 4 digit display to Arduino like following.  
About the **resistor**, Either 100 ohm or 220 ohm is OK but 100 ohm ones will make it brighter.  
```
Pin        12 11 10 9  8  7
           |  |  |  |  |  |
Resistor   |  R  R  |  |  R
           |  |  |  |  |  |
         +------------------+
Display  |    8. 8. 8. 8.   |
         +------------------+
           |  |  |  |  |  |
Resistor   R  R  R  R  R  |
           |  |  |  |  |  |
Pin        1  2  3  4  5  6
```
### Second, include the library
Switch to Arduino IDE.  
Press `Alt+S` and select `Include Library`, then click `fDigitsSegtPin` in the list.  
After that, a `#include <fDigitsSegtPin.h>` should be added to the top your code.  

If there aren't any `fDigitsSegtPin` in the list, make sure you have installed it well. If not, check the `Installaion` part above.  
### Third, create a display
Put this line after all the `#include` and before `void setup()`:  
```
fDigitsSegtPin Display(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
```
* The `Display` here can be any word you want.  
* The numbers here should be the pins used to connect to the display.  
### Forth, init the pins
Put this line in the `setup()` function:  
```
Display.begin();
```
### Finally, you can print the value you want
Use this to print what you want:  
```
Display.print(3.14);
```
This kind of display cannot display a value for long. If you call this function not frequently enough, it will start blinking.  
If you want a continous one, consider those display with a chip on it like 595.  
### At last, there are some settings you can change
you can change the all the settings like this.  
```
Display.Settings = Option;
```
#### doPrint_LastDot
* Usage: Print the dot in the last digit when the number is over 1000.
* Options: 0, 1.
* Default: 0.
* Example: When printing 1024, if this parameter is set to `0`, it will print `1 0 2 4 `, and if this parameter is set to `1`, it will print `1 0 2 4.`.
#### doPrint_firstZero
* Usage: Print the first zero when the number is less than 10.
* Option: 0, 1.
* Default: 0.
* Example: Whenl printing 3.14, if this parameter is set to `0`, it will print `  3.1 4 `, and if this parameter is set to `1`, it will print `0 3.1 4 `.
* Notice: Because the size of a float or double or anything is only 4 in Arduino, it can only keep two decimal places.
#### doReport_overRange
* Usage: Report when the value is larger than 10000 or is smaller than 0.
* Option: 0, 1.
* Default: 1.
* Example: When printing 10001, if this parameter is set to `0`, nothing will happen, and if this parameter is set to `1` and the Serial is available, an error message will be sent through Serial.

## Contact and support us
Please see [CONTRIBUTING.md](CONTRIBUTING.md).  

Thanks.  

