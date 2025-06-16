#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class component {
public:
    virtual void evaluate() = 0;
    virtual void setInput(int index, bool value) = 0;
    virtual bool getOutput(int index) const = 0;
    virtual ~component() = default;
};

class AndGate : public component {
    bool inputs[2] = {false, false};
    bool output = false;

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 2) inputs[index] = value;
    }

    void evaluate() override {
        output = inputs[0] && inputs[1];
    }

    bool getOutput(int index) const override {
        return output;
    }
};

class NotGate : public component {
    bool inputs[1] = {false};
    bool output = false;

public:
    void setInput(int index, bool value) override {
        if (index == 0) inputs[index] = value;
    }
    
    void evaluate() override {
        output = !inputs[0];
    }

    bool getOutput(int index) const override{
        return output;
    }
};

class NandGate : public component {
    AndGate andGate;
    NotGate notGate;

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 2) {
            andGate.setInput(index, value);
        }
    }

    void evaluate() override {
        andGate.evaluate();
        bool andResult = andGate.getOutput(0);

        notGate.setInput(0, andResult);
        notGate.evaluate();
    }

    bool getOutput(int index) const override {
        return notGate.getOutput(0);
    }
};

class OrGate : public component {
    NotGate notGate;
    NotGate notGate2;
    NandGate nandGate;

public: 
    void setInput (int index, bool value) override {
        if (index == 0) {
            notGate.setInput(0, value);
        }
        if (index == 1){
            notGate2.setInput(0, value);
        }
    }

    void evaluate() override {
        notGate.evaluate();
        bool notGateResult = notGate.getOutput(0);

        notGate2.evaluate();
        bool notGateResult2 = notGate2.getOutput(0);

        nandGate.setInput(0, notGateResult);
        nandGate.setInput(1, notGateResult2);
        nandGate.evaluate();
    }

    bool getOutput(int index) const override {
        return nandGate.getOutput(0);
    }
};

class OrGate3 : public component {
    bool inputs[3] = {false};

    OrGate orgate1;
    OrGate orgate2;

public:

    void setInput(int index, bool value) override {
        if (index >= 0 && index < 3){
            inputs[index] = value;
        }
    }

    void evaluate() override {
        orgate1.setInput(0, inputs[0]);
        orgate1.setInput(1, inputs[1]);
        orgate1.evaluate();

        orgate2.setInput(0, orgate1.getOutput(0));
        orgate2.setInput(1, inputs[2]);
        orgate2.evaluate();
    }

    bool getOutput(int index) const override {
        return orgate2.getOutput(0);
    }
};

class OrGate4 :  public component {
    bool inputs[4] = {false};

    OrGate3 orgate3;
    OrGate orgate;

public:
    
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 4){
            inputs[index] = value;
        }
    }

    void evaluate() override{
        orgate3.setInput(0, inputs[0]);
        orgate3.setInput(1, inputs[1]);
        orgate3.setInput(2, inputs[2]);
        orgate3.evaluate();

        orgate.setInput(0, orgate3.getOutput(0));
        orgate.setInput(1, inputs[3]);
        orgate.evaluate();
    }

    bool getOutput(int index) const override {
        return orgate.getOutput(0);
    }
};

class XorGate : public component {
    OrGate orGate;
    NandGate nandGate;
    AndGate andGate;

public:
    void setInput (int index, bool value) override {
        if (index == 0){
            orGate.setInput(index, value);
            nandGate.setInput(index, value);
        }
        if (index == 1){
            orGate.setInput(index, value);
            nandGate.setInput(index, value);
        }
    }

    void evaluate() override {
        orGate.evaluate();
        bool orGateResult = orGate.getOutput(0);

        nandGate.evaluate();
        bool nandGateResult = nandGate.getOutput(0);

        andGate.setInput(0, orGateResult);
        andGate.setInput(1, nandGateResult);
        andGate.evaluate();
    }

    bool getOutput(int index) const override {
        return andGate.getOutput(0);
    }
};

class NorGate : public component {
    
