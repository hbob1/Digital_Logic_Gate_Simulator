#pragma once

#include "notgate.h"
#include "andgate.h"
#include "orgate.h"

class Mux : public component {
private:
    // Inputs
    // 0 - 3 first number
    // 4 - 7 second number
    // 8 Select

    bool inputs[9] = {false};

    NotGate notgate;
    AndGate andgate[8];
    OrGate orgate[4];

public:
    Mux();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};