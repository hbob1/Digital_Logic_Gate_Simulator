#include "setreset.h"

setReset::setReset() {}

void setReset::writeToFile(const std::string &filename) const
{
    std::ifstream inputFile(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line))
    {
        // Change which line to find
        if (line.find("outputSR = 0") != std::string::npos || line.find("outputSR = 1") != std::string::npos)
        {
            line = "outputSR = " + std::to_string(norgate2.getOutput(0));
        }
        lines.push_back(line);
    }

    inputFile.close();

    std::ofstream outputFile(filename);
    for (const auto &modifiedLine : lines)
    {
        outputFile << modifiedLine << "\n";
    }
    outputFile.close();
}

int setReset::getFromFile(const std::string &filename) const
{
    std::ifstream inputFile(filename);
    std::string line;
    int value;

    while (std::getline(inputFile, line))
    {
        if (line.find("outputSR = 0") != std::string::npos || line.find("outputSR = 1") != std::string::npos)
        {
            // Change which line to find
            std::string valueStr = line.substr(line.find('=') + 1);
            value = std::stoi(valueStr);
        }
    }

    inputFile.close();

    return value;
}

void setReset::setInput(int index, bool value)
{
    if (index >= 0 && index < 2)
    {
        inputs[index] = value;
    }
}

void setReset::evaluate()
{

    storedOutput = getFromFile("settings.txt");

    norgate1.setInput(0, inputs[0]);
    norgate1.setInput(1, storedOutput);
    norgate1.evaluate();

    norgate2.setInput(0, norgate1.getOutput(0));
    norgate2.setInput(1, inputs[1]);
    norgate2.evaluate();

    writeToFile("settings.txt");
}

bool setReset::getOutput(int index) const
{
    return norgate2.getOutput(0);
}