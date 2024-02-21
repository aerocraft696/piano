#!/bin/bash

# 进入 build 文件夹
cd build

# 运行 CMake
cmake ..

# 使用 make 编译
make

# 运行生成的可执行文件
./merge_images
