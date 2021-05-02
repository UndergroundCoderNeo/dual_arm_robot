#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <trajectory_msgs/JointTrajectory.h>
//header for socket

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include<wayPoints/Location.h>
#define PI 3.1415
#define PORT 7000
#define BUFFER_SIZE 1024
char sendbuf[BUFFER_SIZE];
char recvbuf[BUFFER_SIZE];
char tmp_cmd[BUFFER_SIZE];
int sock_cli = socket(AF_INET, SOCK_STREAM, 0);
using namespace std;
struct Pose 
{
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
};
//socket client ,action server
class JointTrajectoryActionServer
{
public:
JointTrajectoryActionServer(std::string name):
		as_(nh_, name, false), action_name_(name)
{
	// register callback for goal
	as_.registerGoalCallback(boost::bind(&JointTrajectoryActionServer::goalCallback, this));
	as_.start();
}
~JointTrajectoryActionServer(void){}


// when a trajectory command comes, this function will be called.
void goalCallback()
{
	boost::shared_ptr<const control_msgs::FollowJointTrajectoryGoal> goal;
	goal=as_.acceptNewGoal();
	int point_size=goal->trajectory.points.size();
	cout<<"trajectory point size:"<< goal->trajectory.points.size()<<endl;
	int num=0;
	int joint_num=0;
	float wayPoints;
	int counter=0;
	//store wayPoints
	float PointStor[goal->trajectory.points.size()][7];

	for(;num<goal->trajectory.points.size();num++)
	{
		if(num==0)
		{
			strcpy(sendbuf,"/RP/");
			send(sock_cli,sendbuf,sizeof(sendbuf),0);
			cout<<sendbuf<<endl;
		}
		float GoalDeg[7]={ goal->trajectory.points[num].positions[0]*(180/PI),
 							goal->trajectory.points[num].positions[1]*(180/PI),
 							goal->trajectory.points[num].positions[2]*(180/PI),
 							goal->trajectory.points[num].positions[3]*(180/PI),
       	    				goal->trajectory.points[num].positions[4]*(180/PI),
            				goal->trajectory.points[num].positions[5]*(180/PI),
							goal->trajectory.points[num].positions[6]*(180/PI)};

		cout<<"point_number"<<num+1<< ":[" << (GoalDeg[0]) 
             << "," << (GoalDeg[0])   
             << "," << (GoalDeg[1])  
             << "," << (GoalDeg[2])   
             << "," << (GoalDeg[3])   
             << "," << (GoalDeg[4])
	     	 << "," << (GoalDeg[5])
			 << "," << (GoalDeg[6])    
             << "]" << std::endl ;

		int i;
		for(i=0;i<7;i++)
		{
			PointStor[num][i]=GoalDeg[i];
		}
		//debug information
	     sprintf(sendbuf,"movej([%f,%f,%f,%f,%f,%f,%f],30,2000,-1);",
			GoalDeg[0],
 			GoalDeg[1],
 			GoalDeg[2],
 			GoalDeg[3],
       	    GoalDeg[4],
            GoalDeg[5],
			GoalDeg[6]);
			//send the cmd to the robot
		send(sock_cli,sendbuf,sizeof(sendbuf),0);
		cout<<sendbuf<<endl;
	
	}
	//lift object assume end effector's location is x,y,z
	Pose rightCup;
	sprintf(sendbuf,"movel([%f,%f,%f,%f,%f,%f],30,2000,-1);movep([%f,%f,%f,%f,%f+90,%f],30,2000,-1);\
					 movep([%f,%f,%f,%f,%f,%f],30,2000,-1);",rightCup.x,rightCup.y,rightCup.z,rightCup.rx\
					 ,rightCup.ry,rightCup.rz,rightCup.x,rightCup.y,rightCup.z,rightCup.rx\
					 ,rightCup.ry,rightCup.rz,rightCup.x,rightCup.y,rightCup.z,rightCup.rx\
					 ,rightCup.ry,rightCup.rz);
	send(sock_cli,sendbuf,sizeof(sendbuf),0);	
	// tell motion control hardware to execute
    // do something
	// when finished, return result
	as_.setSucceeded(result_);
}
protected:
ros::NodeHandle nh_;
actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> as_;
actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction>::Result result_;
std::string action_name_;
};

void init_socket()
{
	//定义 sockfd

    //定义sockaddr_in
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);  //服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //use local addr to test
    if(connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
}

void obj_callback(const wayPoints::Location::ConstPtr &msg)
{
	float obj_x,obj_y,obj_z;
	string obj_name;
	obj_name=msg->name;
	obj_x=msg->x;
	obj_y=msg->y;
	obj_z=msg->z;

}

int main(int argc, char** argv)
{
	ros::init(argc,argv, "Rserver");
	ros::NodeHandle n;
	ros::Subscriber sub=n.subscribe("object_information",1000,obj_callback);
	init_socket();
	//JointTrajectoryActionServer srv("left_manipulator_controller/follow_joint_trajectory");
	JointTrajectoryActionServer srv("right_manipulator_controller/follow_joint_trajectory");
	ros::spin();
	return 0;
}
