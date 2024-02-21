cmake_minimum_required(VERSION 3.4.1)
project(MergeImages)

find_package(OpenCV REQUIRED)

add_executable(merge_images src/main.cpp)

target_link_libraries(merge_images ${OpenCV_LIBS})
