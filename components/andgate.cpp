#include "andgate.h"

AndGate::AndGate() {
}

void AndGate::setInput(int index, bool value) {
    if (index >= 0 && index < 2)
        inputs[index] = value;
}

void AndGate::evaluate() {
    output = inputs[0] && inputs[1];
}

bool AndGate::getOutput(int index) const {
    return output;
}