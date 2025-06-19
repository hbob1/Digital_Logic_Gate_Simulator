#pragma once

#include "notgate.h"
#include "nandgate.h"

class OrGate : public component {

private:
    NotGate notGate;
    NotGate notGate2;
    NandGate nandGate;

public: 
    OrGate();
    void setInput (int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const;
};
