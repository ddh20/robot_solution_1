# Base image: ROS 2 Humble Desktop Full
FROM osrf/ros:humble-desktop

# Install necessary development tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    clang-format \
    cmake \
    git \
    wget \
    libssl-dev \
    libpython3-dev \
    && rm -rf /var/lib/apt/lists/*

# Create a workspace
ENV ROS_WS=/ros2_ws
RUN mkdir -p $ROS_WS/src
WORKDIR $ROS_WS

# Source ROS 2 environment
RUN echo "source /opt/ros/humble/setup.bash" >> /root/.bashrc

# Entry point
CMD ["/bin/bash"]
