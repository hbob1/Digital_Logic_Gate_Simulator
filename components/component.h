#pragma once

class component {
public:
    virtual void evaluate() = 0;
    virtual void setInput(int index, bool value) = 0;
    virtual bool getOutput(int index) const = 0;
    virtual ~component() = default;
};
