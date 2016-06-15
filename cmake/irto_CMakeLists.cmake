include_directories (src)


SET ( SRCS 
        src/main.cpp
        src/typedef/memory.hpp
        src/program_options.cpp
        src/irto.cpp
        )

SET ( HEADERS 
        src/program_options.hpp
        src/irto.hpp
        )


add_executable(
        ${PROJECT_NAME}
        ${HEADERS}	
        ${SRCS}	
        )

target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        #lib
        )
