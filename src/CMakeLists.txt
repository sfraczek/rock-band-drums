set(HEADER_LIST ${PROJECT_SOURCE_DIR}/include/lib.hpp
                ${PROJECT_SOURCE_DIR}/include/drum.hpp
                ${PROJECT_SOURCE_DIR}/include/algebra.hpp
                ${PROJECT_SOURCE_DIR}/include/util.hpp
                ${PROJECT_SOURCE_DIR}/include/config_file.hpp
                ${PROJECT_SOURCE_DIR}/include/nlohmann/json.hpp)

add_library(lib STATIC lib.cpp util.cpp config_file.cpp ${HEADER_LIST})
target_include_directories(lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})