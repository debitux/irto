cmake_minimum_required(VERSION 3.0.0)

# Nom du projet
include(cmake/version.cmake)
project(irto VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})


#include(CTest) 
#enable_testing()

#include(cmake/lib.cmake)
#include(cmake/unix.cmake)
#include(cmake/windows.cmake)

include(cmake/build.cmake)


include(cmake/doxygen.cmake)

include(cmake/irto_CMakeLists.cmake)
include(cmake/unitTest_CMakeLists.cmake)
