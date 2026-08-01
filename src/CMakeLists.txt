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

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(ecomm ${SOURCES})

target_include_directories(ecomm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_precompile_headers(ecomm PRIVATE pch.h)

if(WIN32)
    target_compile_definitions(ecomm PRIVATE UNICODE _UNICODE)

    if(BUILD_SHARED_LIBS)
        target_compile_definitions(ecomm
            PRIVATE ECOMM_BUILD_SHARED
            INTERFACE ECOMM_USE_SHARED
        )
    endif()
endif()

add_library(ecomm::ecomm ALIAS ecomm)