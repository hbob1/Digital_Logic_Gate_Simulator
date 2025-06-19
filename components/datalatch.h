#pragma once

#include "setreset.h"

class DataLatch : public component {
private:
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

    void writeToFile(const std::string& filename) const;
    int getFromFile(const std::string& filename) const;

public:

    DataLatch(int count) : countPrivate(count) {};
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const;

    
};