    bool inputs[2] = {false, false};

    OrGate orgate;
    NotGate notgate;

public:
    void setInput (int index, bool value) override {
        if (index >= 0 && index < 2){
            inputs[index] = value;
        }
    }

    void evaluate() override {
        orgate.setInput(0, inputs[0]);
        orgate.setInput(1, inputs[1]);
        orgate.evaluate();

        notgate.setInput(0, orgate.getOutput(0));
        notgate.evaluate();
    }

    bool getOutput(int index) const override {
        return notgate.getOutput(0);
    }
};

class Adder : public component {
    XorGate xor1;
    XorGate xor2;
    AndGate and1;
    AndGate and2;
    OrGate orGate;

    bool inputs[3] = {false, false, false}; 

public: 
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 3) {
            inputs[index] = value;
        }
    }

    void evaluate() override {

        xor1.setInput(0, inputs[0]);
        xor1.setInput(1, inputs[1]);
        xor1.evaluate();
        bool resultXor1 = xor1.getOutput(0);

        and1.setInput(0, inputs[0]);
        and1.setInput(1, inputs[1]);;
        and1.evaluate();
        bool resultAnd1 = and1.getOutput(0);

        xor2.setInput(0, resultXor1);
        xor2.setInput(1, inputs[2]);
        xor2.evaluate();
        bool resultXor2 = xor2.getOutput(0);

        and2.setInput(0, resultXor1);
        and2.setInput(1, inputs[2]);
        and2.evaluate();
        bool resultAnd2 = and2.getOutput(0);

        orGate.setInput(0, resultAnd1);
        orGate.setInput(1, resultAnd2);
        orGate.evaluate();
        bool resultOr = orGate.getOutput(0);
    }

    bool getOutput(int index) const override {
        if (index == 0) return xor2.getOutput(0);
        if (index == 1) return orGate.getOutput(0);
        return false;
    }
};

class FourBitAdder : public component {
    bool inputs[9] = {false, false, false, false, false, false, false, false, false};

    Adder adder1;
    Adder adder2;
    Adder adder3;
    Adder adder4;

public:
    void setInput(int index, bool value) override {
        if(index >= 0 && index < 9){
            inputs[index] = value;
        }
    }

    void evaluate() override {
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

    bool getOutput(int index) const override {
        if (index == 0) return adder4.getOutput(0);
        if (index == 1) return adder3.getOutput(0);
        if (index == 2) return adder2.getOutput(0);
        if (index == 3) return adder1.getOutput(0);
        if (index == 4) return adder4.getOutput(1);
        return false;
    }
};

class ALU : public component {
    // -8 to 7
    // 0 - 3, where 0 is negative, A
    // 4 - 7, where 4 is negative, B
    // 8, subtract
    bool inputs[9] = {false};

