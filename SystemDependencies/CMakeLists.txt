# target_sources(
#     Playground_OpenCV
#     PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/FSRCNN_x2.pb,
#     ${CMAKE_CURRENT_LIST_DIR}/FSRCNN_x3.pb,
#     ${CMAKE_CURRENT_LIST_DIR}/FSRCNN_x4.pb,
#     ${CMAKE_CURRENT_LIST_DIR}/FSRCNN-small_x2.pb,
#     ${CMAKE_CURRENT_LIST_DIR}/FSRCNN-small_x3.pb,
#     ${CMAKE_CURRENT_LIST_DIR}/FSRCNN-small_x4.pb
# )



target_include_directories(
    Playground_OpenCV
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)