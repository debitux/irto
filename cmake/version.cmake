
# The project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

string(TIMESTAMP CURRENT_DATE %d-%m-%Y)
string(TIMESTAMP CURRENT_TIME %H:%M)

SET(BUILD_DATE ${CURRENT_DATE}_${CURRENT_TIME} )

set(version_in ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.in)
set(version_hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp)

configure_file(${version_in} ${version_hpp})
