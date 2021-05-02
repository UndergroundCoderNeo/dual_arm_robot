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
#include <vision_msgs/ObjInfo.h>
#include <tf/transform_listener.h>
#define PI 3.1415
#define PORT 7000
#define BUFFER_SIZE 1024
char sendbuf[55];
char endbuf[150];
char recvbuf[BUFFER_SIZE];
char tmp_cmd[BUFFER_SIZE];
int sock_cli = socket(AF_INET, SOCK_STREAM, 0);
using namespace std;
struct Location
{
  float x;
  float y;
  float z;
};
Location cupCam;
Location cupBase;
struct Pose 
{
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
};
Pose leftCup;
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
	int wayPointsNum=0;

	
	float PointStor[goal->trajectory.points.size()][7];
	//approach object
	wayPointsNum=goal->trajectory.points.size();
	for(;num<goal->trajectory.points.size()-1;num=num+5)
	{
		if(num==0)
		{
			strcpy(sendbuf,"<start>LP/ ");
			send(sock_cli,sendbuf,sizeof(sendbuf),0);
			cout<<sendbuf<<endl;
		}
		float GoalDeg[7]={ -goal->trajectory.points[num].positions[0]*(180/PI),
 							-goal->trajectory.points[num].positions[1]*(180/PI),
 							-goal->trajectory.points[num].positions[2]*(180/PI),
 							goal->trajectory.points[num].positions[3]*(180/PI)-90,
       	    				goal->trajectory.points[num].positions[4]*(180/PI),
            				-goal->trajectory.points[num].positions[5]*(180/PI),
							goal->trajectory.points[num].positions[6]*(180/PI)};

		// cout<<"point_number"<<num+1<< ":[" << (GoalDeg[0]) 
        //      << "," << (GoalDeg[0])   
        //      << "," << (GoalDeg[1])  
        //      << "," << (GoalDeg[2])   
        //      << "," << (GoalDeg[3])   
        //      << "," << (GoalDeg[4])
	    //  	 << "," << (GoalDeg[5])
		// 	 << "," << (GoalDeg[6])    
        //      << "]" << endl ;
		

		int i;
		for(i=0;i<7;i++)
		{
			PointStor[num][i]=GoalDeg[i];
		}
		//debug information
	     sprintf(sendbuf,"movej([%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f],30,2000,-1); ",
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
	float endGoal[7]={-goal->trajectory.points[point_size-1].positions[0]*(180/PI),
 							-goal->trajectory.points[point_size-1].positions[1]*(180/PI),
 							-goal->trajectory.points[point_size-1].positions[2]*(180/PI),
 							goal->trajectory.points[point_size-1].positions[3]*(180/PI)-90,
       	    				goal->trajectory.points[point_size-1].positions[4]*(180/PI),
            				-goal->trajectory.points[point_size-1].positions[5]*(180/PI),
							goal->trajectory.points[point_size-1].positions[6]*(180/PI)};

	
	// if (wayPointsNum%2==0)
	// {
		
	// }
	     sprintf(endbuf,"movej([%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f],30,2000,-1);movej_pose([%.0f,%.0f,%.0f,78,51,90],40,20,-1);movej_pose([%.0f,%.0f,%.0f,78,51,90],40,20,-1);",
			endGoal[0],
 			endGoal[1],
 			endGoal[2],
 			endGoal[3],
       	   	endGoal[4],
            endGoal[5],
			endGoal[6],
			cupBase.x*1000-400,
			cupBase.y*1000-20,
			cupBase.z*1000+250,
			cupBase.x*1000-260,
			cupBase.y*1000-20,
			cupBase.z*1000+10);
		//send the cmd to the robot
		send(sock_cli,endbuf,sizeof(endbuf),0);
		cout<<endbuf<<endl;
		
	//lift object assume end effector's location is x,y,z
	// Pose leftCup;
	// sprintf(sendbuf,"movel([%.1f,%.1f,%.1f,%.1f,%.1f,%.1f],30,2000,-1);",
	//                         goal->trajectory.points[wayPointsNum-1].positions[0]*(180/PI),
 	// 						goal->trajectory.points[wayPointsNum-1].positions[1]*(180/PI),
 	// 						goal->trajectory.points[wayPointsNum-1].positions[2]*(180/PI),
 	// 						goal->trajectory.points[wayPointsNum-1].positions[3]*(180/PI),
    //    	    				goal->trajectory.points[wayPointsNum-1].positions[4]*(180/PI),
    //         				goal->trajectory.points[wayPointsNum-1].positions[5]*(180/PI),
	// 						goal->trajectory.points[wayPointsNum-1].positions[6]*(180/PI));
	// send(sock_cli,sendbuf,sizeof(sendbuf),0);
	/**sprintf(sendbuf,"movel([%f,%f,%f,%f,%f,%f],30,2000,-1);movep([%f,%f,%f,%f,%f+90,%f],30,2000,-1);\
					 movep([%f,%f,%f,%f,%f,%f],30,2000,-1);",leftCup.x,leftCup.y,leftCup.z,leftCup.rx\
					 ,leftCup.ry,leftCup.rz,leftCup.x,leftCup.y,leftCup.z,leftCup.rx\
					 ,leftCup.ry,leftCup.rz,leftCup.x,leftCup.y,leftCup.z,leftCup.rx\
					 ,leftCup.ry,leftCup.rz);
	send(sock_cli,sendbuf,sizeof(sendbuf),0);**/		
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
//get cup location in base

void callback(const vision_msgs::ObjInfo::ConstPtr& revmsg)
{
  cupBase.x=revmsg->x;
  cupBase.y=revmsg->y;
  cupBase.z=revmsg->z;
}

int main(int argc, char** argv)
{
	ros::init(argc,argv, "Lserver");

	init_socket();
	ros::NodeHandle n;
	JointTrajectoryActionServer srv("left_manipulator_controller/follow_joint_trajectory");
	ros::Subscriber sub=n.subscribe("LeftObjBase",10,callback);
	//JointTrajectoryActionServer right_srv("right_manipulator_controller/follow_joint_trajector");
	ros::spin();
	return 0;
}
