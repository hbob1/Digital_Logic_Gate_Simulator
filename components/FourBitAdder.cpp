#include "FourBitAdder.h"

FourBitAdder::FourBitAdder() {}

void FourBitAdder::setInput(int index, bool value)
{
    if (index >= 0 && index < 9)
    {
        inputs[index] = value;
    }
}

void FourBitAdder::evaluate()
{
    adder1.setInput(0, inputs[3]);
    adder1.setInput(1, inputs[7]);
    adder1.setInput(2, inputs[8]);
    adder1.evaluate();
    bool resultAdder1Sum = adder1.getOutput(0);
    bool resultAdder1Carry = adder1.getOutput(1);

    adder2.setInput(0, inputs[2]);
    adder2.setInput(1, inputs[6]);
    adder2.setInput(2, resultAdder1Carry);
    adder2.evaluate();
    bool resultAdder2Sum = adder2.getOutput(0);
    bool resultAdder2Carry = adder2.getOutput(1);

    adder3.setInput(0, inputs[1]);
    adder3.setInput(1, inputs[5]);
    adder3.setInput(2, resultAdder2Carry);
    adder3.evaluate();
    bool resultAdder3Sum = adder3.getOutput(0);
    bool resultAdder3Carry = adder3.getOutput(1);

    adder4.setInput(0, inputs[0]);
    adder4.setInput(1, inputs[4]);
    adder4.setInput(2, resultAdder3Carry);
    adder4.evaluate();
    bool resultAdder4Sum = adder4.getOutput(0);
    bool resultAdder4Carry = adder4.getOutput(1);
}

bool FourBitAdder::getOutput(int index) const
{
    if (index == 0)
        return adder4.getOutput(0);
    if (index == 1)
        return adder3.getOutput(0);
    if (index == 2)
        return adder2.getOutput(0);
    if (index == 3)
        return adder1.getOutput(0);
    if (index == 4)
        return adder4.getOutput(1);
    return false;
}