cmake_minimum_required(VERSION 3.20)

# ============================================================
# 项目名称
# ============================================================
project(BusinessServer VERSION 1.0.0 LANGUAGES CXX)

# ============================================================
# C++ 标准
# ============================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# 编译选项
# ============================================================
if(MSVC)
    # MSVC 编译选项
    add_compile_options(/W4 /utf-8)
    # 将静态运行时库与动态运行时库统一，这里使用动态（/MD）
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
    # GCC/Clang 编译选项
    add_compile_options(-Wall -Wextra -Wpedantic)
    add_compile_options(-O2)
endif()

# ============================================================
# 输出目录 — 所有生成文件统一放在 build 下
# ============================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ============================================================
# 第三方依赖（示例：spdlog 日志库）
# 取消注释以下内容以启用 FetchContent 自动拉取
# ============================================================
# include(FetchContent)
#
# FetchContent_Declare(
#     spdlog
#     GIT_REPOSITORY https://github.com/gabime/spdlog.git
#     GIT_TAG        v1.12.0
# )
# FetchContent_MakeAvailable(spdlog)

# ============================================================
# 子目录
# ============================================================
# add_subdirectory(src)

# ============================================================
# 可执行目标（示例）
# 后续有源文件后取消注释并修改 file(GLOB ...) 为显式列出源文件
# ============================================================
# file(GLOB_RECURSE SOURCES
#     src/*.cpp
#     src/*.cc
# )
#
# add_executable(${PROJECT_NAME} ${SOURCES})
#
# target_include_directories(${PROJECT_NAME} PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )
#
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     # spdlog::spdlog
# )

# ============================================================
# 安装规则（可选）
# ============================================================
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
