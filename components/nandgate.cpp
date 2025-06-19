#include "nandgate.h"

NandGate::NandGate() {}

void NandGate::setInput(int index, bool value){
    if (index >= 0 && index < 2) {
        andGate.setInput(index, value);
    }
}

void NandGate::evaluate(){
    andGate.evaluate();
    bool andResult = andGate.getOutput(0);
    notGate.setInput(0, andResult);
    notGate.evaluate();
}

bool NandGate::getOutput(int index) const {
    return notGate.getOutput(0);
}