cmake_minimum_required(VERSION 3.16)
project(isdn3000e_lab7)

set(CMAKE_CXX_STANDARD 17)

# --- 1. 定义可执行文件 ---
add_executable(${PROJECT_NAME} main.cpp
        tasks/task1.cpp
        tasks/task1.h
        tasks/task2.cpp
        tasks/task2.h
)

# --- 2. OpenCV 配置 (关键步骤) ---
# 注意：这里的路径必须指向你**编译好的 OpenCV 构建目录**
# 确保你在编译 OpenCV 时，已经通过 -DOPENCV_EXTRA_MODULES_PATH 包含了 opencv_contrib
set(OpenCV_DIR "/Users/koil/opencv/build_opencv")

# 查找 OpenCV (REQUIRED 表示必须找到，否则报错)
# 如果 Contrib 模块已编译进 OpenCV，这里会自动包含
find_package(OpenCV REQUIRED)

# 打印信息用于调试
message(STATUS "OpenCV Version: ${OpenCV_VERSION}")
message(STATUS "OpenCV Include Dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV Libs: ${OpenCV_LIBS}")

# --- 3. RealSense 配置 ---
find_package(realsense2 REQUIRED)

# --- 4. 链接与包含 ---
# 链接库 (OpenCV_LIBS 已包含主模块和 contrib 模块)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${OpenCV_LIBS}
        realsense2::realsense2
)

# 包含头文件目录
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR} # 可选：如果需要包含项目根目录
)

# --- 5. 复制资源文件 (保持原样) ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)