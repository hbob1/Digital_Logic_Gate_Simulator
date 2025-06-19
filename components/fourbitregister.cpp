#include "fourbitregister.h"

void FourBitRegister::setInput(int index, bool value)
{
    if (index >= 0 && index < 6)
    {
        inputs[index] = value;
    }
}

void FourBitRegister::evaluate()
{
    reg1->setInput(0, inputs[0]);
    reg1->setInput(1, inputs[4]);
    reg1->setInput(2, inputs[5]);
    reg1->evaluate();

    reg2->setInput(0, inputs[1]);
    reg2->setInput(1, inputs[4]);
    reg2->setInput(2, inputs[5]);
    reg2->evaluate();

    reg3->setInput(0, inputs[2]);
    reg3->setInput(1, inputs[4]);
    reg3->setInput(2, inputs[5]);
    reg3->evaluate();

    reg4->setInput(0, inputs[3]);
    reg4->setInput(1, inputs[4]);
    reg4->setInput(2, inputs[5]);
    reg4->evaluate();

    display->setInput(0, reg1->getOutput(0));
    display->setInput(1, reg2->getOutput(0));
    display->setInput(2, reg3->getOutput(0));
    display->setInput(3, reg4->getOutput(0));
    display->evaluate();

    std::vector<bool> segmentStates;
    for (int i = 0; i < 7; i++)
    {
        segmentStates.push_back(display->getOutput(i));
    }

    printDisplay.printDisplay(segmentStates);
}

bool FourBitRegister::getOutput(int index) const
{

    if (index == 0)
        return reg1->getOutput(0);
    if (index == 1)
        return reg2->getOutput(0);
    if (index == 2)
        return reg3->getOutput(0);
    if (index == 3)
        return reg4->getOutput(0);

    return false;
}