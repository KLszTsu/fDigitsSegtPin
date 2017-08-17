/* Library 4Digit7Seg12Pin by KLsz Studio
 * For more info please visit "https://github.com/KuangLei/4Digit7Seg12Pin/"
 * This Library is protected under GPLv3, CopyLeft KLsz Studio
 */

#include <fDigitsSegtPin.h>

fDigitsSegtPin Display(22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33);

void setup() {
    Display.begin();
}

void loop() {
    for(float i = 0.01; i < 10000; i += 0.01) Display.print(i);
}

