cmake_minimum_required(VERSION 3.10)
project(OpenCLHelloWorld)

# 查找OpenCL库
find_package(OpenCL REQUIRED)

# 添加可执行文件
add_executable(hello_world main.cpp)

# 链接OpenCL库
target_link_libraries(hello_world OpenCL::OpenCL)