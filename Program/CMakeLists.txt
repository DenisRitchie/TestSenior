cmake_minimum_required(VERSION 3.22)

project ("Program"
    VERSION 1.0.0.0
    DESCRIPTION "Program"
    HOMEPAGE_URL "<URL>"
    LANGUAGES C CXX
)

message_project()

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC Library::Module::DataModule)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
)
