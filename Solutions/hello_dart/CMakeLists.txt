cmake_minimum_required(VERSION 3.5.1)

project(tutorial_hello_dart)

set(required_components utils-urdf gui-osg)
set(required_libraries dart dart-utils-urdf dart-gui-osg)

find_package(DART 6.6.0 REQUIRED COMPONENTS ${required_components} CONFIG)

add_executable(hello_dart hello_dart.cpp)
target_link_libraries(hello_dart PUBLIC ${required_libraries})
