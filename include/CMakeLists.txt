file(GLOB_RECURSE MY_HEADER_FILES CONFIGURE_DEPENDS "*.h" "*.hpp")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MY_HEADER_FILES})

# אסוף את כל התיקיות שמכילות הדרים והפוך כל אחת ל-include path
set(MY_INCLUDE_DIRS "")
foreach(_header ${MY_HEADER_FILES})
    get_filename_component(_dir ${_header} DIRECTORY)
    list(APPEND MY_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES MY_INCLUDE_DIRS)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${MY_INCLUDE_DIRS}
)