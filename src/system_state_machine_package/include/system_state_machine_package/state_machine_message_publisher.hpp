#pragma once

#include "rclcpp/rclcpp.hpp"

#include "system_interfaces/msg/system_state.hpp"

#include "std_msgs/msg/header.hpp" // Required for std_msgs::msg::Header

#include <memory>

class MyPublisher : public rclcpp::Node
{
public:
  MyPublisher() : Node("my_publisher")
  {
    publisher_ = this->create_publisher<system_interfaces::msg::SystemState>("system_state_topic", 10);
  }

  void publish_message(const std::string& state)
  {
    auto msg = system_interfaces::msg::SystemState();
    msg.header.stamp = this->now(); // Set the timestamp
    msg.header.frame_id = "base_link"; // Set the frame_id
    msg.system_state = state; // Example state

    publisher_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.system_state.c_str());
  }

private:
  rclcpp::Publisher<system_interfaces::msg::SystemState>::SharedPtr publisher_;
};
