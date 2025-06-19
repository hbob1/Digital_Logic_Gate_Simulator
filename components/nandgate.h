#pragma once

#include "andgate.h"
#include "notgate.h"

class NandGate : public component {
private:
    AndGate andGate;
    NotGate notGate;

public:
    NandGate();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};
