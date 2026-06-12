# image object
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/object
     DESTINATION ${CMAKE_BINARY_DIR}/resources/images/
     FILES_MATCHING PATTERN "*.png")

#file json
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels
     DESTINATION ${CMAKE_BINARY_DIR}/resources/
     FILES_MATCHING PATTERN "*.json")