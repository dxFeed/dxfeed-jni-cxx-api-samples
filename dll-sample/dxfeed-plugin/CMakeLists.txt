# Copyright (c) 2024 Devexperts LLC.
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.25)

project(dllsample-dxfeed-plugin)

add_library(dxfcxx SHARED IMPORTED)

set_target_properties(dxfcxx PROPERTIES
    IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/Release/dxFeedGraalCxxApi.lib
    IMPORTED_IMPLIB_DEBUG ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/Debug/dxFeedGraalCxxApi.lib
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Release/dxFeedGraalCxxApi.dll
    IMPORTED_LOCATION_DEBUG ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Debug/dxFeedGraalCxxApi.dll
)

add_library(dxfcxx::graal SHARED IMPORTED)

set_target_properties(dxfcxx::graal PROPERTIES
    IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/Release/DxFeedGraalNativeSdk.lib
    IMPORTED_IMPLIB_DEBUG ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/lib/Debug/DxFeedGraalNativeSdk.lib
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Relese/DxFeedGraalNativeSdk.dll
    IMPORTED_LOCATION_DEBUG ${CMAKE_SOURCE_DIR}/third_party/dxfeed-graal-cxx-api/bin/Debug/DxFeedGraalNativeSdk.dll
)

add_library(${PROJECT_NAME} SHARED plugin.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC dllsample-plugin-api)
target_include_directories(${PROJECT_NAME} PUBLIC ../third_party/dxfeed-graal-cxx-api/include)
target_link_libraries(${PROJECT_NAME} PUBLIC dxfcxx dxfcxx::graal)

target_compile_definitions(${PROJECT_NAME} PRIVATE DXFCPP_USE_DLLS DLLSAMPLE_EXPORTS)
