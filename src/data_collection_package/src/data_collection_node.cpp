#include "rclcpp/rclcpp.hpp"
#include "system_interfaces/msg/system_state.hpp" // Include your custom message header

class DataCollectionSubscriber : public rclcpp::Node
{
public:
  DataCollectionSubscriber()
  : Node("data_collection") // Node name
  {
    subscription_ = this->create_subscription<system_interfaces::msg::SystemState>(
      "system_state_topic", // Topic name
      10, // QoS history depth
      std::bind(&DataCollectionSubscriber::topic_callback, this, std::placeholders::_1));
    RCLCPP_INFO(this->get_logger(), "DataCollection node started, subscribing to /system_state_topic");
  }

private:
  void topic_callback(const system_interfaces::msg::SystemState::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "Received SystemState: SystemState='%s'",
                msg->system_state.c_str());
    // You can add more detailed printing of your custom message fields here
  }
  rclcpp::Subscription<system_interfaces::msg::SystemState>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DataCollectionSubscriber>());
  rclcpp::shutdown();
  return 0;
}
