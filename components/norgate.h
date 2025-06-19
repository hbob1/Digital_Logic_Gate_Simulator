#pragma once

#include "xorgate.h"

class NorGate : public component {
private:
    bool inputs[2] = {false, false};

    OrGate orgate;
    NotGate notgate;

public:
    NorGate();
    void setInput (int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const;
};
