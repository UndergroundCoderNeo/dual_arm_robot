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
#define PI 3.1415
#define PORT 7000
#define BUFFER_SIZE 1024
char sendbuf[BUFFER_SIZE];
char recvbuf[BUFFER_SIZE];
char tmp_cmd[BUFFER_SIZE];
int sock_cli = socket(AF_INET, SOCK_STREAM, 0);
using namespace std;
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
	cout<<"trajectory point size:"<< goal->trajectory.points.size()<<endl;
	int num=0;
	int joint_num=0;
	
	for(;num<goal->trajectory.points.size();num++)
	{
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

	
		//debug information
	     sprintf(sendbuf,"<start> LP/ wayPoints=Array(7,FLO,[%f,%f,%f,%f,%f,%f,%f]);movej(wayPoints,1,1);<end>;",
			GoalDeg[0],
 			GoalDeg[1],
 			GoalDeg[2],
 			GoalDeg[3],
       	    GoalDeg[4],
            GoalDeg[5],
			GoalDeg[6]);
		
		cout<<sendbuf<<endl;
		//send the cmd to the robot
		send(sock_cli,sendbuf,sizeof(sendbuf),0);
					
	}
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

int main(int argc, char** argv)
{
	ros::init(argc,argv, "server");

	init_socket();
	JointTrajectoryActionServer srv("left_manipulator_controller/follow_joint_trajectory");
	//JointTrajectoryActionServer right_srv("right_manipulator_controller/follow_joint_trajector");
	ros::spin();
	return 0;
}
