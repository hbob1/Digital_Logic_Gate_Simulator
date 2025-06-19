#include "busbuffer.h"

BusBuffer::BusBuffer() {}

void BusBuffer::setInput(int index, bool value)
{
    if (index >= 0 && index < 5)
    {
        inputs[index] = value;
    }
}

void BusBuffer::evaluate()
{

    buffer[0].setInput(0, inputs[0]);
    buffer[0].setInput(1, inputs[1]);
    buffer[0].evaluate();

    buffer[1].setInput(0, inputs[0]);
    buffer[1].setInput(1, inputs[2]);
    buffer[1].evaluate();

    buffer[2].setInput(0, inputs[0]);
    buffer[2].setInput(1, inputs[3]);
    buffer[2].evaluate();

    buffer[3].setInput(0, inputs[0]);
    buffer[3].setInput(1, inputs[4]);
    buffer[3].evaluate();
}

bool BusBuffer::getOutput(int index) const
{
    if (index == 0)
        return buffer[0].getOutput(0);
    if (index == 1)
        return buffer[1].getOutput(0);
    if (index == 2)
        return buffer[2].getOutput(0);
    if (index == 3)
        return buffer[3].getOutput(0);

    return false;
}