#----------------------------------------------------------------------
#                            LIBRARIES
#----------------------------------------------------------------------

find_package(Boost 1.55 
    COMPONENTS 

    filesystem 
    program_options 
    date_time 
    unit_test_framework 

    REQUIRED)
# filesystem system serialization thread date_time program_options unit_test_framework 

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
message("***  Boost-dir  : ${Boost_INCLUDE_DIR}")
message("***  Boost-Link : ${Boost_LIBRARIES}")
