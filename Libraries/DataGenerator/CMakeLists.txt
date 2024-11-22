cmake_minimum_required(VERSION 3.22)

project("DataGenerator"
    VERSION 1.0.0.0
    DESCRIPTION "Data Generator"
    HOMEPAGE_URL "<URL>"
    LANGUAGES C CXX
)

message_project()

add_library(${PROJECT_NAME} STATIC)
add_library(Library::Module::DataGenerator ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Includes)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_sources(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/IDataGenerator.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/DataGeneratorFactory.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/DataGeneratorFactory.cpp"

    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/Internal/DataGenerator.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Internal/DataGenerator.cpp"
)

install(
    TARGETS ${PROJECT_NAME}
    CONFIGURATIONS Debug
    RUNTIME DESTINATION Debug/Bin # .out files -> .exe
    LIBRARY DESTINATION Debug/Bin # .so  files -> .dll
    ARCHIVE DESTINATION Debug/Bin # .a   files -> .lib
)

install(
    TARGETS ${PROJECT_NAME}
    CONFIGURATIONS Release
    RUNTIME DESTINATION Release/Bin # .out files -> .exe
    LIBRARY DESTINATION Release/Bin # .so  files -> .dll
    ARCHIVE DESTINATION Release/Bin # .a   files -> .lib
)
