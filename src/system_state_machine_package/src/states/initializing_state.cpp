#include "states/initializing_state.hpp"

#include "state_machine/event.hpp"
#include "state_machine/state.hpp"

#include <rclcpp/rclcpp.hpp>

const auto logger = rclcpp::get_logger("InitializingState");

void InitializingState::entry() {
    RCLCPP_INFO(logger, "Entering Initializing State");
}

void InitializingState::exit() {
    RCLCPP_INFO(logger, "Exiting Initializing State");
}

void InitializingState::execute(const Event&) {
    RCLCPP_INFO(logger, "Executing Initializing State");
}

std::string InitializingState::getStateName() const {
    return "InitializingState";
}
