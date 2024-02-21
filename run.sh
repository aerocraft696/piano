#!/bin/bash
BUILD_DIR=build
if [[ ! -d "${BUILD_DIR}" ]]; then
  mkdir -p ${BUILD_DIR}
fi
# 进入 build 文件夹
cd ${BUILD_DIR}

# 运行 CMake
cmake ..

# 使用 make 编译
make

# 运行生成的可执行文件
# ./merge_images
