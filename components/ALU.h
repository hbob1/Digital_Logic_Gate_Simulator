#pragma once

#include "FourBitAdder.h"

class ALU : public component {
private:
    // -8 to 7
    // 0 - 3, where 0 is negative, A
    // 4 - 7, where 4 is negative, B
    // 8, subtract
    bool inputs[9] = {false};

    XorGate xorgate[4];
    FourBitAdder fourbitadder;
    NotGate notgate[4];
    AndGate andgate[3];

public:
    ALU();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};
