project(SpaceBash)
cmake_minimum_required(VERSION 2.6)

# Public Settings
# ------------------------------------------------------------------------------

# Only runs on win32, for now.
set(_PLATFORM "win32")

# Output Location
# ------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Compile with C++11 enabled.
if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

add_definitions("-DNOMINMAX")
add_definitions("-D_UNICODE" "-DUNICODE")

if(MINGW)
  # Windows XP and up
  add_definitions("-D_WIN32_WINNT=0x0501")
  message(STATUS "WIN32: Setting windows version to XP")
else()
  # Windows 7 and up
  add_definitions("-D_WIN32_WINNT=0x0601")
  message(STATUS "WIN32: Setting windows version to Vista")
  
  message(STATUS "MSVC: Mapping memory leaks.")
  add_definitions("-D_CRTDBG_MAP_ALLOC")

  message(STATUS "MSVC: Enable variadic tuples for Visual Studio 2012.")
  add_definitions("-D_VARIADIC_MAX=10")

  message(STATUS "MSVC: Enable multi-processor compilation.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

  message(STATUS "MSVC: Enable use full paths.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FC")

  # Default to statically-linked runtime.
  set(MSVC_RUNTIME "dynamic" CACHE STRING "Use dynamic or static runtime (dynamic/static)")
  # Set compiler options.
  set(variables
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_MINSIZEREL
    CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_MINSIZEREL
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_RELWITHDEBINFO
  )
  if(${MSVC_RUNTIME} STREQUAL "static")
    message(STATUS "MSVC: Forcing use of statically-linked runtime.")
    foreach(variable ${variables})
      if(${variable} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
      endif()
    endforeach()
  else()
    message(STATUS "MSVC: Forcing use of dynamically-linked runtime.")
    foreach(variable ${variables})
      if(${variable} MATCHES "/MT")
        string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
      endif()
    endforeach()
  endif()
endif()

# Executable name and source files
# ------------------------------------------------------------------------------

file(GLOB _SOURCES
    "src/*.h"
    "src/*.cpp"
)

set(_EXE_NAME "SpaceBash_cmake")
add_executable(${_EXE_NAME} main.cpp ${_SOURCES})
# For third_party libraries, we use the root of the project as an include
# directory.
include_directories(".")
add_subdirectory("src")

include_directories("src")
