#include "xorgate.h"

XorGate::XorGate() {};

void XorGate::setInput(int index, bool value)
{
    if (index == 0)
    {
        orGate.setInput(index, value);
        nandGate.setInput(index, value);
    }
    if (index == 1)
    {
        orGate.setInput(index, value);
        nandGate.setInput(index, value);
    }
}

void XorGate::evaluate()
{
    orGate.evaluate();
    bool orGateResult = orGate.getOutput(0);

    nandGate.evaluate();
    bool nandGateResult = nandGate.getOutput(0);

    andGate.setInput(0, orGateResult);
    andGate.setInput(1, nandGateResult);
    andGate.evaluate();
}

bool XorGate::getOutput(int index) const
{
    return andGate.getOutput(0);
}