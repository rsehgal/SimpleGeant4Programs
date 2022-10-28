cmake_minimum_required(VERSION 2.8)
project(MST)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

option(ENABLE_OPTICAL_PHYSICS "Enable Optical Physics" OFF)
option(PSBAR_GEOM "Use ISMRAN PSBAR Geometry" OFF)
option(VERBOSE "Enable some printing useful for debugging" OFF)

if(VERBOSE)
add_definitions(-DVERBOSE)
endif(VERBOSE)

if(PSBAR_GEOM)
add_definitions(-DPSBAR_GEOM)
endif(PSBAR_GEOM)

if(ENABLE_OPTICAL_PHYSICS)
add_definitions(-DENABLE_OPTICAL_PHYSICS)
endif(ENABLE_OPTICAL_PHYSICS)
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
#message(STATUS "ROOT LIB : ${ROOT_LIBRARIES}")
#message(STATUS "ROOT INC : ${ROOT_INCLUDE_DIRS}")

file(GLOB MAC_FILES ${PROJECT_SOURCE_DIR}/MacFiles/*)
message(STATUS ${MAC_FILES})
#file(COPY ${MAC_FILES} DESTINATION ${PROJECT_SOURCE_DIR}/build)
file(COPY ${MAC_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/CommonHelpers)
include_directories(../..)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/CommonHelpers/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.h ${PROJECT_SOURCE_DIR}/inc/*.hh ../../base/Vector3D.h ${PROJECT_SOURCE_DIR}/CommonHelpers/*.h) 

add_executable(main main.cpp ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
#target_link_libraries(main ${Geant4_LIBRARIES} Tomo)
add_executable(TestQNearQFar_ExpData ${PROJECT_SOURCE_DIR}/CommonHelpers/test/TestQNearQFar_ExpData.cpp ${sources} ${headers})
target_link_libraries(TestQNearQFar_ExpData ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

