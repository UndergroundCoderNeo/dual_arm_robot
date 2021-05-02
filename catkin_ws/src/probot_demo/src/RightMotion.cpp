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

void robot_motion(moveit::planning_interface::MoveGroupInterface& rArm)
{
  // start of pick
    geometry_msgs::Pose target_pose;
    target_pose.orientation.x = 0;
    target_pose.orientation.y = 0.737;
    target_pose.orientation.z = 0;
    target_pose.orientation.w = 0.676;

    target_pose.position.x = -0.1;
    target_pose.position.y = -0.3;
    target_pose.position.z = 0.9;

    // 设置机器臂当前的状态作为运动初始状态
    rArm.setStartStateToCurrentState();
    rArm.setPoseTarget(target_pose);

    
    moveit::planning_interface::MoveGroupInterface::Plan plan_pick;
    moveit::planning_interface::MoveItErrorCode success = rArm.plan(plan_pick);

    ROS_INFO("Plan (pose goal) %s",success?"":"FAILED");   

    if(success)
      rArm.execute(plan_pick);
    sleep(5);

   
    

    std::vector<geometry_msgs::Pose> waypoints;
    waypoints.push_back(target_pose);
    for(double GoalZ=0.9;GoalZ<=1.05;GoalZ+=0.01)
    {
        target_pose.position.z=GoalZ;
        waypoints.push_back(target_pose);
    }
    moveit_msgs::RobotTrajectory trajectory;
	  const double jump_threshold = 0.0;
	  const double eef_step = 0.01;
	  double fraction = 0.0;
    int maxtries = 500;   //最大尝试规划次数
    int attempts = 0;     //已经尝试规划次数
    while(fraction < 1.0 && attempts < maxtries)
    {
        fraction = rArm.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
        attempts++;
        
        if(attempts % 10 == 0)
            ROS_INFO("Still trying after %d attempts...", attempts);
    }
    
    if(fraction == 1)
    {   
        ROS_INFO("Path computed successfully. Moving the rArm.");

	    // 生成机械臂的运动规划数据
	    moveit::planning_interface::MoveGroupInterface::Plan plan_lift;
	    plan_lift.trajectory_ = trajectory;
	    // 执行运动
	    rArm.execute(plan_lift);
        sleep(10);

    }
    else
    {
        ROS_INFO("Path planning failed with only %0.6f success after %d attempts.", fraction, maxtries);
    }
      //rotate

          //directly set waypoints
    // std::vector<geometry_msgs::Pose> waypoints_r;

    // target_pose.position.x = 0.1;
    // target_pose.position.y = -0.3;
    // target_pose.position.z = 1.05;
    // waypoints_r.push_back(target_pose);
    // double raw=0,pitch=-2,yaw=0;//in rad
    // geometry_msgs::Quaternion q;
    // for(;pitch>-2.35;pitch-=0.01)
    // {
    //   q=tf::createQuaternionMsgFromRollPitchYaw(raw,pitch,yaw);
    //   target_pose.orientation.x = q.x;
    //   target_pose.orientation.y = q.y;
    //   target_pose.orientation.z = q.z;
    //   target_pose.orientation.w = q.w;
    //   waypoints_r.push_back(target_pose);
    // }
    // moveit_msgs::RobotTrajectory trajectory_r;
    
	//   fraction = 0;
    // attempts = 0;     //已经尝试规划次数
    // while(fraction < 1.0 && attempts < maxtries)
    // {
    //     fraction = rArm.computeCartesianPath(waypoints_r, eef_step, jump_threshold, trajectory_r);
    //     attempts++;
        
    //     if(attempts % 10 == 0)
    //         ROS_INFO("Still trying after %d attempts...", attempts);
    // }
    
    // if(fraction == 1)
    // {   
    //     ROS_INFO("Path computed successfully. Moving the rArm.");

	//     // 生成机械臂的运动规划数据
	//     moveit::planning_interface::MoveGroupInterface::Plan plan_r;
	//     plan_r.trajectory_ = trajectory_r;
    
	//     // 执行运动
	//     rArm.execute(plan_r);
    //     sleep(1);
    // }
    // else
    // {
    //     ROS_INFO("Path planning failed with only %0.6f success after %d attempts.", fraction, maxtries);
    // }





    //start of lift
    // robot_state::RobotState start_state_lift(*rArm.getCurrentState());
    // const robot_state::JointModelGroup *joint_model_group =start_state_lift.getJointModelGroup(rArm.getName());  
    // start_state_lift.setFromIK(joint_model_group,target_pose_pick);
    // //set the initial position of motion of rotating
    // // 设置机器人终端的目标位置
    // geometry_msgs::Pose target_pose_lift;
    // target_pose_lift.orientation.x = 0;
    // target_pose_lift.orientation.y = -0.819;
    // target_pose_lift.orientation.z = 0;
    // target_pose_lift.orientation.w = 0.574;
    // //change the height of the end-effector
    // target_pose_lift.position.x = 0.1;
    // target_pose_lift.position.y = -0.3;
    // target_pose_lift.position.z = 1.5;

    // rArm.setStartState(start_state_lift);
    // rArm.setPoseTarget(target_pose_lift);
    // moveit::planning_interface::MoveGroupInterface::Plan plan_lift;
    // success = rArm.plan(plan_lift);

    // ROS_INFO("Plan (pose goal) %s",success?"":"FAILED");   

    // //让机械臂按照规划的轨迹开始运动。
    // if(success)
    //   rArm.execute(plan_lift);
    // sleep(5);
   //end of lift

    //robot_state::RobotState start_state_rotate(*rArm.getCurrentState()); 
    //start_state_rotate.setFromIK(joint_model_group,target_pose_lift);

    // geometry_msgs::Pose target_pose_rotate;

    // target_pose_rotate.orientation.x = 0;
    // target_pose_rotate.orientation.y = -0.966;
    // target_pose_rotate.orientation.z = 0;
    // target_pose_rotate.orientation.w = 0.259;

    // target_pose_rotate.position.x = 0.1;
    // target_pose_rotate.position.y = -0.3;
    // target_pose_rotate.position.z = 1.2;

    // rArm.setStartStateToCurrentState ();
    // rArm.setPoseTarget(target_pose_rotate);

    // moveit::planning_interface::MoveGroupInterface::Plan plan_rotate;
    // success = rArm.plan(plan_rotate);

    // ROS_INFO("Plan (pose goal) %s",success?"":"FAILED");   

    // if(success)
    //   rArm.execute(plan_rotate);
    // sleep(5);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "RightMotion");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    moveit::planning_interface::MoveGroupInterface rArm("right_manipulator");

    //获取终端link的名称
    std::string end_effector_link = rArm.getEndEffectorLink();

    //设置目标位置所使用的参考坐标系
    std::string reference_frame = "base_link";
    rArm.setPoseReferenceFrame(reference_frame);

    //当运动规划失败后，允许重新规划
    rArm.allowReplanning(true);

    //设置位置(单位：米)和姿态（单位：弧度）的允许误差
    rArm.setGoalPositionTolerance(0.001);
    rArm.setGoalOrientationTolerance(0.01);

    //设置允许的最大速度和加速度
    rArm.setMaxAccelerationScalingFactor(0.2);
    rArm.setMaxVelocityScalingFactor(0.2);

    // 控制机械臂先回到初始化位置
    rArm.setNamedTarget("right_original");
    rArm.move();
    sleep(1);

    robot_motion(rArm);


    // 控制机械臂先回到初始化位置
    rArm.setNamedTarget("right_original");
    rArm.move();
    sleep(5);

    ros::shutdown(); 

    return 0;
}
