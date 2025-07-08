file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)
target_sources(cxxgen PRIVATE ${HEADERS} ${SRC})
if(CXXGEN_BUILD_SHARED)
    target_sources(cxxgend PRIVATE ${HEADERS} ${SRC})
endif()

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cxxgen/ast)
