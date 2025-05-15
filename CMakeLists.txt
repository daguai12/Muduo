cmake_minimum_required(VERSION 3.15)
project(mymuduo CXX)
enable_testing()

# 包含头文件的路径
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${PROJECT_SOURCE_DIR}/base)
include_directories(${PROJECT_SOURCE_DIR}/net)

# 定义动态库的位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 定义编译的参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fPIC")

# 进入子目录 base
add_subdirectory(base)
add_subdirectory(net)

# 添加动态库
add_library(mymuduo SHARED ${BASE_SRC} ${NET_SRC})

# 添加头文件的搜索路径
target_include_directories(mymuduo PRIVATE
    ${PROJECT_SOURCE_DIR}/base
    ${PROJECT_SOURCE_DIR}/net
)
