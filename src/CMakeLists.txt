# If you have a program that's just a .c file and it has a main method, define
# an executable. If it has both a .c and .h file, make it a library. Also, link
# libraries appropriately here. Targets should be added in dependency order - if
# executable bar needs library foo, then you should do
#   add_library(foo foo.c foo.h)
#   add_executable(bar bar.c)
#   target_link_libraries(bar PRIVATE foo)
# or similar. The PRIVATE/INTERFACE/PUBLIC keyword will depend on whether the
# library is used only in function bodies (PRIVATE), only in function
# signatures/types (INTERFACE), or both (PUBLIC).

add_library(datatypes datatypes.c datatypes.h)

add_library(collapser collapser.c collapser.h)
target_link_libraries(collapser PRIVATE datatypes)

add_library(parser parser.c parser.h)
target_link_libraries(parser PRIVATE datatypes)

add_library(imgen imgen.c imgen.h)
target_link_libraries(imgen PRIVATE datatypes)

add_executable(main main.c)
target_link_libraries(main PRIVATE collapser parser imgen)
