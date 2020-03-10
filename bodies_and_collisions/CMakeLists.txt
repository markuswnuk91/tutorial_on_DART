cmake_minimum_required(VERSION 3.5.1)

get_filename_component(example_name ${CMAKE_CURRENT_LIST_DIR} NAME)

project(tutorial_bodies_and_collisions)

set(required_components utils-urdf gui)
set(required_libraries dart dart-utils-urdf dart-gui)

find_package(DART 6.6.0 REQUIRED COMPONENTS ${required_components} CONFIG)

add_executable(bodies_and_collisions bodies_and_collisions.cpp)
target_link_libraries(bodies_and_collisions PUBLIC ${required_libraries})
