# ´´½¨¿â
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_library(include ${files})

target_include_directories(include PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})