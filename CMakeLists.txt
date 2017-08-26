
cmake_minimum_required(VERSION 3.5)

project(MinecraftFramework)

file(GLOB FRAMEWORK_SRC "*.cpp" "*.h")
set(FRAMEWORK_EXE bot)

add_executable(${FRAMEWORK_EXE} ${FRAMEWORK_SRC})

set_property(TARGET ${FRAMEWORK_EXE} PROPERTY CXX_STANDARD 11)
