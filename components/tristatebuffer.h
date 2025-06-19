#pragma once

#include "component.h"
#include "iostream"

class TriStateBuffer : public component {
private:
    // 0 is Enable output
    // 1 is Data
    // Output is 1, 0, or Z (3rd state)

    bool inputs[2] = {false};
    
    // 0 = false, 1 = true, 2 = Z
    int output = 2;

public:
    TriStateBuffer();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
    bool isUnkown() const;
};