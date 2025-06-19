#include "norgate.h"

NorGate::NorGate() {}

void NorGate::setInput(int index, bool value)
{
    if (index >= 0 && index < 2)
    {
        inputs[index] = value;
    }
}

void NorGate::evaluate()
{
    orgate.setInput(0, inputs[0]);
    orgate.setInput(1, inputs[1]);
    orgate.evaluate();

    notgate.setInput(0, orgate.getOutput(0));
    notgate.evaluate();
}

bool NorGate::getOutput(int index) const
{
    return notgate.getOutput(0);
}