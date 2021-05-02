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
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <vision_msgs/ObjInfo.h>
#include <tf/transform_listener.h>
#include <math.h>
struct Location
{
  float x;
  float y;
  float z;
};
Location cupCam;
Location cupBase;
int sim=0;
void callback(const vision_msgs::ObjInfo::ConstPtr& revmsg)
{
  cupCam.x=revmsg->x/1000;
  cupCam.y=revmsg->y/1000;
  cupCam.z=revmsg->z/1000;
 // ROS_INFO("recv->obj:%f,%f,%f",cupCam.x,cupCam.y,cupCam.z);
}
void transformPoint(const tf::TransformListener& listener)
{
  geometry_msgs::PointStamped camPoint;
  camPoint.header.frame_id="camera_link";
  camPoint.point.x=cupCam.x;
  camPoint.point.y=cupCam.y;
  camPoint.point.z=cupCam.z;
  try
  {
    geometry_msgs::PointStamped basePoint;
    listener.transformPoint("base_link",camPoint,basePoint);
    if(cupCam.x==0||cupCam.y==0||cupCam.z==0)
      ROS_INFO("Please move RIghtCup in another position");
    else
      ROS_INFO("RightCup->cam:%f,%f,%f--->base:%f,%f,%f",camPoint.point.x,camPoint.point.y\
    ,camPoint.point.z,basePoint.point.x,basePoint.point.y,basePoint.point.z);  
     cupBase.x=basePoint.point.x;
     cupBase.y=basePoint.point.y;
     cupBase.z=basePoint.point.z;
     ROS_INFO("Transformed location:%f,%f,%f",cupBase.x,cupBase.y,cupBase.z);
  }
  catch(tf::TransformException& ex)
  {
    ROS_ERROR("Fail to find transformation!");
  }
}
void robot_motion(moveit::planning_interface::MoveGroupInterface& arm)
{
  // start of pick
    geometry_msgs::Pose target_pose;
    double raw=0,pitch=-90,yaw=180;//in degree 0,-90,190
    geometry_msgs::Quaternion q;
    q=tf::createQuaternionMsgFromRollPitchYaw(raw,pitch,yaw);
    target_pose.orientation.x = 0.71;//+
    target_pose.orientation.y = 0.55;//+
    target_pose.orientation.z = -0.41;//-
    target_pose.orientation.w = -0.16;//-
    // target_pose.orientation.x = 1;
    // target_pose.orientation.y = 0;
    // target_pose.orientation.z = 0;
    // target_pose.orientation.w = 0;

    target_pose.position.x = cupBase.x+0.2;
    target_pose.position.y = cupBase.y;
    target_pose.position.z = cupBase.z+0.2;
    ROS_INFO("Picked obj location:%f,%f,%f",cupBase.x,cupBase.y,cupBase.z);
  
    if(cupCam.x!=0&&cupCam.y!=0&&cupBase.z>=0.8)
    {
        
        ROS_INFO("Ready to plan pick.");
        arm.setStartStateToCurrentState();
        arm.setPoseTarget(target_pose);
        moveit::planning_interface::MoveGroupInterface::Plan plan_pick;
        moveit::planning_interface::MoveItErrorCode success = arm.plan(plan_pick);

        ROS_INFO("Plan (pose goal) %s",success?"":"FAILED");   

        if(success)
        {
          arm.execute(plan_pick);
          sleep(1);
          ros::shutdown();
        
        }

    }
    // robot_state::RobotState start_state_lift(*arm.getCurrentState());
    // const robot_state::JointModelGroup *joint_model_group =start_state_lift.getJointModelGroup(arm.getName());  
    // start_state_lift.setFromIK(joint_model_group,target_pose);
    // float GoalZ;
    // GoalZ=cupBase.z+0.2;
    // //directly set waypoints of movel 
    // std::vector<geometry_msgs::Pose> waypoints;
    // waypoints.push_back(target_pose);
    // for(;GoalZ>=cupBase.z;GoalZ-=0.02)
    // {
    //     target_pose.position.z=GoalZ;
    //     waypoints.push_back(target_pose);
    // }
    // moveit_msgs::RobotTrajectory trajectory;
	  // const double jump_threshold = 0.0;
	  // const double eef_step = 0.01;
	  // double fraction = 0.0;
    // int maxtries = 500;   //最大尝试规划次数
    // int attempts = 0;     //已经尝试规划次数
    // while(fraction < 1.0 && attempts < maxtries)
    // {
    //     fraction = arm.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
    //     attempts++;   
    //     if(attempts % 10 == 0)
    //         ROS_INFO("Still trying after %d attempts...", attempts);
    // }
    
    // if(fraction == 1)
    // {   
    //     ROS_INFO("Path computed successfully. Moving the lArm.");

	  //   // 生成机械臂的运dee动规划数据
    //   arm.setStartState(start_state_lift);
    //   arm.setPoseTarget(target_pose);
	  //   moveit::planning_interface::MoveGroupInterface::Plan plan_movel;
	  //   plan_movel.trajectory_ = trajectory;
	  //   // 执行运动
	  //   arm.execute(plan_movel);
    //   ros::shutdown();
    //   sleep(1);

    // }
    // else
    // {
    //     ROS_INFO("Path planning failed with only %0.6f success after %d attempts.", fraction, maxtries);
    // }
        

}

void addCollisionObjects(moveit::planning_interface::PlanningSceneInterface& planning_scene_interface)
{
  // BEGIN_SUB_TUTORIAL table1
  //
  // Creating Environment
  // ^^^^^^^^^^^^^^^^^^^^
  // Create vector to hold 3 collision objects.
  std::vector<moveit_msgs::CollisionObject> collision_objects;
  collision_objects.resize(3);

  // Add the first table where the cube will originally be kept.
  collision_objects[0].id = "table_top";
  collision_objects[0].header.frame_id = "base_link";

  /* Define the primitive and its dimensions. */
  collision_objects[0].primitives.resize(1);
  collision_objects[0].primitives[0].type = collision_objects[0].primitives[0].BOX;
  collision_objects[0].primitives[0].dimensions.resize(3);
  collision_objects[0].primitives[0].dimensions[0] = 1.4;
  collision_objects[0].primitives[0].dimensions[1] = 1.1;
  collision_objects[0].primitives[0].dimensions[2] = 0.001;

  /* Define the pose of the table. */
  collision_objects[0].primitive_poses.resize(1);
  collision_objects[0].primitive_poses[0].position.x = 0;
  collision_objects[0].primitive_poses[0].position.y = 0.7;
  collision_objects[0].primitive_poses[0].position.z = 0.83;
  // END_SUB_TUTORIAL

  collision_objects[0].operation = collision_objects[0].ADD;






  planning_scene_interface.applyCollisionObjects(collision_objects);
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "RarmMotion");
  ros::NodeHandle n; 
    ros::Subscriber sub=n.subscribe("RightObjects",1,callback);
  tf::TransformListener listener(ros::Duration(1));
    ros::Timer timer=n.createTimer(ros::Duration(1),boost::bind(&transformPoint,boost::ref(listener)));
      
      
    while(ros::ok)
      {
        ros::spinOnce();
        ros::AsyncSpinner spinner(1);
        spinner.start();

        moveit::planning_interface::MoveGroupInterface arm("right_manipulator");
        

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
        //add object

        // Define a pose for the box (specified relative to frame_id)
        // Define a collision object ROS message.
        moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
        addCollisionObjects(planning_scene_interface);

        robot_motion(arm);

      }

    return 0;
}

