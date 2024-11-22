cmake_minimum_required(VERSION 3.22)

project("DataPrintingEngine"
    VERSION 1.0.0.0
    DESCRIPTION "Data Printing Engine"
    HOMEPAGE_URL "<URL>"
    LANGUAGES C CXX
)

message_project()

add_library(${PROJECT_NAME} STATIC)
add_library(Library::Module::DataPrintingEngine ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC Library::Helpers)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Includes)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_sources(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/IDataPrintingEngine.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/DataPrintingEngineFactory.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/DataPrintingEngineFactory.cpp"

    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/Module/Internal/DataPrintingEngine.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Internal/DataPrintingEngine.cpp"
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
