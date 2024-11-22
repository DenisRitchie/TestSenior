cmake_minimum_required(VERSION 3.22)

project("DataSearchEngine"
    VERSION 1.0.0.0
    DESCRIPTION "Data Search Engine"
    HOMEPAGE_URL "<URL>"
    LANGUAGES C CXX
)

message_project()

add_library(${PROJECT_NAME} STATIC)
add_library(Library::Module::DataSearchEngine ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Includes)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_sources(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/IDataSearchEngine.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/DataSearchEngineFactory.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/DataSearchEngineFactory.cpp"

    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/Internal/DataSearchEngine.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Internal/DataSearchEngine.cpp"
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
