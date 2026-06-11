#target_include_directories (${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
#file (GLOB MY_HEADER_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.h)
#target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_HEADER_FILES})

file(GLOB_RECURSE MY_HEADER_FILES CONFIGURE_DEPENDS "*.h")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MY_HEADER_FILES})

# כל תת-תיקייה ב-include הופכת ל-include path
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/core
    ${CMAKE_CURRENT_LIST_DIR}/data
    ${CMAKE_CURRENT_LIST_DIR}/data/factory
    ${CMAKE_CURRENT_LIST_DIR}/data/loader
    ${CMAKE_CURRENT_LIST_DIR}/data/resource
    ${CMAKE_CURRENT_LIST_DIR}/objects
    ${CMAKE_CURRENT_LIST_DIR}/settings
    ${CMAKE_CURRENT_LIST_DIR}/strategies
    ${CMAKE_CURRENT_LIST_DIR}/utility/
    ${CMAKE_CURRENT_LIST_DIR}/utility/enums
    ${CMAKE_CURRENT_LIST_DIR}/utility/structs
    ${CMAKE_CURRENT_LIST_DIR}/utility/constants
    ${CMAKE_CURRENT_LIST_DIR}/external
)