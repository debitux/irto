#----------------------------------------------------------------------
#                            COMPILATION
#----------------------------------------------------------------------

IF(NOT CMAKE_BUILD_TYPE)
        SET(CMAKE_BUILD_TYPE Debug CACHE STRING
                "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
                FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)


message (STATUS "${PROJECT_NAME} version : ${PROJECT_VERSION} in ${CMAKE_BUILD_TYPE} mode of ${CMAKE_SYSTEM}")

INCLUDE (CheckCXXCompilerFlag)

if(CMAKE_COMPILER_IS_GNUCXX)
        check_cxx_compiler_flag("-Wall" CXX_COMPILER_FLAG_WALL)
        if (CXX_COMPILER_FLAG_WALL)
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -w -std=c++14") ##Optimize -Werror -Wdeprecated-declarations -Wall -Wextra
                set(CMAKE_EXE_LINKER_FLAGS -s)	 ## Strip binary
        endif (CXX_COMPILER_FLAG_WALL)
endif(CMAKE_COMPILER_IS_GNUCXX)


#message (STATUS "Lib to link : ${LIBRARIES_BDD}")

#----------------------------------------------------------------------
#                            DIRECTORY
#----------------------------------------------------------------------

SET ( SRCS_DIR
        ${PROJECT_SOURCE_DIR}/src
        )

SET(BIN_DIR
        ${PROJECT_SOURCE_DIR}/bin)

SET(TEST_DIR
        ${BIN_DIR}/test)

set(EXECUTABLE_OUTPUT_PATH 
        ${BIN_DIR}/)

set(LIB_DIR
        ${PROJECT_SOURCE_DIR}/lib/)

set(LIBRARY_OUTPUT_PATH 
        ${LIB_DIR}/)

set(INCLUDES 
        ${PROJECT_SOURCE_DIR}/include/)



