# 创建库
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_library(Functions ${files})


target_include_directories(Functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


