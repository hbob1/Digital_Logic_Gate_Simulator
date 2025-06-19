#include "orgate.h"

OrGate::OrGate() {}

void OrGate::setInput(int index, bool value)
{
    if (index == 0)
    {
        notGate.setInput(0, value);
    }
    if (index == 1)
    {
        notGate2.setInput(0, value);
    }
}

void OrGate::evaluate()
{
    notGate.evaluate();
    bool notGateResult = notGate.getOutput(0);

    notGate2.evaluate();
    bool notGateResult2 = notGate2.getOutput(0);

    nandGate.setInput(0, notGateResult);
    nandGate.setInput(1, notGateResult2);
    nandGate.evaluate();
}

bool OrGate::getOutput(int index) const
{
    return nandGate.getOutput(0);
}