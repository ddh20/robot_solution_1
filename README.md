# robot_solution_1
Sandbox for creating a simple robot solution.

# Getting Started
Repository: https://github.com/ddh20/robot_solution_1 <br>
Building the Docker Container: `docker build --no-cache --platform linux/amd64 -t ros2-dev .`

# System State Machine POC
To build and run this demo follow these steps
* Open the folder workspace in vscode
* Open in container
* `colcon build --packages-select system_interfaces`
* `source install/setup.bash`
* `colcon build`
* In terminal 1:<br>
  `source install/setup.bash`<br>
  `ros2 run data_collection_package data_collection_node`
* In terminal 2:<br>
  `source install/setup.bash`<br>
  `ros2 run system_state_machine_package system_state_machine_node`