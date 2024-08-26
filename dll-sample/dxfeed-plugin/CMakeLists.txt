# Copyright (c) 2024 Devexperts LLC.
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.25)

project(dllsample-dxfeed-plugin)

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
    IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/DxFeedGraalNativeSdk.lib
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/DxFeedGraalNativeSdk.dll
)

add_library(${PROJECT_NAME} SHARED plugin.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC dllsample-plugin-api)
target_include_directories(${PROJECT_NAME} PUBLIC ../third_party/dxfeed-graal-cxx-api/include)
target_link_libraries(${PROJECT_NAME} PUBLIC dxfcxx dxfcxx::graal)

if (DLLSAMPLE_LINK_PLUGIN_AND_API_STATIC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DLLSAMPLE_EXPORTS)
else ()
    target_compile_definitions(${PROJECT_NAME} PRIVATE DXFCPP_USE_DLLS DLLSAMPLE_EXPORTS)
endif ()

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:dxfcxx::graal>
#        $<TARGET_FILE:dxfcxx>
#        ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/dxfeed-jni-native-sdk-0.1.0.jar
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>)