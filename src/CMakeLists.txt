file(GLOB HEADER_LIST "${PROJECT_SOURCE_DIR}/include/*.hpp")
set(SOURCES
    config_file.cpp
    lib.cpp
    util.cpp)

add_library(libraries STATIC ${SOURCES})
target_include_directories(libraries PUBLIC ${PROJECT_SOURCE_DIR}/include)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})