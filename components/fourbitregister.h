#pragma once

#include "onebitregister.h"
#include "sevensegmentdriver.h"

class FourBitRegister : public component {
private:
    // Index 3 - data 0
    // Index 2 - data 1
    // Index 1 - data 2
    // Index 0 - data 3
    // Index 4 - store
    // Index 5 - clock

    bool inputs[6] = {false};

    int countDLP1; int countDLP2; int countDLP3; int countDLP4; int countDLP5;
    int countDLP6; int countDLP7; int countDLP8;    
    
    int countRegP1; int countRegP2; int countRegP3; int countRegP4;

    component* reg1 = new OneBitRegister(countDLP1, countDLP2, countRegP1);
    component* reg2 = new OneBitRegister(countDLP3, countDLP4, countRegP2);
    component* reg3 = new OneBitRegister(countDLP5, countDLP6, countRegP3);
    component* reg4 = new OneBitRegister(countDLP7, countDLP8, countRegP4);

    component* display = new SevenSegmentDriver;
    DigitDisplay printDisplay;

public:
    FourBitRegister(int countDL1, int countDL2, int countDL3, int countDL4, int countDL5,
    int countDL6, int countDL7, int countDL8, int countReg1, int countReg2, int countReg3,
    int countReg4) : countDLP1(countDL1), countDLP2(countDL2), countDLP3(countDL3),
    countDLP4(countDL4), countDLP5(countDL5), countDLP6(countDL6), countDLP7(countDL7),
    countDLP8(countDL8), countRegP1(countReg1), countRegP2(countReg2), countRegP3(countReg3),
    countRegP4(countReg4) {}
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const;


};
