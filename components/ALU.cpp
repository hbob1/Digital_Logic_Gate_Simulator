#include "ALU.h"

ALU::ALU() {}

void ALU::setInput(int index, bool value)
{
    if (index >= 0 && index < 9)
    {
        inputs[index] = value;
    }
}

void ALU::evaluate()
{
    for (int i = 0; i < 4; ++i)
    {
        xorgate[i].setInput(0, inputs[i + 4]);
        xorgate[i].setInput(1, inputs[8]);
        xorgate[i].evaluate();
    }

    for (int i = 0; i < 4; ++i)
    {
        fourbitadder.setInput(i, inputs[i]);
    }
    for (int i = 0; i < 4; ++i)
    {
        fourbitadder.setInput(i + 4, xorgate[i].getOutput(0));
    }
    fourbitadder.setInput(8, inputs[8]);
    fourbitadder.evaluate();

    // Output
    // 0 - 3, number where 0 is negative
    //  6, zero or not
    //  5, Negative or Positive
    //  4, Carry

    for (int i = 0; i < 4; ++i)
    {
        notgate[i].setInput(0, fourbitadder.getOutput(i));
        notgate[i].evaluate();
    }

    andgate[0].setInput(0, notgate[0].getOutput(0));
    andgate[0].setInput(1, notgate[1].getOutput(0));
    andgate[0].evaluate();

    andgate[1].setInput(0, andgate[0].getOutput(0));
    andgate[1].setInput(1, notgate[2].getOutput(0));
    andgate[1].evaluate();

    andgate[2].setInput(0, andgate[1].getOutput(0));
    andgate[2].setInput(1, notgate[3].getOutput(0));
    andgate[2].evaluate();
}

bool ALU::getOutput(int index) const
{
    if (index >= 0 && index <= 3)
        return fourbitadder.getOutput(index);
    if (index == 4)
        return fourbitadder.getOutput(4); // Carry
    if (index == 5)
        return fourbitadder.getOutput(0); // Negative
    if (index == 6)
        return andgate[2].getOutput(0); // Zero
    return false;
}