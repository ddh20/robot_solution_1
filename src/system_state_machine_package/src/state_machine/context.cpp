#include "state_machine/context.hpp"

void Context::setInitialState(std::shared_ptr<State> state) {
  currentState_ = state;
  if (currentState_) {
    currentState_->entry();
  }
}

void Context::postEvent(std::shared_ptr<Event> event) {
  std::lock_guard<std::mutex> lock(queueMutex_);
  eventQueueActive_.push(event);
}

void Context::start() {
  running_ = true;
  workerThread_ = std::thread([this]() { this->processEvents(); });
}

void Context::stop() {
  running_ = false;
  if (workerThread_.joinable())
    workerThread_.join();
}

Context::~Context() {
  stop();
  if (currentState_)
    currentState_->exit();
}

void Context::processEvents() {
  MyPublisher publisher;

  while (running_) {
    static auto lastIterationEnd = std::chrono::steady_clock::now();
    const auto iterationStart = std::chrono::steady_clock::now();

    // Calculate sleep duration (skip sleep on first iteration)
    if (lastIterationEnd != std::chrono::steady_clock::time_point{}) {
      const auto elapsedTime = iterationStart - lastIterationEnd;
      const auto sleepDuration = std::chrono::seconds(5) - elapsedTime;
      if (sleepDuration > std::chrono::seconds(0)) {
        std::this_thread::sleep_for(sleepDuration);
      }
    }

    // Swap queues
    std::queue<std::shared_ptr<Event>> eventsToProcess;
    {
      std::lock_guard<std::mutex> lock(queueMutex_);
      std::swap(eventQueueActive_, eventsToProcess);
    }

    // Process all events in the swapped queue
    while (!eventsToProcess.empty()) {
      auto event = eventsToProcess.front();
      eventsToProcess.pop();

      if (event->isStateChangeEvent()) {
        auto stateChangeEvent =
            std::dynamic_pointer_cast<StateChangeEvent>(event);

        publisher.publish_message(currentState_->getStateName());
        publisher.publish_message(
            stateChangeEvent->getNewState()->getStateName());

        if (currentState_)
          currentState_->exit();
        currentState_ = stateChangeEvent->getNewState();
        if (currentState_)
          currentState_->entry();
        if (currentState_)
          currentState_->execute(*event);
      } else {
        if (currentState_)
          currentState_->execute(*event);
      }
    }
  }
}
