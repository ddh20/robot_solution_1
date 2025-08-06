#pragma once

#include <memory>

class Event {
public:
    virtual ~Event() = default;
    virtual bool isStateChangeEvent() const { return false; }
};

class StateChangeEvent : public Event {
public:
    StateChangeEvent(std::shared_ptr<class State> newState) : newState_(newState) {}
    bool isStateChangeEvent() const override { return true; }
    std::shared_ptr<class State> getNewState() const { return newState_; }

private:
    std::shared_ptr<class State> newState_;
};
