#pragma once

#include "tristatebuffer.h"

class BusBuffer: public component {
private:
    // Inputs 0 - output enable
    // 1 - 4 Data
    bool inputs[5] = {false};

    TriStateBuffer buffer[4];

public:
    BusBuffer();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;
};