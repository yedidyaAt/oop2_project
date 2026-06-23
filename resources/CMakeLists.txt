# image object
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/object
     DESTINATION ${CMAKE_BINARY_DIR}/resources/images/
     FILES_MATCHING PATTERN "*.png")

# image sounds
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sounds
     DESTINATION ${CMAKE_BINARY_DIR}/resources/
     FILES_MATCHING PATTERN "*.wav")

# image music
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/music
     DESTINATION ${CMAKE_BINARY_DIR}/resources/
     FILES_MATCHING PATTERN "*.wav")

#file json
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels
     DESTINATION ${CMAKE_BINARY_DIR}/resources
     FILES_MATCHING PATTERN "*.json")