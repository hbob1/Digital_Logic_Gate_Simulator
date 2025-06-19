#pragma once

#include "dflipflop.h"

class OneBitRegister : public component {
private:
    // Index 0 Data
    // Index 1 Store
    // Index 2 Clock
    bool inputs[3] = {false};
    bool storedOutput = false;

    int countP1; // DL type
    int countP2; // DL type
    int countP3; // Reg type

    component* notgate = new NotGate();
    component* andgate1 = new AndGate();
    component* andgate2 = new AndGate();
    component* orgate = new OrGate();
    component* dff = new DFlipFlop(countP1, countP2);

    void writeToFile(const std::string& filename) const;

    int getFromFile(const std::string& filename) const;

public:
    OneBitRegister(int count1, int count2, int count3) : countP1(count1), countP2(count2), countP3(count3) {}
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const override;

};
