#pragma once

#include "adder.h"

class FourBitAdder : public component {
private:
    bool inputs[9] = {false, false, false, false, false, false, false, false, false};

    Adder adder1;
    Adder adder2;
    Adder adder3;
    Adder adder4;

public:
    FourBitAdder();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};