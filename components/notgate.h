#pragma once
#include "component.h"
class NotGate : public component {
private:
    bool inputs[1] = {false};
    bool output = false;

public:
    NotGate();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};
