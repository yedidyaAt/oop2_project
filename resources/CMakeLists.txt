# image object
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/object
     DESTINATION ${CMAKE_BINARY_DIR}/resources/images/
     FILES_MATCHING PATTERN "*.png")

# ui images
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/ui
     DESTINATION ${CMAKE_BINARY_DIR}/resources/images
     FILES_MATCHING PATTERN "*.png")

# animation images
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/animation
     DESTINATION ${CMAKE_BINARY_DIR}/resources/images
     FILES_MATCHING PATTERN "*.png")

# sounds
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sounds
     DESTINATION ${CMAKE_BINARY_DIR}/resources/
     FILES_MATCHING PATTERN "*.wav")

# music
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/music
     DESTINATION ${CMAKE_BINARY_DIR}/resources/
     FILES_MATCHING PATTERN "*.wav")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/music
     DESTINATION ${CMAKE_BINARY_DIR}/resources/
     FILES_MATCHING PATTERN "*.mp3")

# levels json
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels
     DESTINATION ${CMAKE_BINARY_DIR}/resources
     FILES_MATCHING PATTERN "*.json")

# fonts
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts
     DESTINATION ${CMAKE_BINARY_DIR}/resources
     FILES_MATCHING PATTERN "*.ttf")
