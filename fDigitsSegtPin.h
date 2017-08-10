class fDigitsSegtPin {
    public:
        //Storage and init the pins
        fDigitsSegtPin(u8 vPf1, u8 vPf2, u8 vPf3, u8 vPf4, u8 vPf5, u8 vPf6, u8 vPf7, u8 vPf8, u8 vPf9, u8 vPf10, u8 vPf11, u8 vPf12);

        //Print digit
        void print(float vffInput);
    private:
        //Pins
        u8 vPcD1; u8 vPcD2; u8 vPcD3; vPcD4;
        u8 vPcA; u8 vPcB; u8 vPcC; u8 vPcD; u8 vPcE; u8 vPcF; u8 vPcG; u8 vPcH;

        //Table
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
        void fvWrite(u8 vifNumber);

        //Clear the digit
        void fvClear(u8 vifDigit);
        //Print the digit with the number
        void fvPrint(u8 vifDigit, u8 vifNumber);

        //Rounding function used in printing
        u8 fiRound(float vff);
}

//Storage and init the pins
fDigitsSegtPin::fDigitsSegtPin(u8 vPf1, u8 vPf2, u8 vPf3, u8 vPf4, u8 vPf5, u8 vPf6, u8 vPf7, u8 vPf8, u8 vPf9, u8 vPf10, u8 vPf11, u8 vPf12) {
    //Srorage the pins
    vPcD1 = vPf12; vPcD2 = vPf9; vPcD3 = vPf8; vPcD4 = vPf6; 
    vPcA = vPf11; vPcB = vPf7; vPcC = vPf4; vPcD = vPf2; vPcE = vPf1; vPcF = vPf10; vPcG = vPf5; vPcH = vPf3;

    //Init the pins
    digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, HIGH);
    digitalWrite(vPcA, LOW); digitalWrite(vPcB, LOW); digitalWrite(vPcC, LOW); digitalWrite(vPcD, LOW); digitalWrite(vPcE, LOW); digitalWrite(vPcF, LOW); digitalWrite(vPcG, LOW); digitalWrite(vPcH, LOW);
}

//Clean the afterglow
void fDigitsSegtPin::fvAfterGlow() {
    digitalWrite(vPcA,LOW);
    digitalWrite(vPcB,LOW);
    digitalWrite(vPcC,LOW);
    digitalWrite(vPcD,LOW);
    digitalWrite(vPcE,LOW);
    digitalWrite(vPcF,LOW);
    digitalWrite(vPcG,LOW);
    digitalWrite(vPcH,LOW);
}
//Set the digit to write
void fDigitsSegtPin::fvSet(u8 vifDigit) {
    switch(vifDigit) {
        case 1: digitalWrite(vPcD1, LOW); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, HIGH); break;
        case 2: digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, LOW); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, HIGH); break;
        case 3: digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, LOW); digitalWrite(vPcD4, HIGH); break;
        case 4: digitalWrite(vPcD1, HIGH); digitalWrite(vPcD2, HIGH); digitalWrite(vPcD3, HIGH); digitalWrite(vPcD4, LOW); break;
        default: break;
    }
}
//Write number to the digit
void fDigitsSegtPin::fvWrite(u8 vifNumber) {
    digitalWrite(vPcA, villDigitTable[vifNumber][0]);
    digitalWrite(vPcB, villDigitTable[vifNumber][1]);
    digitalWrite(vPcC, villDigitTable[vifNumber][2]);
    digitalWrite(vPcD, villDigitTable[vifNumber][3]);
    digitalWrite(vPcE, villDigitTable[vifNumber][4]);
    digitalWrite(vPcF, villDigitTable[vifNumber][5]);
    digitalWrite(vPcG, villDigitTable[vifNumber][6]);
}

//Clear the digit
void fDigitsSegtPin::fvClear(u8 vifDigit) {
    fvAfterGlow();
    fvSet(vifDigit);
//    delay(2); ----------------------------------------------------!
}
//Print the digit with the number
void fDigitsSegtPin::fvPrint(u8 vifDigit, u8 vifNumber) {
    fvAfterGlow();
    fvSet(vifDigit);
    fvWrite(vifNumber);
//    delay(2); ----------------------------------------------------!
}

u8 fiRound(float vff) { return((vff - (int)(vff) >= 0.5) ? ((int)(vff) + 1) : ((int)(vff))); }
void fDigitsSegtPin::print(float vffInput) {
}

/*-------------------------------------------------------------------
 *                  Origin code from STF_A_3                         
 *-------------------------------------------------------------------
 */

//[OUTER]Print the Recorded Voltage through the 4-digit display using fv();
#define fvDigit() { \
    if(vfRead <= 5) { \
        fvPrint(1, fiRound(vfRead), 1); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvPrint(2, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvPrint(3, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvPrint(4, fiRound(vfRead), 0); \
    } \
    else { \
        vfRead /= 10; \
        fvPrint(1, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvPrint(2, fiRound(vfRead), 1); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvPrint(3, fiRound(vfRead), 0); \
        vfRead -= fiRound(vfRead); \
        vfRead *= 10; \
        fvPrint(4, fiRound(vfRead), 0); \
    } \
}

