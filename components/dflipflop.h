#pragma once

#include "datalatch.h"

class DFlipFlop : public component {
private:
    // index 0 Data
    // index 1 Clock

    int countP1;
    int countP2;

    bool inputs[2] = {false};

    component* notgate = new NotGate();
    component* dl1 = new DataLatch(countP1);
    component* dl2 = new DataLatch(countP2);

public:
    DFlipFlop(int count1, int count2) : countP1(count1), countP2(count2) {}; 
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;

};
