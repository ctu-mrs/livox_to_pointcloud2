#include "ros/ros.h"
#include "livox_to_pointcloud2.hpp"
#include "sensor_msgs/PointCloud2.h"
#include "livox_ros_driver2/CustomMsg.h"
#include "sensor_msgs/PointField.h"

LivoxToPointCloud2::LivoxToPointCloud2()
{
    ros::NodeHandle nh;
    publisher_ = nh.advertise<sensor_msgs::PointCloud2>("converted_pointcloud2", 10);
    subscriber_ = nh.subscribe("livox_pointcloud", 10, &LivoxToPointCloud2::callback, this);
}

void LivoxToPointCloud2::callback(const livox_ros_driver2::CustomMsg::ConstPtr& msg)
{
    sensor_msgs::PointCloud2 output;
    output.header = msg->header;
    output.fields.resize(6);

    output.fields[0].name = "x";
    output.fields[0].offset = 0;
    output.fields[0].datatype = sensor_msgs::PointField::FLOAT32;
    output.fields[0].count = 1;

    output.fields[1].name = "y";
    output.fields[1].offset = 4;
    output.fields[1].datatype = sensor_msgs::PointField::FLOAT32;
    output.fields[1].count = 1;

    output.fields[2].name = "z";
    output.fields[2].offset = 8;
    output.fields[2].datatype = sensor_msgs::PointField::FLOAT32;
    output.fields[2].count = 1;

    output.fields[3].name = "intensity";
    output.fields[3].offset = 12;
    output.fields[3].datatype = sensor_msgs::PointField::FLOAT32;
    output.fields[3].count = 1;

    output.fields[4].name = "tag";
    output.fields[4].offset = 16;
    output.fields[4].datatype = sensor_msgs::PointField::UINT8;
    output.fields[4].count = 1;

    output.fields[5].name = "line";
    output.fields[5].offset = 17;
    output.fields[5].datatype = sensor_msgs::PointField::UINT8;
    output.fields[5].count = 1;

    output.point_step = 18;
    output.row_step = output.point_step * msg->point_num;
    output.data.resize(output.row_step);

    uint8_t* raw_data_ptr = &output.data[0];
    for (const auto& point : msg->points)
    {
        *(reinterpret_cast<float*>(raw_data_ptr + 0)) = point.x;
        *(reinterpret_cast<float*>(raw_data_ptr + 4)) = point.y;
        *(reinterpret_cast<float*>(raw_data_ptr + 8)) = point.z;
        *(reinterpret_cast<float*>(raw_data_ptr + 12)) = point.reflectivity;
        *(raw_data_ptr + 16) = point.tag;
        *(raw_data_ptr + 17) = point.line;

        raw_data_ptr += output.point_step;
    }

    output.width = msg->point_num;
    output.height = 1;
    output.is_bigendian = false;
    output.is_dense = true;

    publisher_.publish(output);
}
