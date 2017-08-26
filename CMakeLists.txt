
cmake_minimum_required(VERSION 3.2)

project(MinecraftFramework)

#setup variables
file(GLOB FRAMEWORK_SRC "*.cpp" "*.h")
set(FRAMEWORK_EXE bot)
set(FRAMEWORK_NAME MinecraftFramework)

#compile framework library
add_library(${FRAMEWORK_NAME} STATIC ${FRAMEWORK_SRC})

#change it for testing purpose(compile executable file with MinecraftFramework)
#add_executable(${FRAMEWORK_EXE} main.cpp)
#target_link_libraries(${FRAMEWORK_EXE} ${FRAMEWORK_NAME})

#using C++11
#set_property(TARGET ${FRAMEWORK_EXE} PROPERTY CXX_STANDARD 11) #uncoment if compile with main.cpp
set_property(TARGET ${FRAMEWORK_NAME} PROPERTY CXX_STANDARD 11)
