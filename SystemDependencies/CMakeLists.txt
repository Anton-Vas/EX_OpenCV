#  SUPRES resourses:
#
#   fsrcnn_model_file - protobuffers name
#   FSRCNN_x2
#   FSRCNN_x3
#   FSRCNN_x4
#   FSRCNN-small_x2
#   FSRCNN-small_x3
#   FSRCNN-small_x4
#   
#   fsrcnn_model_name - MUST be corelated to 'fsrcnn_model_file' (as it should be in OpenCV API)
#   -> "fsrcnn"
#
#   fsrcnn_scale      - MUST be corelated to 'fsrcnn_model_file' (as it should be in OpenCV API)
#   -> 2/3/4
#   



target_include_directories(
    Playground_OpenCV
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)