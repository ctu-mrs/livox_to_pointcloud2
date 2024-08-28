
#ifndef LIVOX_TO_POINTCLOUD2_HPP
#define LIVOX_TO_POINTCLOUD2_HPP

#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include "livox_ros_driver2/CustomMsg.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/PointField.h"

class LivoxToPointCloud2
{
public:
    LivoxToPointCloud2();
    void callback(const livox_ros_driver2::CustomMsg::ConstPtr& msg);

private:
    ros::NodeHandle nh_;  // Node handle to manage the communication with ROS
    ros::Publisher publisher_;
    ros::Subscriber subscriber_;
};

#endif  // LIVOX_TO_POINTCLOUD2_HPP

