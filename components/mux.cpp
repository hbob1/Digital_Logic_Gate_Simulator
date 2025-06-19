#include "mux.h"

Mux::Mux() {}

void Mux::setInput(int index, bool value)
{
    if (index >= 0 && index < 9)
    {
        inputs[index] = value;
    }
}

void Mux::evaluate()
{
    notgate.setInput(0, inputs[8]);
    notgate.evaluate();

    andgate[0].setInput(0, inputs[0]);
    andgate[0].setInput(1, notgate.getOutput(0));
    andgate[0].evaluate();

    andgate[1].setInput(0, inputs[1]);
    andgate[1].setInput(1, notgate.getOutput(0));
    andgate[1].evaluate();

    andgate[2].setInput(0, inputs[2]);
    andgate[2].setInput(1, notgate.getOutput(0));
    andgate[2].evaluate();

    andgate[3].setInput(0, inputs[3]);
    andgate[3].setInput(1, notgate.getOutput(0));
    andgate[3].evaluate();

    andgate[4].setInput(0, inputs[4]);
    andgate[4].setInput(1, inputs[8]);
    andgate[4].evaluate();

    andgate[5].setInput(0, inputs[5]);
    andgate[5].setInput(1, inputs[8]);
    andgate[5].evaluate();

    andgate[6].setInput(0, inputs[6]);
    andgate[6].setInput(1, inputs[8]);
    andgate[6].evaluate();

    andgate[7].setInput(0, inputs[7]);
    andgate[7].setInput(1, inputs[8]);
    andgate[7].evaluate();

    orgate[0].setInput(0, andgate[0].getOutput(0));
    orgate[0].setInput(1, andgate[4].getOutput(0));
    orgate[0].evaluate();

    orgate[1].setInput(0, andgate[1].getOutput(0));
    orgate[1].setInput(1, andgate[5].getOutput(0));
    orgate[1].evaluate();

    orgate[2].setInput(0, andgate[2].getOutput(0));
    orgate[2].setInput(1, andgate[6].getOutput(0));
    orgate[2].evaluate();

    orgate[3].setInput(0, andgate[3].getOutput(0));
    orgate[3].setInput(1, andgate[7].getOutput(0));
    orgate[3].evaluate();
}

bool Mux::getOutput(int index) const
{
    if (index == 0)
        return orgate[0].getOutput(0);
    if (index == 1)
        return orgate[1].getOutput(0);
    if (index == 2)
        return orgate[2].getOutput(0);
    if (index == 3)
        return orgate[3].getOutput(0);

    return false;
}