// Headers in this package
#include <odrive_driver/odrive_driver_component.h>

// Headers in RCLCPP
#include <rclcpp/rclcpp.hpp>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto component = std::make_shared<odrive_driver::ODriveDriverComponent>(options);
    rclcpp::spin(component);
    rclcpp::shutdown();
    return 0;
}