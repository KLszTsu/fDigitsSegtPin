float vfRead;

#define vPcDigitD1 vPcDigit12
#define vPcDigitD2 vPcDigit9
#define vPcDigitD3 vPcDigit8
#define vPcDigitD4 vPcDigit6
#define vPcDigitA vPcDigit11
#define vPcDigitB vPcDigit7
#define vPcDigitC vPcDigit4
#define vPcDigitD vPcDigit2
#define vPcDigitE vPcDigit1
#define vPcDigitF vPcDigit10
#define vPcDigitG vPcDigit5
#define vPcDigitH vPcDigit3

//[OUTER]Init the 4-digit display pins using fvDigitInit();
#define fvDigitInit() { \
    pinMode(vPcDigit1, OUTPUT); pinMode(vPcDigit2, OUTPUT); pinMode(vPcDigit3, OUTPUT); pinMode(vPcDigit4, OUTPUT); pinMode(vPcDigit5, OUTPUT); pinMode(vPcDigit6, OUTPUT); pinMode(vPcDigit7, OUTPUT); pinMode(vPcDigit8, OUTPUT); pinMode(vPcDigit9, OUTPUT); pinMode(vPcDigit10, OUTPUT); pinMode(vPcDigit11, OUTPUT); pinMode(vPcDigit12, OUTPUT); \
    digitalWrite(vPcDigitA, HIGH); digitalWrite(vPcDigitB, HIGH); digitalWrite(vPcDigitC, HIGH); digitalWrite(vPcDigitD, HIGH); digitalWrite(vPcDigitE, HIGH); digitalWrite(vPcDigitF, HIGH); digitalWrite(vPcDigitG, HIGH); digitalWrite(vPcDigitH, HIGH); \
}

//[OUTER]Read the voltage using fvCheck();
#define fvCheck() { \
    if (analogRead(vPcMode) <= 675) vfRead = (float)analogRead(vPcIn) / 204.8; /*5V range*/ \
    else vfRead = (float)analogRead(vPcIn) / 51.2; /*20V range*/ \
}

//[OUTER]Print the recorded voltage through Serial using fvSerial();
#define fvSerial() { Serial.print(vfRead); Serial.println("V"); }

//[INNER]Storge the 4-digit display table
u8 villDigitTable[11][7] = {
//   a  b  c  d  e  f  g  h     
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
//[INNER]Clean the afterglow using fvDigitAfterGlow();
#define fvDigitAfterGlow() { \
    digitalWrite(vPcDigitA,LOW); \
    digitalWrite(vPcDigitB,LOW); \
    digitalWrite(vPcDigitC,LOW); \
    digitalWrite(vPcDigitD,LOW); \
    digitalWrite(vPcDigitE,LOW); \
    digitalWrite(vPcDigitF,LOW); \
    digitalWrite(vPcDigitG,LOW); \
    digitalWrite(vPcDigitH,LOW); \
}
//[INNER]Set the digit to write using fvDigitSet(viDigit);
#define fvDigitSet(vifDigit) { \
    switch(vifDigit) { \
        case 1: digitalWrite(vPcDigitD1, LOW); digitalWrite(vPcDigitD2, HIGH); digitalWrite(vPcDigitD3, HIGH); digitalWrite(vPcDigitD4, HIGH); break; \
        case 2: digitalWrite(vPcDigitD1, HIGH); digitalWrite(vPcDigitD2, LOW); digitalWrite(vPcDigitD3, HIGH); digitalWrite(vPcDigitD4, HIGH); break; \
        case 3: digitalWrite(vPcDigitD1, HIGH); digitalWrite(vPcDigitD2, HIGH); digitalWrite(vPcDigitD3, LOW); digitalWrite(vPcDigitD4, HIGH); break; \
        case 4: digitalWrite(vPcDigitD1, HIGH); digitalWrite(vPcDigitD2, HIGH); digitalWrite(vPcDigitD3, HIGH); digitalWrite(vPcDigitD4, LOW); break; \
        default: break; \
    } \
}
//[INNER]Write the number using fvDigitWrite(viNumber, vifDot);
#define fvDigitWrite(vifNumber, vifDot) { \
    digitalWrite(vPcDigitA, villDigitTable[vifNumber][0]); \
    digitalWrite(vPcDigitB, villDigitTable[vifNumber][1]); \
    digitalWrite(vPcDigitC, villDigitTable[vifNumber][2]); \
    digitalWrite(vPcDigitD, villDigitTable[vifNumber][3]); \
    digitalWrite(vPcDigitE, villDigitTable[vifNumber][4]); \
    digitalWrite(vPcDigitF, villDigitTable[vifNumber][5]); \
    digitalWrite(vPcDigitG, villDigitTable[vifNumber][6]); \
    digitalWrite(vPcDigitH, vifDot); \
}
//[INNER]Clear the digit using fvDigitClear(viDigit)
#define fvDigitClear(vifDigit) { \
    fvDigitAfterGlow(); \
    fvDigitSet(vifDigit); \
    delay(2); \
}
//[INNER]Print the digit with the number using fvDigitPrint(viDigit, viNumber, viDot);
#define fvDigitPrint(vifDigit, vifNumber, vifDot) { \
    fvDigitAfterGlow(); \
    fvDigitSet(vifDigit); \
    fvDigitWrite(vifNumber, vifDot); \
    delay(2); \
}
//[INNER]Round the float to int using fiRound(vfFloat);
u8 fiRound(float vff) { return((vff - (int)(vff) >= 0.5) ? ((int)(vff) + 1) : ((int)(vff))); }
//[OUTER]Print the Recorded Voltage through the 4-digit display using fvDigit();
#define fvDigit() { \
    if(vfRead <= 5) { \
        fvDigitPrint(1, fiRound(vfRead), 1); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvDigitPrint(2, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvDigitPrint(3, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvDigitPrint(4, fiRound(vfRead), 0); \
    } \
    else { \
        vfRead /= 10; \
        fvDigitPrint(1, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvDigitPrint(2, fiRound(vfRead), 1); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvDigitPrint(3, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvDigitPrint(4, fiRound(vfRead), 0); \
    } \
}

