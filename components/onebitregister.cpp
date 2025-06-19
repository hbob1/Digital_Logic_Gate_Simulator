#include "onebitregister.h"

void OneBitRegister::writeToFile(const std::string &filename) const
{
    std::ifstream inputFile(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line))
    {
        // Change which line to find
        if (line.find("outputReg" + std::to_string(countP3) + " = 0") != std::string::npos || line.find("outputReg" + std::to_string(countP3) + " = 1") != std::string::npos)
        {
            line = "outputReg" + std::to_string(countP3) + " = " + std::to_string(dff->getOutput(0));
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

int OneBitRegister::getFromFile(const std::string &filename) const
{
    std::ifstream inputFile(filename);
    std::string line;
    int value = 0;

    while (std::getline(inputFile, line))
    {
        if (line.find("outputReg" + std::to_string(countP3) + " = 0") != std::string::npos || line.find("outputReg" + std::to_string(countP3) + " = 1") != std::string::npos)
        {
            // Change which line to find
            std::string valueStr = line.substr(line.find('=') + 1);
            value = std::stoi(valueStr);
        }
    }

    inputFile.close();

    return value;
}

void OneBitRegister::setInput(int index, bool value)
{
    if (index >= 0 && index < 3)
    {
        inputs[index] = value;
    }
}

void OneBitRegister::evaluate()
{

    storedOutput = getFromFile("settings.txt");
    // std::cout << "storedOutput: " << storedOutput << std::endl;

    notgate->setInput(0, inputs[1]);
    notgate->evaluate();
    // std::cout << "notgate: " << notgate->getOutput(0) << std::endl;

    andgate1->setInput(0, storedOutput);
    andgate1->setInput(1, notgate->getOutput(0));
    andgate1->evaluate();
    // std::cout << "andgate1: " << andgate1->getOutput(0) << std::endl;

    andgate2->setInput(0, inputs[1]);
    andgate2->setInput(1, inputs[0]);
    andgate2->evaluate();
    // std::cout << "andgate2: " << andgate2->getOutput(0) << std::endl;

    orgate->setInput(0, andgate1->getOutput(0));
    orgate->setInput(1, andgate2->getOutput(0));
    orgate->evaluate();
    // std::cout << "orgate: " << orgate->getOutput(0) << std::endl;

    dff->setInput(0, orgate->getOutput(0)); // D
    dff->setInput(1, inputs[2]);            // Clock
    dff->evaluate();
    // std::cout << "dff: " << dff->getOutput(0) << std::endl;

    writeToFile("settings.txt");
}

bool OneBitRegister::getOutput(int index) const
{
    return dff->getOutput(0);
}