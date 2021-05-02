# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "wayPoints: 1 messages, 0 services")

set(MSG_I_FLAGS "-IwayPoints:/home/dell/catkin_ws/src/wayPoints/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(wayPoints_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg" NAME_WE)
add_custom_target(_wayPoints_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "wayPoints" "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(wayPoints
  "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wayPoints
)

### Generating Services

### Generating Module File
_generate_module_cpp(wayPoints
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wayPoints
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(wayPoints_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(wayPoints_generate_messages wayPoints_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg" NAME_WE)
add_dependencies(wayPoints_generate_messages_cpp _wayPoints_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(wayPoints_gencpp)
add_dependencies(wayPoints_gencpp wayPoints_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wayPoints_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(wayPoints
  "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/wayPoints
)

### Generating Services

### Generating Module File
_generate_module_eus(wayPoints
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/wayPoints
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(wayPoints_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(wayPoints_generate_messages wayPoints_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg" NAME_WE)
add_dependencies(wayPoints_generate_messages_eus _wayPoints_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(wayPoints_geneus)
add_dependencies(wayPoints_geneus wayPoints_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wayPoints_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(wayPoints
  "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wayPoints
)

### Generating Services

### Generating Module File
_generate_module_lisp(wayPoints
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wayPoints
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(wayPoints_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(wayPoints_generate_messages wayPoints_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg" NAME_WE)
add_dependencies(wayPoints_generate_messages_lisp _wayPoints_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(wayPoints_genlisp)
add_dependencies(wayPoints_genlisp wayPoints_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wayPoints_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(wayPoints
  "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/wayPoints
)

### Generating Services

### Generating Module File
_generate_module_nodejs(wayPoints
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/wayPoints
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(wayPoints_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(wayPoints_generate_messages wayPoints_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg" NAME_WE)
add_dependencies(wayPoints_generate_messages_nodejs _wayPoints_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(wayPoints_gennodejs)
add_dependencies(wayPoints_gennodejs wayPoints_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wayPoints_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(wayPoints
  "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wayPoints
)

### Generating Services

### Generating Module File
_generate_module_py(wayPoints
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wayPoints
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(wayPoints_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(wayPoints_generate_messages wayPoints_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dell/catkin_ws/src/wayPoints/msg/Location.msg" NAME_WE)
add_dependencies(wayPoints_generate_messages_py _wayPoints_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(wayPoints_genpy)
add_dependencies(wayPoints_genpy wayPoints_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wayPoints_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wayPoints)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wayPoints
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(wayPoints_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/wayPoints)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/wayPoints
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(wayPoints_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wayPoints)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wayPoints
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(wayPoints_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/wayPoints)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/wayPoints
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(wayPoints_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wayPoints)
  install(CODE "execute_process(COMMAND \"/home/dell/tensorflow/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wayPoints\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wayPoints
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(wayPoints_generate_messages_py std_msgs_generate_messages_py)
endif()
