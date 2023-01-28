cmake_minimum_required(VERSION 3.20.0)
project(Playground_OpenCV VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Playground_OpenCV 
    main.hpp
    main.cpp
)

# >> project folders
add_subdirectory(SystemDependencies)
add_subdirectory(SystemManager)
add_subdirectory(DebugPrint)

############## Project requirements ##################################
    # c++  minimum
set(CMAKE_CXX_STANDARD_REQUIRED 17)

    # root path
set(ROOT /home/dev/Desktop/EX_openCV)

    # threads
find_package(Threads REQUIRED)
target_link_libraries(Playground_OpenCV Threads::Threads)

    # OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Playground_OpenCV ${OpenCV_LIBS})

######################################################################

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message("\n############################################################################################\n")
message("> BUILD INFO")
message("-- BASIC")
message("       ROOT:           " ${ROOT})
message("       C++ STANDART:   " ${CMAKE_CXX_STANDARD_REQUIRED})
message("       CMAKE version:  " ${CMAKE_VERSION})
message("-- OpenCV")
message("       OPENCV version: " ${OpenCV_VERSION})
message("       OPENCV include: " ${OpenCV_INCLUDE_DIRS})
message("\n############################################################################################\n")



