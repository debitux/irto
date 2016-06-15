add_executable(
    program_options_test 
    unit_test/program_options_test.cpp
    src/program_options.hpp
    src/program_options.cpp)

target_link_libraries(
    program_options_test 
    ${Boost_LIBRARIES}
    )

add_test(Program_Options_Test ${BIN_DIR}/program_options_test)
