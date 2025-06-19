#include "dflipflop.h"

void DFlipFlop::setInput(int index, bool value)
{
    if (index >= 0 && index < 2)
    {
        inputs[index] = value;
    }
}

void DFlipFlop::evaluate()
{
    notgate->setInput(0, inputs[1]);
    notgate->evaluate();

    dl1->setInput(0, inputs[0]);
    dl1->setInput(1, notgate->getOutput(0));
    dl1->evaluate();

    dl2->setInput(0, dl1->getOutput(0));
    dl2->setInput(1, inputs[1]);
    dl2->evaluate();
}

bool DFlipFlop::getOutput(int index) const
{
    return dl2->getOutput(0);
}