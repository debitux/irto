include_directories (src)


SET ( SRCS 
        ${SRCS_DIR}/irto.cpp
        )

SET ( HEADERS 
        ${SRCS_DIR}/irto.hpp
        )


add_executable(
	${PROJECT_NAME}
        ${HEADERS}	
        ${SRCS}	
	)

target_link_libraries(
	${PROJECT_NAME}
        #lib
	)
