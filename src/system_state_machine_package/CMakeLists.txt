cmake_minimum_required(VERSION 3.8)
project(system_state_machine_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(system_interfaces REQUIRED)

add_executable(system_state_machine_node
  src/states/initializing_state.cpp
  src/states/running_state.cpp  

  src/state_machine/context.cpp

  src/system_state_machine_node.cpp
)

target_include_directories(system_state_machine_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/system_state_machine_package>
  $<INSTALL_INTERFACE:include>)
target_compile_features(system_state_machine_node
  PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  system_state_machine_node
  "rclcpp"
  "system_interfaces"
)

install(TARGETS system_state_machine_node
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
