CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
# 项目名通用设置方法
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)
# 设置C语言标准
set(CMAKE_C_STANDARD 17)

add_executable(${ProjectId} src/level2-2.c)

set_target_properties(${ProjectId} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)