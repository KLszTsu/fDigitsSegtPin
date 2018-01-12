/* fDigitsSegtPin by KLsz
 * For more info please visit "https://github.com/KuangLei" or "https://coding.net/u/KLsz"
 * License: GPL v3, CopyLeft KLsz
 */

#ifndef ARDUINO                           // This part is used to make a fool of Syntastic.
#ifndef Syntastic_h                       // Syntastic is a vim syntax checker.
#include "/home/klsz/Arduino/Syntastic.h" // It can act as a C++ checker,
#endif                                    // but not an Arduino checker.
#endif                                    // It wont affect compiling using Arduino IDE.

#ifdef ARDUINO
#include "Arduino.h"
#endif

#include "fDigitsSegtPin.h"

//Storage the pins
fDigitsSegtPin::fDigitsSegtPin(u8 vPf1, u8 vPf2, u8 vPf3, u8 vPf4, u8 vPf5, u8 vPf6, u8 vPf7, u8 vPf8, u8 vPf9, u8 vPf10, u8 vPf11, u8 vPf12) {
    vPcD1 = vPf12; vPcD2 = vPf9; vPcD3 = vPf8; vPcD4 = vPf6;
    vPcA = vPf11; vPcB = vPf7; vPcC = vPf4; vPcD = vPf2; vPcE = vPf1; vPcF = vPf10; vPcG = vPf5; vPcH = vPf3;
}

//Init the pins
void fDigitsSegtPin::begin() {
    pinMode(vPcD1, OUTPUT); pinMode(vPcD2, OUTPUT); pinMode(vPcD3, OUTPUT); pinMode(vPcD4, OUTPUT);
    pinMode(vPcA, OUTPUT); pinMode(vPcB, OUTPUT); pinMode(vPcC, OUTPUT); pinMode(vPcD, OUTPUT); pinMode(vPcE, OUTPUT); pinMode(vPcF, OUTPUT); pinMode(vPcG, OUTPUT); pinMode(vPcH, OUTPUT);

    digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, HIGH);
    digitalWrite(vPcA, LOW); digitalWrite(vPcB, LOW); digitalWrite(vPcC, LOW); digitalWrite(vPcD, LOW); digitalWrite(vPcE, LOW); digitalWrite(vPcF, LOW); digitalWrite(vPcG, LOW); digitalWrite(vPcH, LOW);
}

//Clean the afterglow
void fDigitsSegtPin::fvAfterGlow() {
    digitalWrite(vPcA, LOW); digitalWrite(vPcB, LOW); digitalWrite(vPcC, LOW); digitalWrite(vPcD, LOW); digitalWrite(vPcE, LOW); digitalWrite(vPcF, LOW); digitalWrite(vPcG, LOW);
    digitalWrite(vPcH, LOW);
}
//Set the digit to write
void fDigitsSegtPin::fvSet(u8 vifDigit) {
    switch(vifDigit) {
        case 0: digitalWrite(vPcD1, LOW); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, HIGH); break;
        case 1: digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, LOW); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, HIGH); break;
        case 2: digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, LOW); digitalWrite(vPcD4, HIGH); break;
        case 3: digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, LOW); break;
        default: break;
    }
}
//Write number to the digit
void fDigitsSegtPin::fvWrite(u8 vifNumber, u8 vifDot) {
    digitalWrite(vPcA, villDigitTable[vifNumber][0]); digitalWrite(vPcB, villDigitTable[vifNumber][1]); digitalWrite(vPcC, villDigitTable[vifNumber][2]); digitalWrite(vPcD, villDigitTable[vifNumber][3]); digitalWrite(vPcE, villDigitTable[vifNumber][4]); digitalWrite(vPcF, villDigitTable[vifNumber][5]); digitalWrite(vPcG, villDigitTable[vifNumber][6]);
    digitalWrite(vPcH, vifDot);
}

//Print the digit with the number
void fDigitsSegtPin::fvPrint(u8 vifDigit, u8 vifNumber, u8 vifDot) {
    fvSet(vifDigit);
    fvWrite(vifNumber, vifDot);
    delay(1);
    fvAfterGlow();
}

//Print user's input
void fDigitsSegtPin::print(float vff) {
    //Make sure these value can be printed
    if(vff >= 10000) {
        if(Serial && doReport_overRange) Serial.println("[Error](4Digit7Seg12Pin): Input value larger than 10000.");
        return;
    }
    if(vff < 0) {
        if(Serial && doReport_overRange) Serial.println("[Error](4Digit7Seg12Pin): Input value smaller than 0.");
        return;
    }

    //Print the values
    if(vff >= 1000) {
        fvPrint(0, vff / 1000, 0); vff -= (int)(vff / 1000) * 1000;
        fvPrint(1, vff / 100, 0); vff -= (int)(vff / 100) * 100;
        fvPrint(2, vff / 10, 0); vff -= (int)(vff / 10) * 10;
        fvPrint(3, (int)(vff), doPrint_lastDot);
    }
    else if(vff >= 100) {
        fvPrint(0, vff / 100, 0); vff -= (int)(vff / 100) * 100;
        fvPrint(1, vff / 10, 0); vff -= (int)(vff / 10) * 10;
        fvPrint(2, (int)(vff), 1); vff -= (int)(vff);
        vff *= 10; fvPrint(3, ((vff - (int)(vff)) > 0.5) ? ((int)(vff) + 1) : (int)(vff), 0);
    }
    else if(vff >= 10) {
        fvPrint(0, vff / 10, 0); vff -= (int)(vff / 10) * 10;
        fvPrint(1, (int)(vff), 1); vff -= (int)(vff);
        vff *= 10; fvPrint(2, (int)(vff), 0); vff-= (int)(vff);
        vff *= 10; fvPrint(3, ((vff - (int)(vff)) > 0.5) ? ((int)(vff) + 1) : (int)(vff), 0);
    }
    else {
        if(doPrint_firstZero = 0) fvPrint(0, 0, 0);
        fvPrint(1, (int)(vff), 1); vff -= (int)(vff);
        vff *= 10; fvPrint(2, (int)(vff), 0); vff-= (int)(vff);
        vff *= 10; fvPrint(3, ((vff - (int)(vff)) > 0.5) ? ((int)(vff) + 1) : (int)(vff), 0);
    }
}

