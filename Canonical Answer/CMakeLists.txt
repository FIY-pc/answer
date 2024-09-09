CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
# 项目名通用设置方法
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)
# 设置C语言标准
set(CMAKE_C_STANDARD 11)

# 版本信息
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Canonical_Answer.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Canonical_Answer.h)

add_subdirectory(Functions)
add_executable(${ProjectId} main.c)
# 链接Function库
target_link_libraries(${ProjectId} PUBLIC Functions)


