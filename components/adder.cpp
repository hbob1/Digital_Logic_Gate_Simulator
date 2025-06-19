#include "adder.h"

Adder::Adder() {}

void Adder::setInput(int index, bool value)
{
    if (index >= 0 && index < 3)
    {
        inputs[index] = value;
    }
}

void Adder::evaluate()
{

    xor1.setInput(0, inputs[0]);
    xor1.setInput(1, inputs[1]);
    xor1.evaluate();
    bool resultXor1 = xor1.getOutput(0);

    and1.setInput(0, inputs[0]);
    and1.setInput(1, inputs[1]);

    and1.evaluate();
    bool resultAnd1 = and1.getOutput(0);

    xor2.setInput(0, resultXor1);
    xor2.setInput(1, inputs[2]);
    xor2.evaluate();
    bool resultXor2 = xor2.getOutput(0);

    and2.setInput(0, resultXor1);
    and2.setInput(1, inputs[2]);
    and2.evaluate();
    bool resultAnd2 = and2.getOutput(0);

    orGate.setInput(0, resultAnd1);
    orGate.setInput(1, resultAnd2);
    orGate.evaluate();
    bool resultOr = orGate.getOutput(0);
}

bool Adder::getOutput(int index) const
{
    if (index == 0)
        return xor2.getOutput(0);
    if (index == 1)
        return orGate.getOutput(0);
    return false;
}