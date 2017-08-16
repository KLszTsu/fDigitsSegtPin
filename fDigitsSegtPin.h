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
        if(Serial) Serial.println("[Error](4Digit7Seg12Pin): Input value larger than 10000.");
        return;
    }
    if(vff < 0) {
        if(Serial) Serial.println("[Error](4Digit7Seg12Pin): Input value smaller than 0.");
        return;
    }

    //Print the values
    if(vff >= 1000) {
        fvPrint(0, vff / 1000, 0); vff -= (int)(vff / 1000) * 1000;
        fvPrint(1, vff / 100, 0); vff -= (int)(vff / 100) * 100;
        fvPrint(2, vff / 10, 0); vff -= (int)(vff / 10) * 10;
        fvPrint(3, (int)(vff), doPrint_lastDot);
        vff = 0;
    }
    else if(vff >= 100) {
        fvPrint(0, vff / 100, 0); vff -= (int)(vff / 100) * 100;
        fvPrint(1, vff / 10, 0); vff -= (int)(vff / 10) * 10;
        fvPrint(2, (int)(vff), 1); vff -= (int)(vff);
        vff *= 10; fvPrint(3, ((vff - (int)(vff)) > 0.5) ? ((int)(vff) + 1) : (int)(vff), 0);
        vff = 0;
    }
    else if(vff >= 10) {
        fvPrint(0, vff / 10, 0); vff -= (int)(vff / 10) * 10;
        fvPrint(1, (int)(vff), 1); vff -= (int)(vff);
        vff *= 10; fvPrint(2, (int)(vff), 0); vff-= (int)(vff);
        vff *= 10; fvPrint(3, ((vff - (int)(vff)) > 0.5) ? ((int)(vff) + 1) : (int)(vff), 0);
        vff = 0;
    }
    else {
        if(doPrint_firstZero = 0) fvPrint(0, 0, 0);
        fvPrint(1, (int)(vff), 1); vff -= (int)(vff);
        vff *= 10; fvPrint(2, (int)(vff), 0); vff-= (int)(vff);
        vff *= 10; fvPrint(3, ((vff - (int)(vff)) > 0.5) ? ((int)(vff) + 1) : (int)(vff), 0);
        vff = 0;
    }
}

