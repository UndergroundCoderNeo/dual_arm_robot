/***********************************************************************
Copyright 2019 Wuhan PS-Micro Technology Co., Itd.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************/

#include <string>
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>

void robot_motion(moveit::planning_interface::MoveGroupInterface& arm)
{
  // start of pick
    geometry_msgs::Pose target_pose_pick;
    target_pose_pick.orientation.x = 0;
    target_pose_pick.orientation.y = -0.819;
    target_pose_pick.orientation.z = 0;
    target_pose_pick.orientation.w = 0.574;

    target_pose_pick.position.x = 0.1;
    target_pose_pick.position.y = -0.3;
    target_pose_pick.position.z = 0.9;

    // 设置机器臂当前的状态作为运动初始状态
    arm.setStartStateToCurrentState();
    arm.setPoseTarget(target_pose_pick);

    // 进行运动规划，计算机器人移动到目标的运动轨迹，此时只是计算出轨迹，并不会控制机械臂运动
    moveit::planning_interface::MoveGroupInterface::Plan plan_pick;
    moveit::planning_interface::MoveItErrorCode success = arm.plan(plan_pick);

    ROS_INFO("Plan (pose goal) %s",success?"":"FAILED");   

    //让机械臂按照规划的轨迹开始运动。
    if(success)
      arm.execute(plan_pick);
    sleep(5);

    //end of pick
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "moveit_fk_demo");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    moveit::planning_interface::MoveGroupInterface arm("left_manipulator");

    //获取终端link的名称
    std::string end_effector_link = arm.getEndEffectorLink();

    //设置目标位置所使用的参考坐标系
    std::string reference_frame = "base_link";
    arm.setPoseReferenceFrame(reference_frame);

    //当运动规划失败后，允许重新规划
    arm.allowReplanning(true);

    //设置位置(单位：米)和姿态（单位：弧度）的允许误差
    arm.setGoalPositionTolerance(0.001);
    arm.setGoalOrientationTolerance(0.01);

    //设置允许的最大速度和加速度
    arm.setMaxAccelerationScalingFactor(0.2);
    arm.setMaxVelocityScalingFactor(0.2);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("left_original");
    arm.move();
    sleep(1);

    robot_motion(arm);


    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("left_original");
    arm.move();
    sleep(5);

    ros::shutdown(); 

    return 0;
}
