#include "state_machine/event.hpp"

bool Event::isStateChangeEvent() const {
    return false;
}

bool StateChangeEvent::isStateChangeEvent() const {
    return true;
}

std::shared_ptr<class State> StateChangeEvent::getNewState() const {
    return newState_;
}
