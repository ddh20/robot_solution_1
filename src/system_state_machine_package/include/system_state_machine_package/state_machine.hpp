// state_machine.hpp
#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <iostream>

enum class SystemState {
    INITIALIZE,
    RUNNING,
    SHUTTING_DOWN
};

class StateMachine {
public:
    StateMachine() : current_state_(SystemState::INITIALIZE) {
        std::cout << "State machine initialized. Current state: INITIALIZE" << std::endl;
    }

    void execute() {
        switch (current_state_) {
            case SystemState::INITIALIZE:
                std::cout << "Executing INITIALIZE state." << std::endl;
                // Perform initialization tasks
                current_state_ = SystemState::RUNNING;
                break;
            case SystemState::RUNNING:
                std::cout << "Executing RUNNING state." << std::endl;
                // Perform running tasks
                current_state_ = SystemState::SHUTTING_DOWN;
                break;
            case SystemState::SHUTTING_DOWN:
                std::cout << "Executing SHUTTING_DOWN state." << std::endl;
                // Perform shutdown tasks
                current_state_ = SystemState::INITIALIZE; // Cycle back to initialize
                break;
            default:
                std::cerr << "Unknown state encountered!" << std::endl;
                break;
        }
    }

private:
    SystemState current_state_;
};

#endif // STATE_MACHINE_HPP