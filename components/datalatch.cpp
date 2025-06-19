#include "datalatch.h"

void DataLatch::writeToFile(const std::string &filename) const
{
    std::ifstream inputFile(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line))
    {
        // Change which line to find
        if (line.find("outputDL" + std::to_string(countPrivate) + " = 0") != std::string::npos || line.find("outputDL" + std::to_string(countPrivate) + " = 1") != std::string::npos)
        {
            line = "outputDL" + std::to_string(countPrivate) + " = " + std::to_string(norgate2.getOutput(0));
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

    // std::cout << "Writing outputDL" << countPrivate << " = " << norgate2.getOutput(0) << std::endl;
}

int DataLatch::getFromFile(const std::string &filename) const
{
    std::ifstream inputFile(filename);
    std::string line;
    int value;

    while (std::getline(inputFile, line))
    {
        if (line.find("outputDL" + std::to_string(countPrivate) + " = 0") != std::string::npos || line.find("outputDL" + std::to_string(countPrivate) + " = 1") != std::string::npos)
        {
            // Change which line to find
            std::string valueStr = line.substr(line.find('=') + 1);
            value = std::stoi(valueStr);
        }
    }

    inputFile.close();

    // std::cout << "Read outputDL" << countPrivate << " = " << value << std::endl;

    return value;
}

void DataLatch::setInput(int index, bool value)
{
    if (index >= 0 && index < 2)
    {
        inputs[index] = value;
    }
}

void DataLatch::evaluate()
{

    storeOutput = getFromFile("settings.txt");

    andgate1.setInput(0, inputs[0]);
    andgate1.setInput(1, inputs[1]);
    andgate1.evaluate();

    notgate.setInput(0, inputs[0]);
    notgate.evaluate();

    andgate2.setInput(0, inputs[1]);
    andgate2.setInput(1, notgate.getOutput(0));
    andgate2.evaluate();

    norgate1.setInput(0, andgate1.getOutput(0));
    norgate1.setInput(1, storeOutput);
    norgate1.evaluate();

    norgate2.setInput(0, norgate1.getOutput(0));
    norgate2.setInput(1, andgate2.getOutput(0));
    norgate2.evaluate();

    writeToFile("settings.txt");
}

bool DataLatch::getOutput(int index) const
{
    return norgate2.getOutput(0);
}