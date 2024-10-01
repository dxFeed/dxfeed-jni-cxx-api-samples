# Copyright (c) 2024 Devexperts LLC.
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.25)

project(dllsample-sample)

set(CMAKE_C_STANDARD 11)

add_library(dxfcxx SHARED IMPORTED)

set_target_properties(dxfcxx PROPERTIES
        IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/Release/dxFeedGraalCxxApi.lib
        IMPORTED_IMPLIB_DEBUG ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/Debug/dxFeedGraalCxxApi.lib
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Release/dxFeedGraalCxxApi.dll
        IMPORTED_LOCATION_DEBUG ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Debug/dxFeedGraalCxxApi.dll
)

add_library(dxfcxx::graal SHARED IMPORTED)

set_target_properties(dxfcxx::graal PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Release/DxFeedGraalNativeSdk.dll
        IMPORTED_LOCATION_DEBUG ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Debug/DxFeedGraalNativeSdk.dll
)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} dllsample-plugin-api)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:dllsample-dxfeed-plugin>
        $<TARGET_FILE:dxfcxx::graal>
        $<TARGET_FILE:dxfcxx>
        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxfeed-jni-native-sdk-0.1.0.jar
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND if $<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>==1 (
        "${CMAKE_COMMAND}" -E copy_if_different
        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Debug/dxFeedGraalCxxApi.pdb
        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Debug/DxFeedGraalNativeSdk.pdb
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
)