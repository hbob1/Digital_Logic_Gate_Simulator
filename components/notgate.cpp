#include "notgate.h"

NotGate::NotGate() {}

void NotGate::setInput(int index, bool value) {
    if (index == 0) inputs[index] = value;
}
    
void NotGate::evaluate() {
    output = !inputs[0];
}

bool NotGate::getOutput(int index) const {
    return output;
}
