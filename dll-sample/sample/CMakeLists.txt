# Copyright (c) 2024 Devexperts LLC.
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.25)

project(dllsample-sample)

set(CMAKE_C_STANDARD 11)

if (DLLSAMPLE_LINK_PLUGIN_AND_API_STATIC)
    add_library(dxfcxx STATIC IMPORTED)

    set_target_properties(dxfcxx PROPERTIES
            IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxFeedGraalCxxApi_static.lib
    )
else ()
    add_library(dxfcxx SHARED IMPORTED)

    set_target_properties(dxfcxx PROPERTIES
            IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/dxFeedGraalCxxApi.lib
            IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxFeedGraalCxxApi.dll
    )
endif ()

add_library(dxfcxx::graal SHARED IMPORTED)
set_target_properties(dxfcxx::graal PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/DxFeedGraalNativeSdk.dll
)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} dllsample-plugin-api)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:dllsample-dxfeed-plugin>
        $<TARGET_FILE:dxfcxx::graal>
        $<TARGET_FILE:dxfcxx>
        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxfeed-jni-native-sdk-0.1.0.jar
        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxFeedGraalCxxApi.pdb
        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/DxFeedGraalNativeSdk.pdb
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)