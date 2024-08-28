#include "ros/ros.h"
#include "livox_to_pointcloud2.hpp"

int main(int argc, char **argv)
{
    // Initialize the ROS system
    ros::init(argc, argv, "livox_to_pointcloud2_node");

    // Create an instance of your node's main class
    LivoxToPointCloud2 livox_to_pointcloud2;

    // Handle ROS communication events
    ros::spin();

    return 0;
}
