cmake_minimum_required(VERSION 2.8.3)
project(CamToBaseTrans)

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

add_executable(CamToBase src/CamToBase.cpp)
target_link_libraries(CamToBase ${catkin_LIBRARIES})

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


