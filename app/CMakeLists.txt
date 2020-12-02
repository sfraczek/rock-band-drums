add_definitions(-D_HAS_AUTO_PTR_ETC=1)
# GUI library
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.5.1
    GIT_PROGRESS   TRUE
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(sfml)

add_executable(app app.cpp)

target_include_directories(app PRIVATE ${sfml_SOURCE_DIR}/include)
target_link_directories(app PRIVATE ${sfml_BINARY_DIR}/lib)

target_link_libraries(app PRIVATE libraries sfml-audio sfml-graphics sfml-window sfml-system)