    XorGate xorgate[4];
    FourBitAdder fourbitadder;
    NotGate notgate[4];
    AndGate andgate[3];

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 9){
            inputs[index] = value;
        }
    }

    void evaluate() override {
        for (int i = 0; i < 4; ++i){
            xorgate[i].setInput(0, inputs[i + 4]);
            xorgate[i].setInput(1, inputs[8]);
            xorgate[i].evaluate();
        }

        for (int i = 0; i < 4; ++i){
            fourbitadder.setInput(i, inputs[i]);
        }
        for (int i = 0; i < 4; ++i){
            fourbitadder.setInput(i + 4, xorgate[i].getOutput(0));
        }
        fourbitadder.setInput(8, inputs[8]);
        fourbitadder.evaluate();

        //Output
        //0 - 3, number where 0 is negative
        // 6, zero or not
        // 5, Negative or Positive
        // 4, Carry

        for (int i = 0; i < 4; ++i){
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

    bool getOutput(int index) const override {
        if (index >= 0 && index <= 3) return fourbitadder.getOutput(index);
        if (index == 4) return fourbitadder.getOutput(4); //Carry
        if (index == 5) return fourbitadder.getOutput(0); //Negative
        if (index == 6) return andgate[2].getOutput(0); // Zero
        return false;
    }
};

void loadInputsToALU(ALU* alu, int a, int b, bool subtract) {

    a = std::clamp(a, -8, 7);
    b = std::clamp(b, -8, 7);

    std::bitset<4> bitsA(a < 0 ? (16 + a) : a); 
    std::bitset<4> bitsB(b < 0 ? (16 + b) : b);

    for (int i = 0; i < 4; ++i) {
        alu->setInput(i, bitsA[3 - i]);     
        alu->setInput(i + 4, bitsB[3 - i]); 
    }

    alu->setInput(8, subtract);             
}

int outputFromALUToInt(ALU* alu) {
    int value = 0;
    for (int i = 0; i < 4; ++i) {
        value |= (alu->getOutput(i) << (3 - i));
    }

    if (value >= 8) value -= 16;
    return value;
}

class setReset : public component {

    // index 0, Set
    // index 1, Reset

    bool inputs[2] = {false, false};
    bool storedOutput = false;

    NorGate norgate1;
    NorGate norgate2;

    void writeToFile(const std::string& filename) const {
        std::ifstream inputFile(filename);
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line)) {
            // Change which line to find
            if (line.find("outputSR = 0") != std::string::npos || line.find("outputSR = 1") != std::string::npos) {
                line = "outputSR = " + std::to_string(norgate2.getOutput(0));
            }
            lines.push_back(line);
        }

        inputFile.close();

        std::ofstream outputFile(filename);
        for (const auto& modifiedLine : lines) {
            outputFile << modifiedLine << "\n";
        }
        outputFile.close();
    }

    int getFromFile(const std::string& filename) const {
        std::ifstream inputFile(filename);
        std::string line;
        int value;

        while (std::getline(inputFile, line)) {
            if (line.find("outputSR = 0") != std::string::npos || line.find("outputSR = 1") != std::string::npos) {
                // Change which line to find
                std::string valueStr = line.substr(line.find('=') + 1);
                value = std::stoi(valueStr);
            }
        }

        inputFile.close();

        return value;
        
    }
    
public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 2){
            inputs[index] = value;
        }
    }

    void evaluate() override {

        storedOutput = getFromFile("settings.txt");

        norgate1.setInput(0, inputs[0]);
        norgate1.setInput(1, storedOutput);
        norgate1.evaluate();

        norgate2.setInput(0, norgate1.getOutput(0));
        norgate2.setInput(1, inputs[1]);
        norgate2.evaluate();

        writeToFile("settings.txt");
    }

    bool getOutput(int index) const override {
        return norgate2.getOutput(0);
    }


};

class DataLatch : public component {
    // Index 1 data
    // Index 2 store

    int countPrivate;

    bool inputs[2] = {false, false};
    bool storeOutput = false;

    NorGate norgate1;
    NorGate norgate2;
    NotGate notgate;
    AndGate andgate1;
    AndGate andgate2;

    void writeToFile(const std::string& filename) const {
        std::ifstream inputFile(filename);
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line)) {
            // Change which line to find
            if (line.find("outputDL" + std::to_string(countPrivate) + " = 0") != std::string::npos 
            || line.find("outputDL" + std::to_string(countPrivate) + " = 1") != std::string::npos) {
                line = "outputDL" + std::to_string(countPrivate) +" = " + std::to_string(norgate2.getOutput(0));
            }
            lines.push_back(line);
        }

        inputFile.close();

        std::ofstream outputFile(filename);
        for (const auto& modifiedLine : lines) {
            outputFile << modifiedLine << "\n";
        }
        outputFile.close();
        
        //std::cout << "Writing outputDL" << countPrivate << " = " << norgate2.getOutput(0) << std::endl;

    }

    int getFromFile(const std::string& filename) const {
        std::ifstream inputFile(filename);
        std::string line;
        int value;

        while (std::getline(inputFile, line)) {
            if (line.find("outputDL" + std::to_string(countPrivate) + " = 0") != std::string::npos 
            || line.find("outputDL" + std::to_string(countPrivate) + " = 1") != std::string::npos) {
                // Change which line to find
                std::string valueStr = line.substr(line.find('=') + 1);
                value = std::stoi(valueStr);
            }
        }

        inputFile.close();

        //std::cout << "Read outputDL" << countPrivate << " = " << value << std::endl;


        return value;
        
    }

