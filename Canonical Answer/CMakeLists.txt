CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
# 项目名通用设置方法
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)
# 设置C语言标准
set(CMAKE_C_STANDARD 17)

# 版本信息
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

# 添加公共头文件
include_directories(include)
include_directories(build)
include_directories(data)
# 包含项目下的所有目录
add_subdirectory(Functions)
add_subdirectory(data)
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(build)

FILE(GLOB SRCS src/*.c)
# 添加exe
add_executable(${ProjectId} ${SRCS})
# 链接Function库
target_link_libraries(${ProjectId} PUBLIC Functions)
# 链接data库
target_link_libraries(${ProjectId} PUBLIC data)
# 链接include库
target_link_libraries(${ProjectId} PUBLIC include)



