#pragma once

#include "state_machine/event.hpp"
#include "state_machine/state.hpp"

class InitializingState : public State {
public:
    void entry() override;
    void exit() override;
    void execute(const Event&) override;

    std::string getStateName() const override;
};
