#include "tristatebuffer.h"

TriStateBuffer::TriStateBuffer() {};

void TriStateBuffer::setInput(int index, bool value)
{
    if (index >= 0 && index < 2)
    {
        inputs[index] = value;
    }
}

void TriStateBuffer::evaluate()
{
    if (inputs[0] == 1)
    {
        output = inputs[1];
    }
    if (inputs[0] == 0)
    {
        output = 2;
    }
}

bool TriStateBuffer::getOutput(int index) const
{
    if (output == 0)
        return false;
    if (output == 1)
        return true;
    if (output == 2)
    {
        std::cout << "buffer is off" << std::endl;
        return false;
    }
    return false;
}

bool TriStateBuffer::isUnkown() const
{
    return output == 2;
}