# 创建库
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_library(data ${files})

target_include_directories(data INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
