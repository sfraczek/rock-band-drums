set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/lib.hpp")

add_library(lib lib.cpp ${HEADER_LIST})
target_include_directories(lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})