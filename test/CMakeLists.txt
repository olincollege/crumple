# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

list(APPEND CMAKE_CTEST_ARGUMENTS --verbose)

add_executable(test_collapser test_collapser.c)
target_link_libraries(test_collapser
    PRIVATE collapser
    PRIVATE parser
    PRIVATE helpers
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_collapser
    COMMAND test_collapser ${CRITERION_FLAGS}
)

add_executable(test_parser test_parser.c)
target_link_libraries(test_parser
    PRIVATE parser
    PUBLIC ${CRITERION}
)
add_test(
    NAME test_parser
    COMMAND test_parser ${CRITERION_FLAGS}
)
