#pragma once

#include "norgate.h"
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class setReset : public component {
private:
    // index 0, Set
    // index 1, Reset

    bool inputs[2] = {false, false};
    bool storedOutput = false;

    NorGate norgate1;
    NorGate norgate2;

    void writeToFile(const std::string& filename) const;
    int getFromFile(const std::string& filename) const;
    
public:
    setReset();
    void setInput(int index, bool value) override;
    void evaluate() override;
    bool getOutput(int index) const;


};
