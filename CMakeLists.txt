cmake_minimum_required(VERSION 3.10)
project(SDL3UE VERSION 0.0.1 LANGUAGES CXX)

include(cmake/CompilerSettings.cmake)

# 设置项目根目录
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/prebuilt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")


# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/out/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/out/Release)

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 指定静态库路径
# list(APPEND CMAKE_PREFIX_PATH
#     "/library/glm/lib/"
#     "/library/SDL3/SDL3-3.4.4"
#     "/library/SDL3/SDL3_image-3.4.2"
#     "/library/SDL3/SDL3_mixer-3.2.0"
#     "/library/SDL3/SDL3_ttf-3.2.2"
# )

#查找并载入Cmake预设
find_package(glm CONFIG REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

# # 设置项目根目录
# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/prebuilt)

# 设置通用源文件
set(SOURCES
    "main.cpp"
    "src/Config.h"
    "src/Game.cpp"
    "src/Object.cpp"
    "src/Sprite.cpp"
    "src/AssetsManager.cpp"
    "src/AJ_TTF_Engine.cpp"
)

# 根据平台向"通用源文件"追加平台专属的文件
if(WIN32)
    # 如果是 Windows 平台, 将资源文件追加到源文件列表
    list(APPEND SOURCES resources.rc)
endif()
# TODO: MacOS 和 Linux 平台

# 添加可执行文件, 使用配置好的 "SOURCES" 变量
add_executable(${TARGET} ${SOURCES})

# 链接库
target_link_libraries(${TARGET}
${SDL3_LIBRARIES}
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
)

setup_compiler_options(${TARGET})

# 复制库到输出目录
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glm::glm>
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE:SDL3_image::SDL3_image>
        $<TARGET_FILE:SDL3_mixer::SDL3_mixer>
        $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
        $<TARGET_FILE_DIR:${TARGET}>
)
# 复制资源到输出目录
if(WIN32)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets/
            $<TARGET_FILE_DIR:${TARGET}>/assets/
    )
endif()