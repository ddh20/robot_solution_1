#pragma once

#include "state_machine/event.hpp"

#include <string>

class State {
public:
    virtual ~State() = default;
    
    virtual void entry() {}
    virtual void exit() {}
    virtual void execute(const Event& event) {}

    virtual std::string getStateName() const = 0;
};
