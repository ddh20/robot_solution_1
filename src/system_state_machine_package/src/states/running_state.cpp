#include "states/running_state.hpp"

#include "state_machine/event.hpp"
#include "state_machine/state.hpp"

#include <rclcpp/rclcpp.hpp>

const auto logger = rclcpp::get_logger("RunningState");

void RunningState::entry() {
    RCLCPP_INFO(logger, "Entering Running State");
}

void RunningState::exit() {
    RCLCPP_INFO(logger, "Exiting Running State");
}

void RunningState::execute(const Event&) {
    RCLCPP_INFO(logger, "Executing Running State");
}

std::string RunningState::getStateName() const {
    return "RunningState";
}
