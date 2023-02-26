# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.0)

# Set the project name
project (trestle)

# Create a sources variable with a link to all cpp files to compile
#set(SOURCES
#    src/main.cpp
#)

find_package(Boost COMPONENTS container REQUIRED)
#find_package(gsl-lite REQUIRED)
#find_package(ZLIB REQUIRED)
#find_package(Threads REQUIRED)
find_package(Lua REQUIRED)
find_package(nlohmann_json REQUIRED)

set(TRESTLE_PRIVATE_LIBRARIES
Boost::boost
nlohmann_json::nlohmann_json
)

# The required C++ Standard for Server++ is C++14.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add an executable with the above sources
#add_executable(trestle ${SOURCES})

# Set the direcoties that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
#target_include_directories(trestle
#    PRIVATE ${PROJECT_SOURCE_DIR}/trestle
#)

set (TRESTLE_PUBLIC_SOURCE_FILES
    trestle/main.cpp
    trestle/GameObject.cpp
)

set (TRESTLE_PUBLIC_HEADER_FILES
    trestle/GameObject.hpp
)


add_executable(trestle
    #${TRESTLE_PUBLIC_HEADER_FILES}
    ${TRESTLE_PUBLIC_SOURCE_FILES}
)

target_precompile_headers(trestle
  PUBLIC
    trestle/stdafx.hpp
  PRIVATE
   #[["other_header.h"]]
    #<unordered_map>
)

target_include_directories(trestle 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/trestle
        /sol2/include/
)

include_directories(/usr/local/include ${LUA_INCLUDE_DIR} ${BOOST_INCLUDEDIR})

target_link_libraries(trestle
    ${TRESTLE_PRIVATE_LIBRARIES}
    ${LUA_LIBRARIES}
    uv
)