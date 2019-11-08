#include <odrive_driver/odrive_driver_component.h>

namespace odrive_driver
{
    ODriveDriverComponent::ODriveDriverComponent(const rclcpp::NodeOptions & options)
    : Node("odrive_driver", options)
    {
        declare_parameter("odrive_serial_number","");
        get_parameter("odrive_serial_number",odrive_serial_number_);
        declare_parameter("num_motor",2);
        get_parameter("num_motor",num_motor_);
        if(num_motor_ == 1)
        {
            std::string odrive_serial_numbers[1] = {odrive_serial_number_};
            std::string odrive_serial_numbers_map[1] = {odrive_serial_number_};
            
            int16_t zeroeth_radian_in_encoder_ticks_0 = 0;
            declare_parameter("zeroeth_radian_in_encoder_ticks/0",0);
            get_parameter("zeroeth_radian_in_encoder_ticks/0",zeroeth_radian_in_encoder_ticks_0);
            int16_t zeroeth_radian_in_encoder_ticks[1] = {zeroeth_radian_in_encoder_ticks_0};
            bool odrive_position_per_motor_0;
            declare_parameter("odrive_position_per_motor/0",false);
            get_parameter("odrive_position_per_motor/0",odrive_position_per_motor_0);
            bool odrive_position_per_motor[1] = {odrive_position_per_motor_0};
            float odrive_encoder_ticks_per_radian_per_motor_0;
            declare_parameter("odrive_encoder_ticks_per_radian_per_motor/0",57.2958*(2048*4)/360.0);
            get_parameter("odrive_encoder_ticks_per_radian_per_motor/0",odrive_encoder_ticks_per_radian_per_motor_0);
            float odrive_encoder_ticks_per_radian_per_motor[1] = {odrive_encoder_ticks_per_radian_per_motor_0};

            odrive::CppSdk odrive_cpp_sdk(
                odrive_serial_numbers,
                1,
                odrive_serial_numbers_map,
                odrive_position_per_motor,
                odrive_encoder_ticks_per_radian_per_motor,
                2
            );
            sdk_ptr_ = std::make_shared<odrive::CppSdk>(odrive_cpp_sdk);
            sdk_ptr_->setZeroethRadianInEncoderTicks(zeroeth_radian_in_encoder_ticks);
        }
        else if(num_motor_ == 2)
        {
            std::string odrive_serial_numbers[1] = {odrive_serial_number_};
            std::string odrive_serial_numbers_map[1] = {odrive_serial_number_};

            int16_t zeroeth_radian_in_encoder_ticks_0 = 0;
            declare_parameter("zeroeth_radian_in_encoder_ticks/0",0);
            get_parameter("zeroeth_radian_in_encoder_ticks/0",zeroeth_radian_in_encoder_ticks_0);
            int16_t zeroeth_radian_in_encoder_ticks_1 = 1;
            declare_parameter("zeroeth_radian_in_encoder_ticks/1",1);
            get_parameter("zeroeth_radian_in_encoder_ticks/1",zeroeth_radian_in_encoder_ticks_1);
            int16_t zeroeth_radian_in_encoder_ticks[2] = {zeroeth_radian_in_encoder_ticks_0,zeroeth_radian_in_encoder_ticks_1};
            bool odrive_position_per_motor_0;
            declare_parameter("odrive_position_per_motor/0",false);
            get_parameter("odrive_position_per_motor/0",odrive_position_per_motor_0);
            bool odrive_position_per_motor_1;
            declare_parameter("odrive_position_per_motor/1",false);
            get_parameter("odrive_position_per_motor/1",odrive_position_per_motor_1);
            bool odrive_position_per_motor[2] = {odrive_position_per_motor_0,odrive_position_per_motor_1};
            float odrive_encoder_ticks_per_radian_per_motor_0;
            declare_parameter("odrive_encoder_ticks_per_radian_per_motor/0",57.2958*(2048*4)/360.0);
            get_parameter("odrive_encoder_ticks_per_radian_per_motor/0",odrive_encoder_ticks_per_radian_per_motor_0);
            float odrive_encoder_ticks_per_radian_per_motor_1;
            declare_parameter("odrive_encoder_ticks_per_radian_per_motor/1",57.2958*(2048*4)/360.0);
            get_parameter("odrive_encoder_ticks_per_radian_per_motor/1",odrive_encoder_ticks_per_radian_per_motor_1);
            float odrive_encoder_ticks_per_radian_per_motor[2] = {odrive_encoder_ticks_per_radian_per_motor_0,odrive_encoder_ticks_per_radian_per_motor_1};

            odrive::CppSdk odrive_cpp_sdk(
                odrive_serial_numbers,
                1,
                odrive_serial_numbers_map,
                odrive_position_per_motor,
                odrive_encoder_ticks_per_radian_per_motor,
                2
            );
            sdk_ptr_ = std::make_shared<odrive::CppSdk>(odrive_cpp_sdk);
            sdk_ptr_->setZeroethRadianInEncoderTicks(zeroeth_radian_in_encoder_ticks);
        }
        bool result = sdk_ptr_->init();
        if(!result)
        {
            RCLCPP_ERROR(get_logger(), "failed to connect odrive");
        }
        else
        {
            RCLCPP_DEBUG(get_logger(), "initialized odrive");
        }
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(odrive_driver::ODriveDriverComponent)