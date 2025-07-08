file(GLOB SRC *.cc)
add_executable(astgen ${SRC})
target_link_libraries(astgen PRIVATE cxxgen_static)
set_target_properties(astgen PROPERTIES CXX_STANDARD 17)
