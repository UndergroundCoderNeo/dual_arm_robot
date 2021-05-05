# dual_arm_robot
use Ros to build a handeye system using for positing and picking objects
# 操作教程

1.连接树莓派,运行手抓的socket server程序

确认树莓派和上位机处于同一Wi-Fi下

```cmd
ssh pi@192.168.0.10
password:qwaa1234 
cd ~/Documents
python3 TControl.py
```

2.打开接受路点的socket server

```cmd
cd ~/sendWayPoints
python3 MidServer.py
```

3.连接摄像头

启动虚拟环境（tensorflow环境，也可以在base环境下直接安装tensorflow）

tensorflow 版本1.14.0

```cmd
source ~/tensorflow/bin/activate        //optional
roslaunch tensorflow_object_detector vision.launch
```

4.打开rviz

```cmd
roslaunch dual_config demo.launch
```

5.运行左右臂规划程序

```cmd
rosrun probot_demo rLeftMotion
rosrun probot_demo rRightMotion
```

     规划成功后进程会自动结束

6.发送路点信息给双臂机器人

```cmd
cd ~/sendWayPoints
python3 RobotArmControl.py
```
