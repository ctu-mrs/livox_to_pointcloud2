cmake_minimum_required(VERSION 3.5)
project(livox_to_pointcloud2)

# Default to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific options
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  livox_ros_driver2
)

# Declare a catkin package
catkin_package(
  CATKIN_DEPENDS roscpp sensor_msgs std_msgs livox_ros_driver2
)

# Include directories
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# Declare a C++ executable
add_executable(livox_to_pointcloud2_node src/livox_to_pointcloud2_node.cpp src/livox_to_pointcloud2.cpp)

# Specify libraries to link a library or executable target against
target_link_libraries(livox_to_pointcloud2_node
  ${catkin_LIBRARIES}
)

# Install the executable
install(TARGETS livox_to_pointcloud2_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Install other directories
install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
