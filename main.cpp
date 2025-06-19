#include "components/inclcomp.h"

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

    component* gate = new BusBuffer();
    gate->setInput(0, 1);
    gate->setInput(1, 1);
    gate->setInput(2, 0);
    gate->setInput(3, 1);
    gate->setInput(4, 1);
    gate->evaluate();

    std::cout<<gate->getOutput(0)<<std::endl;

}