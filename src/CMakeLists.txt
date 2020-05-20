file(GLOB HEADER_LIST "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCES "*.cpp")

add_library(libraries STATIC ${SOURCES} ${HEADER_LIST})
target_include_directories(libraries PUBLIC ${PROJECT_SOURCE_DIR}/include)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})