file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)
target_sources(cxxgen PRIVATE ${HEADERS} ${SRC})
target_sources(cxxgend PRIVATE ${HEADERS} ${SRC})

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cxxgen/ast)
