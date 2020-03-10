cmake_minimum_required(VERSION 3.5.1)

project(tutorial_load_urdf)

set(required_components utils-urdf gui)
set(required_libraries dart dart-utils-urdf dart-gui)

find_package(DART 6.6.0 REQUIRED COMPONENTS ${required_components} CONFIG)

add_executable(load_urdf load_urdf.cpp)
target_link_libraries(load_urdf PUBLIC ${required_libraries})
