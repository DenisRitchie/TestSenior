# CMakeList.txt: archivo del proyecto de CMake de nivel superior, establezca la configuración global
# e incluya los subproyectos aquí.
#
cmake_minimum_required (VERSION 3.22)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TestSenior")

# https://cmake.org/cmake/help/latest/command/add_compile_options.html
if (MSVC)
  # warning level 4 and all warnings as errors
  add_compile_options(/W4 /WX /Zc:__cplusplus)
else()
  # lots of warnings and all warnings as errors
  add_compile_options(-Wall -Wextra -pedantic -Werror -fstrict-enums -fconcepts -fpermissive)
endif()

# https://cmake.org/cmake/help/latest/command/add_definitions.html
add_definitions(-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)

macro(message_project)
  # https://cmake.org/cmake/help/latest/command/message.html
  message(STATUS "Building ${PROJECT_NAME} v${PROJECT_VERSION}: ${PROJECT_DESCRIPTION}")
endmacro()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluya los subproyectos.
add_subdirectory ("Libraries")
add_subdirectory ("Program")
