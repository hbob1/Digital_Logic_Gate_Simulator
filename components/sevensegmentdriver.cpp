#include "sevensegmentdriver.h"

SevenSegmentDriver::SevenSegmentDriver() {};

void SevenSegmentDriver::setInput(int index, bool value)
{
    if (index >= 0 && index < 4)
    {
        inputs[index] = value;
    }
}

void SevenSegmentDriver::evaluate()
{
    xorgate[0].setInput(0, inputs[0]);
    xorgate[0].setInput(1, inputs[2]);
    xorgate[0].evaluate();

    notgate.setInput(0, inputs[2]);
    notgate.evaluate();

    nandgate[0].setInput(0, inputs[1]);
    nandgate[0].setInput(1, notgate.getOutput(0));
    nandgate[0].evaluate();

    xorgate[1].setInput(0, nandgate[0].getOutput(0));
    xorgate[1].setInput(1, inputs[3]);
    xorgate[1].evaluate();

    xorgate[2].setInput(0, inputs[1]);
    xorgate[2].setInput(1, xorgate[0].getOutput(0));
    xorgate[2].evaluate();

    orgate[0].setInput(0, inputs[1]);
    orgate[0].setInput(1, xorgate[0].getOutput(0));
    orgate[0].evaluate();

    orgate[1].setInput(0, xorgate[0].getOutput(0));
    orgate[1].setInput(1, xorgate[1].getOutput(0));
    orgate[1].evaluate();

    orgate[2].setInput(0, inputs[1]);
    orgate[2].setInput(1, notgate.getOutput(0));
    orgate[2].evaluate();

    orgate[3].setInput(0, xorgate[1].getOutput(0));
    orgate[3].setInput(1, xorgate[2].getOutput(0));
    orgate[3].evaluate();

    nandgate[1].setInput(0, xorgate[1].getOutput(0));
    nandgate[1].setInput(1, inputs[1]);
    nandgate[1].evaluate();

    orgate[4].setInput(0, orgate[2].getOutput(0));
    orgate[4].setInput(1, inputs[3]);
    orgate[4].evaluate();

    andgate[0].setInput(0, orgate[1].getOutput(0));
    andgate[0].setInput(1, orgate[3].getOutput(0));
    andgate[0].evaluate();

    andgate[1].setInput(0, xorgate[1].getOutput(0));
    andgate[1].setInput(1, nandgate[0].getOutput(0));
    andgate[1].evaluate();

    andgate[2].setInput(0, orgate[2].getOutput(0));
    andgate[2].setInput(1, orgate[3].getOutput(0));
    andgate[2].evaluate();

    andgate[3].setInput(0, orgate[3].getOutput(0));
    andgate[3].setInput(1, orgate[0].getOutput(0));
    andgate[3].evaluate();
}

bool SevenSegmentDriver::getOutput(int index) const
{
    if (index == 0)
        return orgate[1].getOutput(0);
    if (index == 1)
        return nandgate[1].getOutput(0);
    if (index == 2)
        return orgate[4].getOutput(0);
    if (index == 3)
        return andgate[0].getOutput(0);
    if (index == 4)
        return andgate[1].getOutput(0);
    if (index == 5)
        return andgate[2].getOutput(0);
    if (index == 6)
        return andgate[3].getOutput(0);

    return false;
}

DigitDisplay::DigitDisplay() {};

void DigitDisplay::printDisplay(const std::vector<bool> &segments)
{
    if (segments.size() != 7)
    {
        std::cerr << "Error \n";
        return;
    }

    const bool a = segments[0];
    const bool b = segments[1];
    const bool c = segments[2];
    const bool d = segments[3];
    const bool e = segments[4];
    const bool f = segments[5];
    const bool g = segments[6];

    std::cout
        << " " << (a ? "--" : "  ") << " \n"
        << (f ? "|" : " ") << "  " << (b ? "|" : " ") << "\n"
        << " " << (g ? "--" : "  ") << " \n"
        << (e ? "|" : " ") << "  " << (c ? "|" : " ") << "\n"
        << " " << (d ? "--" : "  ") << " \n";
}