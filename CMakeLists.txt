cmake_minimum_required(VERSION 3.5)
project(odrive_driver)

add_definitions(-fPIC)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
  include
)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

add_library(odrive_cpp_sdk src/odrive_cpp_sdk.cpp)

add_library(odrive_driver_component SHARED src/odrive_driver_component.cpp)
target_link_libraries(odrive_driver_component odrive_cpp_sdk)
ament_target_dependencies(odrive_driver_component rclcpp rclcpp_components)

ament_export_libraries(odrive_driver_component)

rclcpp_components_register_nodes(odrive_driver_component
  "odrive_driver::ODriveDriverComponent")

add_executable(odrive_driver_node src/odrive_driver_node.cpp)
target_link_libraries(odrive_driver_node odrive_driver_component)
ament_target_dependencies(odrive_driver_node rclcpp rclcpp_components std_msgs)

install(
  DIRECTORY "include/"
  DESTINATION include
)

install(TARGETS
  odrive_driver_node
  DESTINATION lib/odrive_driver
)

install(TARGETS
  odrive_cpp_sdk
  odrive_driver_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