public:

    DataLatch(int count) : countPrivate(count) {}

    void setInput(int index, bool value) override {
        if (index >= 0 && index < 2){
            inputs[index] = value;
        }
    }

    void evaluate() override {

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

    bool getOutput(int index) const override {
        return norgate2.getOutput(0);
    }

    
};

class DFlipFlop : public component {

    // index 0 Data
    // index 1 Clock

    int countP1;
    int countP2;

    bool inputs[2] = {false};

    component* notgate = new NotGate();
    component* dl1 = new DataLatch(countP1);
    component* dl2 = new DataLatch(countP2);

public:
    DFlipFlop(int count1, int count2) : countP1(count1), countP2(count2) {}
    
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 2){
            inputs[index] = value;
        }
    }

    void evaluate() override {
        notgate->setInput(0, inputs[1]);
        notgate->evaluate();

        dl1->setInput(0, inputs[0]);
        dl1->setInput(1, notgate->getOutput(0));
        dl1->evaluate();

        dl2->setInput(0, dl1->getOutput(0));
        dl2->setInput(1, inputs[1]);
        dl2->evaluate();
    }

    bool getOutput(int index) const override {
        return dl2->getOutput(0);
    }

};

class SevenSegmentDriver : public component {
    // inputs are data from register

    bool inputs [4] = {false};

    XorGate xorgate[3];
    NotGate notgate;
    NandGate nandgate[2];
    OrGate orgate[5];
    AndGate andgate[4];

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 4){
            inputs[index] = value;
        }
    }

    void evaluate() override {
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

    bool getOutput(int index) const override {
        if (index == 0) return orgate[1].getOutput(0);
        if (index == 1) return nandgate[1].getOutput(0);
        if (index == 2) return orgate[4].getOutput(0);
        if (index == 3) return andgate[0].getOutput(0);
        if (index == 4) return andgate[1].getOutput(0);
        if (index == 5) return andgate[2].getOutput(0);
        if (index == 6) return andgate[3].getOutput(0);

        return false;
    }

};

class DigitDisplay {
public:

    void printDisplay(const std::vector<bool>& segments) {
        if (segments.size() != 7) {
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
};

class OneBitRegister : public component {

    // Index 0 Data
    // Index 1 Store
    // Index 2 Clock
    bool inputs[3] = {false};
    bool storedOutput = false;

    int countP1; // DL type
    int countP2; // DL type
    int countP3; // Reg type

    component* notgate = new NotGate();
    component* andgate1 = new AndGate();
    component* andgate2 = new AndGate();
    component* orgate = new OrGate();
    component* dff = new DFlipFlop(countP1, countP2);

        void writeToFile(const std::string& filename) const {
        std::ifstream inputFile(filename);
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line)) {
            // Change which line to find
            if (line.find("outputReg" + std::to_string(countP3) + " = 0") != std::string::npos 
            || line.find("outputReg" + std::to_string(countP3) + " = 1") != std::string::npos) {
                line = "outputReg" + std::to_string(countP3) + " = " + std::to_string(dff->getOutput(0));
            }
            lines.push_back(line);
        }

        inputFile.close();

        std::ofstream outputFile(filename);
        for (const auto& modifiedLine : lines) {
            outputFile << modifiedLine << "\n";
        }
        outputFile.close();
    }

