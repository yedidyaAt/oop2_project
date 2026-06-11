configure_file ("level_01.json" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("levels.json" ${CMAKE_BINARY_DIR} COPYONLY)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION ${CMAKE_BINARY_DIR}/resources FILES_MATCHING PATTERN "*.png")