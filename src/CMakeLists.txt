set(target_name ecomm)

set(SOURCES
    benchmark.c
    file.c
)

if(WIN32)
    list(APPEND SOURCES
        cmdutils_w.c
        strutils_w.c
        thread_w.c
    )
else()
    list(APPEND SOURCES
        cmdutils_u.c
    )
endif()

file(GLOB PRIVATE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

file(GLOB PUBLIC_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/${PROJECT_NAME}/*.h"
)

add_library(${target_name})

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${PRIVATE_HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/../include/${PROJECT_NAME}
	PREFIX "Public Headers" FILES
		${PUBLIC_HEADERS}
)

target_sources(${target_name}
    PRIVATE
        ${SOURCES}

    PRIVATE
        FILE_SET private_headers
        TYPE HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES ${PRIVATE_HEADERS}

    PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include
        FILES ${PUBLIC_HEADERS}
)

target_include_directories(${target_name}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_precompile_headers(${target_name} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)

if(WIN32)
    target_compile_definitions(${target_name} PRIVATE UNICODE _UNICODE)

    if(BUILD_SHARED_LIBS)
        target_compile_definitions(${target_name}
            PRIVATE ECOMM_BUILD_SHARED
            INTERFACE ECOMM_USE_SHARED
        )
    endif()
endif()

add_library(${target_name}::${target_name} ALIAS ${target_name})