    int getFromFile(const std::string& filename) const {
        std::ifstream inputFile(filename);
        std::string line;
        int value = 0;

        while (std::getline(inputFile, line)) {
            if (line.find("outputReg" + std::to_string(countP3) + " = 0") != std::string::npos 
            || line.find("outputReg" + std::to_string(countP3) + " = 1") != std::string::npos) {
                // Change which line to find
                std::string valueStr = line.substr(line.find('=') + 1);
                value = std::stoi(valueStr);
            }
        }

        inputFile.close();

        return value;
        
    }

public:
    OneBitRegister(int count1, int count2, int count3) : countP1(count1), countP2(count2), countP3(count3) {}

    void setInput(int index, bool value) override {
        if (index >= 0 && index < 3){
            inputs[index] = value;
        }
    }

    void evaluate() override {

        storedOutput = getFromFile("settings.txt");
        //std::cout << "storedOutput: " << storedOutput << std::endl;

        notgate->setInput(0, inputs[1]);
        notgate->evaluate();
        //std::cout << "notgate: " << notgate->getOutput(0) << std::endl;

        andgate1->setInput(0, storedOutput);
        andgate1->setInput(1, notgate->getOutput(0));
        andgate1->evaluate();
        //std::cout << "andgate1: " << andgate1->getOutput(0) << std::endl;

        andgate2->setInput(0, inputs[1]);
        andgate2->setInput(1, inputs[0]);
        andgate2->evaluate();
        //std::cout << "andgate2: " << andgate2->getOutput(0) << std::endl;

        orgate->setInput(0, andgate1->getOutput(0));
        orgate->setInput(1, andgate2->getOutput(0));
        orgate->evaluate();
        //std::cout << "orgate: " << orgate->getOutput(0) << std::endl;

        dff->setInput(0, orgate->getOutput(0));  // D
        dff->setInput(1, inputs[2]);             // Clock
        dff->evaluate();
        //std::cout << "dff: " << dff->getOutput(0) << std::endl;

        writeToFile("settings.txt");
    }

    bool getOutput(int index) const override {
        return dff->getOutput(0);
    }

};

class FourBitRegister : public component {
    // Index 3 - data 0
    // Index 2 - data 1
    // Index 1 - data 2
    // Index 0 - data 3
    // Index 4 - store
    // Index 5 - clock

    bool inputs[6] = {false};

    int countDLP1; int countDLP2; int countDLP3; int countDLP4; int countDLP5;
    int countDLP6; int countDLP7; int countDLP8;    
    
    int countRegP1; int countRegP2; int countRegP3; int countRegP4;

    component* reg1 = new OneBitRegister(countDLP1, countDLP2, countRegP1);
    component* reg2 = new OneBitRegister(countDLP3, countDLP4, countRegP2);
    component* reg3 = new OneBitRegister(countDLP5, countDLP6, countRegP3);
    component* reg4 = new OneBitRegister(countDLP7, countDLP8, countRegP4);

    component* display = new SevenSegmentDriver;
    DigitDisplay printDisplay;

public:

    FourBitRegister(int countDL1, int countDL2, int countDL3, int countDL4, int countDL5,
    int countDL6, int countDL7, int countDL8, int countReg1, int countReg2, int countReg3,
    int countReg4) : countDLP1(countDL1), countDLP2(countDL2), countDLP3(countDL3),
    countDLP4(countDL4), countDLP5(countDL5), countDLP6(countDL6), countDLP7(countDL7),
    countDLP8(countDL8), countRegP1(countReg1), countRegP2(countReg2), countRegP3(countReg3),
    countRegP4(countReg4) {}


    void setInput(int index, bool value) override {
        if (index >= 0 && index < 6){
            inputs[index] = value;
        }
    }

    void evaluate() override {
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
        for (int i = 0; i < 7; i++){
            segmentStates.push_back(display->getOutput(i));
        }

        printDisplay.printDisplay(segmentStates);
    }

    bool getOutput(int index) const override {

        if (index == 0) return reg1->getOutput(0);
        if (index == 1) return reg2->getOutput(0);
        if (index == 2) return reg3->getOutput(0);
        if (index == 3) return reg4->getOutput(0);

        return false;
    }


};

class Dabble : public component {
    
    bool inputs[4] = {false};

