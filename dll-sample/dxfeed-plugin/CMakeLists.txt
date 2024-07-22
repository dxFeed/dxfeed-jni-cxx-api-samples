# Copyright (c) 2023 Devexperts LLC.
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.25)

project(dllsample-dxfeed-plugin)

add_library(dxfcxx SHARED IMPORTED)
set_target_properties(dxfcxx PROPERTIES
        IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/dxFeedGraalCxxApi.lib
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxFeedGraalCxxApi.dll
)
#
#add_library(dxfcxx::graal SHARED IMPORTED)
#set_target_properties(dxfcxx::graal PROPERTIES
#        IMPORTED_LOCATION ../third_party/dxfeed-graal-cxx-api/bin/DxFeedGraalNativeSdk.dll
#)

add_library(${PROJECT_NAME} SHARED plugin.cpp)

target_link_libraries(${PROJECT_NAME} dllsample-plugin-api)
target_include_directories(${PROJECT_NAME} PUBLIC ../third_party/dxfeed-graal-cxx-api/include)
target_link_libraries(${PROJECT_NAME} dxfcxx)
target_compile_definitions(${PROJECT_NAME} PRIVATE DXFCPP_USE_DLLS DLLSAMPLE_EXPORTS)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:dxfcxx::graal>
#        $<TARGET_FILE:dxfcxx>
#        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxfeed-jni-native-sdk-0.1.0.jar
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>)