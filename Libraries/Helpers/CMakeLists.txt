cmake_minimum_required(VERSION 3.22)

project("Helpers"
    VERSION 1.0.0.0
    DESCRIPTION "Helpers"
    HOMEPAGE_URL "<URL>"
    LANGUAGES C CXX
)

message_project()

add_library(${PROJECT_NAME} INTERFACE)
add_library(Library::Helpers ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Includes)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_sources(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/Helpers/ostream_joiner.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/Helpers/semiregular_box.hpp
)