    XorGate xorgate[3];
    NorGate nor[4];
    OrGate orgate;
    AndGate andgate;

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 4){
            inputs[index] = value;
        }
    }

    void evaluate() override {

        xorgate[0].setInput(0, inputs[3]);
        xorgate[0].setInput(1, inputs[0]);
        xorgate[0].evaluate();

        nor[0].setInput(0, inputs[0]);
        nor[0].setInput(1, inputs[1]);
        nor[0].evaluate();

        xorgate[1].setInput(0, inputs[0]);
        xorgate[1].setInput(1, inputs[2]);
        xorgate[1].evaluate();

        nor[1].setInput(0, xorgate[0].getOutput(0));
        nor[1].setInput(1, xorgate[1].getOutput(0));
        nor[1].evaluate();

        nor[2].setInput(0, nor[1].getOutput(0));
        nor[2].setInput(1, nor[0].getOutput(0));
        nor[2].evaluate();

        orgate.setInput(0, nor[0].getOutput(0));
        orgate.setInput(1, xorgate[0].getOutput(0));
        orgate.evaluate();

        nor[3].setInput(0, orgate.getOutput(0));
        nor[3].setInput(1, inputs[2]);
        nor[3].evaluate();

        andgate.setInput(0, orgate.getOutput(0));
        andgate.setInput(1, xorgate[1].getOutput(0));
        andgate.evaluate();

        xorgate[2].setInput(0, nor[2].getOutput(0));
        xorgate[2].setInput(1, inputs[3]);
        xorgate[2].evaluate();
    }

    bool getOutput(int index) const override {
        if (index == 0) return nor[2].getOutput(0);
        if (index == 1) return nor[3].getOutput(0);
        if (index == 2) return andgate.getOutput(0);
        if (index == 3) return xorgate[2].getOutput(0);
        return false;
    }

};

class Mux : public component {
    // Inputs
    // 0 - 3 first number
    // 4 - 7 second number
    // 8 Select

    bool inputs[9] = {false};

    NotGate notgate;
    AndGate andgate[8];
    OrGate orgate[4];

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 9) {
            inputs[index] = value;
        }
    }

    void evaluate() override {
        notgate.setInput(0, inputs[8]);
        notgate.evaluate();

        andgate[0].setInput(0, inputs[0]);
        andgate[0].setInput(1, notgate.getOutput(0));
        andgate[0].evaluate();

        andgate[1].setInput(0, inputs[1]);
        andgate[1].setInput(1, notgate.getOutput(0));
        andgate[1].evaluate();

        andgate[2].setInput(0, inputs[2]);
        andgate[2].setInput(1, notgate.getOutput(0));
        andgate[2].evaluate();

        andgate[3].setInput(0, inputs[3]);
        andgate[3].setInput(1, notgate.getOutput(0));
        andgate[3].evaluate();

        andgate[4].setInput(0, inputs[4]);
        andgate[4].setInput(1, inputs[8]);
        andgate[4].evaluate();

        andgate[5].setInput(0, inputs[5]);
        andgate[5].setInput(1, inputs[8]);
        andgate[5].evaluate();

        andgate[6].setInput(0, inputs[6]);
        andgate[6].setInput(1, inputs[8]);
        andgate[6].evaluate();

        andgate[7].setInput(0, inputs[7]);
        andgate[7].setInput(1, inputs[8]);
        andgate[7].evaluate();

        orgate[0].setInput(0, andgate[0].getOutput(0));
        orgate[0].setInput(1, andgate[4].getOutput(0));
        orgate[0].evaluate();

        orgate[1].setInput(0, andgate[1].getOutput(0));
        orgate[1].setInput(1, andgate[5].getOutput(0));
        orgate[1].evaluate();

        orgate[2].setInput(0, andgate[2].getOutput(0));
        orgate[2].setInput(1, andgate[6].getOutput(0));
        orgate[2].evaluate();

        orgate[3].setInput(0, andgate[3].getOutput(0));
        orgate[3].setInput(1, andgate[7].getOutput(0));
        orgate[3].evaluate();
    }

    bool getOutput(int index) const override {
        if (index == 0) return orgate[0].getOutput(0);
        if (index == 1) return orgate[1].getOutput(0);
        if (index == 2) return orgate[2].getOutput(0);
        if (index == 3) return orgate[3].getOutput(0);

        return false;
    }
};

