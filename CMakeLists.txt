cmake_minimum_required(VERSION 3.22.1)
project(catnet)

set(CMAKE_CXX_STANDARD 17)

# 添加头文件和源文件所在目录到include路径
include_directories(${CMAKE_SOURCE_DIR}/src)

# 自动查找src目录中的所有源文件
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# 打印找到的源文件（调试用，可选操作）
message(STATUS "Source files: ${SOURCES}")
#add_executable(catnet ${SOURCES})
add_executable(test_log test/test_log.cpp ${SOURCES}
        src/log2/log.h)
add_executable(test_env test/test_env.cpp ${SOURCES})
add_executable(test_crtp test/test_crtp/test_crtp.cpp test/test_crtp/animal.h
        test/test_crtp/animal2.h
        )
add_executable(test_crtp2 test/test_crtp/test_crtp2.cpp)
