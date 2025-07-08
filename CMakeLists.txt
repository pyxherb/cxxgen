cmake_minimum_required(VERSION 3.13)
project(cxxgen VERSION 0.1.0)

include_directories(.)

add_subdirectory("cxxgen")
add_subdirectory("example")

# Generate the version file for the config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cxxgenConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
)

# Create config file
configure_package_config_file(
    cmake/cxxgenConfig.cmake.in cxxgenConfig.cmake
    INSTALL_DESTINATION lib/cmake/cxxgen
)

# Install config files
install(
    FILES
       ${CMAKE_CURRENT_BINARY_DIR}/cxxgenConfig.cmake
       ${CMAKE_CURRENT_BINARY_DIR}/cxxgenConfigVersion.cmake
    DESTINATION
        lib/cmake/${PROJECT_NAME}
)

# Exporting Targets from the Build Tree
install(EXPORT cxxgenTargets
    FILE cxxgenTargets.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)
