#pragma once

#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <atomic>

#include "state_machine/state.hpp"
#include "state_machine/event.hpp"
#include "state_machine_message_publisher.hpp"

class Context {
public:
    Context() : running_(false) {}

    void setInitialState(std::shared_ptr<State> state);
    void postEvent(std::shared_ptr<Event> event);
    void start();
    void stop();

    ~Context();

private:
    void processEvents();

    std::queue<std::shared_ptr<Event>> eventQueueActive_;
    std::mutex queueMutex_;
    std::shared_ptr<State> currentState_;
    std::atomic<bool> running_;
    std::thread workerThread_;
};