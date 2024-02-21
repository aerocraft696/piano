cmake_minimum_required(VERSION 3.4.1)
project(MergeImages)

# Set the cross-compiling options
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# Find the OpenCV library for aarch64-linux-gnu
find_package(OpenCV REQUIRED
    PATHS "/path/to/opencv/aarch64-linux-gnu" # Replace with the actual path to your cross-compiled OpenCV
)

# Add include directories for the cross-compiled OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the executable and set sources
add_executable(merge_images src/main.cpp)

# Link against the cross-compiled OpenCV library
target_link_libraries(merge_images ${OpenCV_LIBS} pthread)
