cmake_minimum_required(VERSION 3.21)

if(DEFINED CACHE{CMAKE_BUILD_TYPE})
    set(_BUILD_TYPE_USER_SPECIFIED ON)
else()
    set(_BUILD_TYPE_USER_SPECIFIED OFF)
endif()

project(ecomm VERSION 0.1.0 LANGUAGES C
    DESCRIPTION "eggor's common stuff")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build ecomm as a shared library (ON) or static (OFF)" OFF)

if(CMAKE_CONFIGURATION_TYPES)
    # Multi-config generator.
    # Configuration is selected at build time.
    message(STATUS
        "Configuring multi-config generator: ${CMAKE_GENERATOR}")

else()
    # Single-config generator.
    if(NOT _BUILD_TYPE_USER_SPECIFIED)
        set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Build type"            
        )
        message(STATUS
            "CMAKE_BUILD_TYPE not specified; defaulting to Release")
    endif()

    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        Debug
        Release
        RelWithDebInfo
        MinSizeRel
    )

    message(STATUS
        "Configuring ${CMAKE_BUILD_TYPE} build")

endif()

add_subdirectory(src)

include(CTest)
enable_testing()

if(NOT CMAKE_CROSSCOMPILING)
#    add_subdirectory(tests)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ecomm.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/ecomm.pc
    @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ecomm.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

install(TARGETS ecomm
    EXPORT ecommTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ecommConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ecommConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/ecommConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ecomm
)

install(EXPORT ecommTargets
    FILE ecommTargets.cmake
    NAMESPACE ecomm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ecomm
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ecommConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ecommConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ecomm
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
