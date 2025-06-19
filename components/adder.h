#pragma once

#include "norgate.h"

class Adder : public component {
private:
    XorGate xor1;
    XorGate xor2;
    AndGate and1;
    AndGate and2;
    OrGate orGate;

    bool inputs[3] = {false, false, false}; 

public: 
    Adder();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};

