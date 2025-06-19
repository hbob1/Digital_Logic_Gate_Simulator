#pragma once

#include "nandgate.h"
#include "orgate.h"

class XorGate : public component {
private:
    OrGate orGate;
    NandGate nandGate;
    AndGate andGate;

public:
    XorGate();
    void setInput (int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};
