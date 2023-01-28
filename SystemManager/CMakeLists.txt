target_sources(
    Playground_OpenCV
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/SystemManager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SystemManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SysParams.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SysParams.cpp
)

target_include_directories(
    Playground_OpenCV
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)