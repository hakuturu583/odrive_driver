#ifndef ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_H_INCLUDED
#define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_H_INCLUDED

#if __cplusplus
extern "C" {
#endif

// The below macros are taken from https://gcc.gnu.org/wiki/Visibility and from
// demos/composition/include/composition/visibility_control.h at https://github.com/ros2/demos
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_EXPORT __attribute__ ((dllexport))
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_IMPORT __attribute__ ((dllimport))
  #else
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_EXPORT __declspec(dllexport)
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_IMPORT __declspec(dllimport)
  #endif
  #ifdef ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_BUILDING_DLL
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_EXPORT
  #else
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_IMPORT
  #endif
  #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC_TYPE ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC
  #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_LOCAL
#else
  #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_EXPORT __attribute__ ((visibility("default")))
  #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_IMPORT
  #if __GNUC__ >= 4
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC __attribute__ ((visibility("default")))
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC
    #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_LOCAL
  #endif
  #define ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC_TYPE
#endif

#if __cplusplus
} // extern "C"
#endif

// Headers in ros2
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>

// Headers in this package
#include <odrive_driver/odrive_cpp_sdk.h>

namespace odrive_driver
{
  class ODriveDriverComponent: public rclcpp::Node
  {
  public:
    ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_PUBLIC
    explicit ODriveDriverComponent(const rclcpp::NodeOptions & options);
  private:
    std::shared_ptr<odrive::CppSdk> sdk_ptr_;
    std::string odrive_serial_number_;
    int num_motor_;
  };
}

#endif  //ODRIVE_DRIVER_ODRIVE_DRIVER_COMPONENT_H_INCLUDED