#pragma once

#include "component.h"

class AndGate : public component {
private:
    bool inputs[2] = {false};
    bool output = false;

public:
    AndGate();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};
