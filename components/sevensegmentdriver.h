#pragma once

#include "onebitregister.h"

class SevenSegmentDriver : public component {
private:
    // inputs are data from register

    bool inputs [4] = {false};

    XorGate xorgate[3];
    NotGate notgate;
    NandGate nandgate[2];
    OrGate orgate[5];
    AndGate andgate[4];

public:
    SevenSegmentDriver();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const;

};

class DigitDisplay {
public:
    DigitDisplay();
    void printDisplay(const std::vector<bool>& segments);
};
