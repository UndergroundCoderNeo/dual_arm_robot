#include <string>
#include <ros/ros.h>
#include <vision_msgs/ObjInfo.h>
#include <tf/transform_listener.h>
#include <math.h>
struct Location
{
  float x;
  float y;
  float z;
};
Location lcupCam,rcupCam;
Location lcupBase,rcupBase;
int sim=0;
void Lcallback(const vision_msgs::ObjInfo::ConstPtr& revmsg)
{
  lcupCam.x=revmsg->x/1000;
  lcupCam.y=revmsg->y/1000;
  lcupCam.z=revmsg->z/1000;
}
void Rcallback(const vision_msgs::ObjInfo::ConstPtr& revmsg)
{
  rcupCam.x=revmsg->x/1000;
  rcupCam.y=revmsg->y/1000;
  rcupCam.z=revmsg->z/1000 ;
}
void transformPoint(const tf::TransformListener& listener)
{
  geometry_msgs::PointStamped lcamPoint;
  lcamPoint.header.frame_id="camera_link";
  lcamPoint.point.x=lcupCam.x;
  lcamPoint.point.y=lcupCam.y;
  lcamPoint.point.z=lcupCam.z;

  geometry_msgs::PointStamped rcamPoint;
  rcamPoint.header.frame_id="camera_link";
  rcamPoint.point.x=rcupCam.x;
  rcamPoint.point.y=rcupCam.y;
  rcamPoint.point.z=rcupCam.z;
  try
  {
    geometry_msgs::PointStamped lbasePoint;
    listener.transformPoint("base_link",lcamPoint,lbasePoint);
    geometry_msgs::PointStamped rbasePoint;
    listener.transformPoint("base_link",rcamPoint,rbasePoint);

      ROS_INFO("LeftCup->cam:%f,%f,%f--->base:%f,%f,%f",lcamPoint.point.x
      ,lcamPoint.point.y\
      ,lcamPoint.point.z\
      ,lbasePoint.point.x\
      ,lbasePoint.point.y\
      ,lbasePoint.point.z);  
     lcupBase.x=lbasePoint.point.x;
     lcupBase.y=lbasePoint.point.y;
     lcupBase.z=lbasePoint.point.z;
      ROS_INFO("RightCup->cam:%f,%f,%f--->base:%f,%f,%f",rcamPoint.point.x
      ,rcamPoint.point.y\
      ,rcamPoint.point.z\
      ,rbasePoint.point.x\
      ,rbasePoint.point.y\
      ,rbasePoint.point.z);  
     rcupBase.x=rbasePoint.point.x;
     rcupBase.y=rbasePoint.point.y;
     rcupBase.z=rbasePoint.point.z;
    // ROS_INFO("Transformed location:%f,%f,%f",cupBase.x,cupBase.y,cupBase.z);
  }
  catch(tf::TransformException& ex)
  {
    ROS_ERROR("Fail to find transformation!");
  }
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "ObjPosNode"); 
    ros::NodeHandle n; 
    ros::Publisher rObjPosPub=n.advertise<vision_msgs::ObjInfo>("RightObjBase",10);
    ros::Publisher lObjPosPub=n.advertise<vision_msgs::ObjInfo>("LeftObjBase",10);
    ros::Rate loop_rate=10;
    ros::Subscriber lsub=n.subscribe("LeftObjects",10,Lcallback);
    ros::Subscriber rsub=n.subscribe("RightObjects",10,Rcallback);
    tf::TransformListener listener(ros::Duration(1));
    ros::Timer timer=n.createTimer(ros::Duration(1),boost::bind(&transformPoint,boost::ref(listener)));
    while(ros::ok())
    {
      
        vision_msgs::ObjInfo lobjbase;
        lobjbase.x=lcupBase.x;
        lobjbase.y=lcupBase.y;
        lobjbase.z=lcupBase.z;
      if(lobjbase.z>0.8)
      {
        lObjPosPub.publish(lobjbase);
      }
      
      vision_msgs::ObjInfo robjbase;
      robjbase.x=rcupBase.x;
      robjbase.y=rcupBase.y;
      robjbase.z=rcupBase.z;
      if(robjbase.z>0.8)
      {
        rObjPosPub.publish(robjbase);
      }
      ros::spinOnce();
      loop_rate.sleep();
    }
}