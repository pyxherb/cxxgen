find_package(peff REQUIRED)

file(GLOB HEADERS *.h)
file(GLOB SRC *.cc)

add_library(cxxgen SHARED)
target_compile_definitions(cxxgen PRIVATE IS_CXXGEN_BASE_BUILDING=1)
set_target_properties(cxxgen PROPERTIES CXX_STANDARD 17)
target_sources(cxxgen PRIVATE ${HEADERS} ${SRC})
target_include_directories(cxxgen PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(cxxgen PUBLIC peff_base peff_utils peff_containers)
set_target_properties(cxxgen PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    ARCHIVE FALSE
)

add_library(cxxgen_static STATIC)
target_compile_definitions(cxxgen_static PRIVATE CXXGEN_STATIC_LINK=1 IS_CXXGEN_BASE_BUILDING=1)
set_target_properties(cxxgen_static PROPERTIES CXX_STANDARD 17)
target_sources(cxxgen_static PRIVATE ${HEADERS} ${SRC})
target_link_libraries(cxxgen_static PUBLIC peff_base_static peff_utils_static peff_containers_static)
target_include_directories(cxxgen_static PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
set_target_properties(cxxgen_static PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
    VERSION ${PROJECT_VERSION}
)

add_subdirectory("ast")

install(TARGETS cxxgen cxxgen_static
    EXPORT cxxgenTargets
    LIBRARY DESTINATION lib/
    ARCHIVE DESTINATION lib/
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/peff/base/
)
