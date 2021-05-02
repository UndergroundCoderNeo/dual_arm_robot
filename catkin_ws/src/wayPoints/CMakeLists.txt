cmake_minimum_required(VERSION 3.0.2)
project(wayPoints)


find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  message_generation 
  vision_msgs
  moveit_msgs
  moveit_ros_perception
  moveit_ros_planning_interface
)





add_message_files(
  FILES
  Location.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp  actionlib_msgs actionlib message_runtime
)
include_directories(

  ${catkin_INCLUDE_DIRS}
)


add_executable(Lserver src/Lserver.cpp)
target_link_libraries(Lserver ${catkin_LIBRARIES})
add_executable(Rserver src/Rserver.cpp)
target_link_libraries(Rserver ${catkin_LIBRARIES})
add_executable(Llistener src/Llistener.cpp)
target_link_libraries(Llistener ${catkin_LIBRARIES})


