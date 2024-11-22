cmake_minimum_required(VERSION 3.22)

project("DataModule"
    VERSION 1.0.0.0
    DESCRIPTION "Data Module"
    HOMEPAGE_URL "<URL>"
    LANGUAGES C CXX
)

message_project()

add_library(${PROJECT_NAME} STATIC)
add_library(Library::Module::DataModule ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Library::Helpers
        Library::Module::DataGenerator
        Library::Module::DataSearchEngine
        Library::Module::DataPrintingEngine
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Includes)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_sources(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/IModule.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/ModuleFactory.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/ModuleFactory.cpp"

    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/Internal/DataModule.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Internal/DataModule.cpp"
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
