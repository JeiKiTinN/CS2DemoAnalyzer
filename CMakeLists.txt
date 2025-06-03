cmake_minimum_required(VERSION 3.13)

project(CS2DemoAnalyzer)
set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR "D:/CS2Parser/CS2DemosAnalyzer/Opencv/opencv/build")
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB IMGUI_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-1.91.9b/*.cpp"
)

set(IMGUI_BACKENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-1.91.9b/backends/imgui_impl_dx11.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-1.91.9b/backends/imgui_impl_win32.cpp"
)

# Удаляем ненужные бэкенды из общего списка
list(REMOVE_ITEM IMGUI_SOURCES ${IMGUI_BACKENDS})


add_executable(CS2DemoAnalyzer ${MY_SOURCES} ${IMGUI_SOURCES} ${IMGUI_BACKENDS})


target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

target_include_directories(CS2DemoAnalyzer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-1.91.9b"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-1.91.9b/backends"
     ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(CS2DemoAnalyzer PRIVATE
    d3d11
    dxgi
    dxguid
    user32
    ${OpenCV_LIBS}
)
