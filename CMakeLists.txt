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
find_package(spdlog REQUIRED)
find_package(Catch2 3 REQUIRED)


set(TRESTLE_PRIVATE_LIBRARIES
Boost::boost
nlohmann_json::nlohmann_json
)

# The required C++ Standard for Server++ is C++14.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Add an executable with the above sources
#add_executable(trestle ${SOURCES})

# Set the direcoties that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
#target_include_directories(trestle
#    PRIVATE ${PROJECT_SOURCE_DIR}/trestle
#)

set (TRESTLE_PUBLIC_SOURCE_FILES
    #trestle/main.cpp
    trestle/GameObject.cpp
    trestle/LoggingService.cpp
    trestle/SettingsDB.cpp
)

set (TRESTLE_PUBLIC_HEADER_FILES
    trestle/GameObject.hpp
    trestle/LoggingService.hpp
    trestle/ScriptFuncs.hpp
    trestle/EntityDefs.hpp
    trestle/StringFuncs.hpp
    trestle/SettingsDB.hpp
    trestle/RabbitHandler.hpp
    trestle/stdafx.hpp
)


add_executable(trestle
    #${TRESTLE_PUBLIC_HEADER_FILES}
    trestle/main.cpp
    ${TRESTLE_PUBLIC_SOURCE_FILES}
    
)
add_executable(tests
    #${TRESTLE_PUBLIC_HEADER_FILES}
    trestle/tests.cpp
    ${TRESTLE_PUBLIC_SOURCE_FILES}
    
)
target_precompile_headers(trestle
  PUBLIC
    trestle/stdafx.hpp
  PRIVATE
   #[["other_header.h"]]
    #<unordered_map>
)
target_precompile_headers(tests
  PUBLIC
    trestle/stdafx.hpp
  PRIVATE
   #[["other_header.h"]]
    #<unordered_map>
)
target_include_directories(trestle 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/trestle
        ${PROJECT_SOURCE_DIR}/unqlite
        /sol2/include/
        /speedb/include/
        #/unqlite/
)
target_include_directories(tests 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/trestle
        ${PROJECT_SOURCE_DIR}/unqlite
        /sol2/include/
        /speedb/include/
        #/unqlite/
)

include_directories(/usr/local/include ${LUA_INCLUDE_DIR} ${BOOST_INCLUDEDIR})

target_link_libraries(trestle
    ${TRESTLE_PRIVATE_LIBRARIES}
    ${LUA_LIBRARIES}
    /speedb/build/libspeedb.so
    uv
    amqpcpp
    dl
    pthread
)

target_link_libraries(tests
    ${TRESTLE_PRIVATE_LIBRARIES}
    ${LUA_LIBRARIES}
    /speedb/build/libspeedb.so
    uv
    amqpcpp 
    Catch2::Catch2WithMain
    dl
    pthread
)

#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
#include(CTest)
#include(Catch)
#catch_discover_tests(trestle)

#link_directories(/speedb/build)