class TriStateBuffer : public component {
    // 0 is Enable output
    // 1 is Data
    // Output is 1, 0, or Z (3rd state)

    bool inputs[2] = {false};
    
    // 0 = false, 1 = true, 2 = Z
    int output = 2;

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 2) {
            inputs[index] = value;
        }
    }

    void evaluate() override {
        if (inputs[0] == 1){
            output = inputs[1];
        }
        if (inputs[0] == 0){
            output = 2;
        }
    }

    bool getOutput(int index) const override {
        if (output == 0) return false;
        if (output == 1) return true;
        if (output == 2) {
            std::cout << "buffer is off" << std::endl;
            return false;
        }
        return false;
    }

    bool isUnkown() const {
        return output == 2;
    }
};

class BusBuffer: public component {
    // Inputs 0 - output enable
    // 1 - 4 Data
    bool inputs[5] = {false};

    TriStateBuffer buffer[4];

public:
    void setInput(int index, bool value) override {
        if (index >= 0 && index < 5){
            inputs[index] = value;
        }
    }

    void evaluate() override {

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

    bool getOutput(int index) const override {
        if (index == 0) return buffer[0].getOutput(0);
        if (index == 1) return buffer[1].getOutput(0);
        if (index == 2) return buffer[2].getOutput(0);
        if (index == 3) return buffer[3].getOutput(0);
    }
};

int main(){
    /*examples
    component* gate = new AndGate();
    gate->setInput(0, true);
    gate->setInput(1, true);

    gate->evaluate();
    bool result = gate->getOutput(0);  
    std::cout << "result of AND gate: " << result << std::endl;
    
     
    //Biggest number for 4 Bit Adder is 15
    //Biggest number for ALU is -8 to 7
    ALU* alu = new ALU();

    int a = 1;
    int b = -8;
    bool subtract = false;

    loadInputsToALU(alu, a, b, subtract);
    alu->evaluate();

    int result = outputFromALUToInt(alu);
    std::cout << "Result: " << result << std::endl;

    std::cout << "Carry: " << alu->getOutput(4) << std::endl;
    std::cout << "Negative: " << alu->getOutput(5) << std::endl;
    std::cout << "Zero: " << alu->getOutput(6) << std::endl;

    delete alu;


    dynamic_cast<setReset*>(sr)->writeToFile("settings.txt", "outputSR = ");
    std::cout << dynamic_cast<setReset*>(sr)->getFromFile("settings.txt");

    To use dff you first need to set data run, and then set clock and run again
    Works as above for 1-bit-register too

    // 4 bit Register
    component* reg = new FourBitRegister(1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4); 

    reg->setInput(0, true);   
    reg->setInput(1, false);   
    reg->setInput(2, true);
    reg->setInput(3, true);
    reg->setInput(4, true);
    reg->setInput(5, true);
      
    reg->evaluate();

    std::cout << reg->getOutput(0) << std::endl << 
    reg->getOutput(1) << std::endl <<
    reg->getOutput(2) << std::endl <<
    reg->getOutput(3) << std::endl << std::endl;

  

    component* gate = new SevenSegmentDriver();
    gate->setInput(0, false);
    gate->setInput(3, false);

    gate->evaluate();

    std::vector<bool> segmentStates;
    for (int i = 0; i < 7; i++){
        std::cout << gate->getOutput(i) << std::endl;
        segmentStates.push_back(gate->getOutput(i));
    }

    DigitDisplay display;
    display.printDisplay(segmentStates);
    
  */

  component* gate = new TriStateBuffer();
  gate->setInput(0, 0);
  gate->setInput(1, 1);
  gate->evaluate();
  std::cout << gate->getOutput(0);


}