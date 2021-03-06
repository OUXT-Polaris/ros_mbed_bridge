cmake_minimum_required(VERSION 2.8.3)
project(ros_mbed_bridge)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  message_runtime
  roscpp
  std_msgs
)

add_message_files(
  FILES
  KeyValue.msg
  Cmd.msg
  Ack.msg
  HeartBeat.msg
  HeartBeatStatus.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(udp_client src/udp_client.cpp)

add_library(udp_server src/udp_server.cpp)

add_executable(ros_mbed_bridge_node src/ros_mbed_bridge_node.cpp src/ros_mbed_bridge.cpp)
target_link_libraries(ros_mbed_bridge_node ${catkin_LIBRARIES} udp_server udp_client)
add_dependencies(ros_mbed_bridge_node ros_mbed_bridge_generate_messages_cpp)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

foreach(dir launch msg)
  install(DIRECTORY ${dir}/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)

install(TARGETS udp_client udp_server
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)