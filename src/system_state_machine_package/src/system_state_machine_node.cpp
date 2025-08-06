#include "state_machine/context.hpp"
#include "states/initializing_state.hpp"
#include "states/running_state.hpp"

#include <rclcpp/rclcpp.hpp>

#include <chrono>
#include <thread>

class StateMachineNode : public rclcpp::Node {
public:
    StateMachineNode() : Node("state_machine_node") {
        context_ = std::make_unique<Context>();
        
        // Set initial state to Initializing
        auto initState = std::make_shared<InitializingState>();
        context_->setInitialState(initState);
        
        // Create timer for state changes
        timer_ = this->create_wall_timer(
            std::chrono::seconds(6),
            std::bind(&StateMachineNode::timer_callback, this));
        
        // Start the context
        context_->start();
        RCLCPP_INFO(this->get_logger(), "State machine node started.");
    }

    ~StateMachineNode() {
        if (context_) {
            context_->stop();
        }
    }

private:
    void timer_callback() {
        // Change to running state after first timer callback
        if (!state_changed_) {
            auto runningState = std::make_shared<RunningState>();
            auto stateChangeEvent = std::make_shared<StateChangeEvent>(runningState);
            context_->postEvent(stateChangeEvent);
            state_changed_ = true;
            RCLCPP_INFO(this->get_logger(), "Changing to running state");
        }
    }

    std::unique_ptr<Context> context_;
    rclcpp::TimerBase::SharedPtr timer_;
    bool state_changed_{false};
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<StateMachineNode>());
    rclcpp::shutdown();

    return 0;
}
