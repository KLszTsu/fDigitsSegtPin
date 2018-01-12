/* fDigitsSegtPin by KLsz
 * For more info please visit "https://github.com/KuangLei" or "https://coding.net/u/KLsz"
 * License: GPL v3, CopyLeft KLsz
 */

#ifndef ARDUINO                           // This part is used to make a fool of Syntastic.
#ifndef Syntastic_h                       // Syntastic is a vim syntax checker.
#include "/home/klsz/Arduino/Syntastic.h" // It can act as a C++ checker,
#endif                                    // but not an Arduino checker.
#endif                                    // It wont affect compiling using Arduino IDE.

#ifndef __FDIGITSSEGTPIN_H__
#define __FDIGITSSEGTPIN_H__

#ifdef ARDUINO
#include "Arduino.h"
#endif
#include "ver.h"

class fDigitsSegtPin {
    public:
        //Storage the pins
        fDigitsSegtPin(u8 vPf1, u8 vPf2, u8 vPf3, u8 vPf4, u8 vPf5, u8 vPf6, u8 vPf7, u8 vPf8, u8 vPf9, u8 vPf10, u8 vPf11, u8 vPf12);

        //Init the pins
        void begin();

        //Print digit
        void print(float vff);

        //Settings
        u8 doPrint_lastDot = 0;
        u8 doPrint_firstZero = 0;
        u8 doReport_overRange = 1;
    private:
        //Pins
        u8 vPcD1; u8 vPcD2; u8 vPcD3; u8 vPcD4;
        u8 vPcA; u8 vPcB; u8 vPcC; u8 vPcD; u8 vPcE; u8 vPcF; u8 vPcG; u8 vPcH;

        //Display table
        u8 villDigitTable[10][7] = {
        //   a  b  c  d  e  f  g   
            {1, 1, 1, 1, 1, 1, 0}, //0
            {0, 1, 1, 0, 0, 0, 0}, //1
            {1, 1, 0, 1, 1, 0, 1}, //2
            {1, 1, 1, 1, 0, 0, 1}, //3
            {0, 1, 1, 0, 0, 1, 1}, //4
            {1, 0, 1, 1, 0, 1, 1}, //5
            {1, 0, 1, 1, 1, 1, 1}, //6
            {1, 1, 1, 0, 0, 0, 0}, //7
            {1, 1, 1, 1, 1, 1, 1}, //8
            {1, 1, 1, 1, 0, 1, 1}, //9
        };

        //Clean the afterglow
        void fvAfterGlow();
        //Set the digit to write
        void fvSet(u8 vifDigit);
        //Write number to the digit
        void fvWrite(u8 vifNumber, u8 vifDot);

        //Print the digit with the number
        void fvPrint(u8 vifDigit, u8 vifNumber, u8 vifDot);
};

#endif //__FDIGITSSEGTPIN_H__

