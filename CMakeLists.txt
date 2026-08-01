cmake_minimum_required(VERSION 3.21)

set(USER_SPECIFIED_BUILD_TYPE OFF)
if(DEFINED CACHE{CMAKE_BUILD_TYPE})
	set(USER_SPECIFIED_BUILD_TYPE ON)
endif()

project(ecomm VERSION 0.1.0 LANGUAGES C
	DESCRIPTION "eggor's common stuff"
)

if(WIN32 AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(_default_prefix "$ENV{ProgramW6432}/${PROJECT_NAME}")
	else()
		set(_default_prefix "$ENV{ProgramFiles(x86)}/${PROJECT_NAME}")
	endif()

	file(TO_CMAKE_PATH "${_default_prefix}" _default_prefix)

	set(CMAKE_INSTALL_PREFIX
		"${_default_prefix}"
		CACHE PATH "Install prefix" FORCE
	)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS
	"Build ecomm as a shared library (ON) or static (OFF)"
	OFF
)

if(CMAKE_CONFIGURATION_TYPES)
	message(STATUS
		"Configuring multi-config generator: ${CMAKE_GENERATOR}")
else()
	if(NOT USER_SPECIFIED_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)

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
	add_subdirectory(tests)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/ecomm.pc.in
	${CMAKE_CURRENT_BINARY_DIR}/ecomm.pc
	@ONLY
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/ecomm.pc
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

install(TARGETS ecomm
	EXPORT ecommTargets

	FILE_SET public_headers
		DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"

	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
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

install(
	EXPORT ecommTargets
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