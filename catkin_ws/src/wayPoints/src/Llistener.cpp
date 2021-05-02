#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
int counter=0;

void jointstatesCallback(const sensor_msgs::JointStateConstPtr& msg)
{
  float pos[14],last_pos[14];
  int i,j;
  for(i=0;i<14;i++)
  {
      pos[i]=msg->position[i];
      last_pos[i]=pos[i];
      ROS_INFO("Right_arm:[%f],[%f],[%f],[%f],[%f],[%f],[%f]",pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6]);
      ROS_INFO("Left_arm:[%f],[%f],[%f],[%f],[%f],[%f],[%f]",pos[7],pos[8],pos[9],pos[10],pos[11],pos[12],pos[13]);
     
  }
  
}
 
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "listener");
 
 
  ros::NodeHandle n;
 
 
  ros::Subscriber sub = n.subscribe("/joint_states", 1000, jointstatesCallback);
 
 
  ros::spin();
 
 
  return 0;
}
