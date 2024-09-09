cmake_minimum_required(VERSION 3.25)
project(dllsample)

set(CMAKE_CXX_STANDARD 20)

option(DLLSAMPLE_LINK_PLUGIN_AND_API_STATIC "Link plugin and dxFeed CXX API static" OFF)

add_subdirectory(plugin-api)
add_subdirectory(dxfeed-plugin)
add_subdirectory(sample)

add_dependencies(dllsample-dxfeed-plugin dllsample-plugin-api)
add_dependencies(dllsample-sample dllsample-plugin-api dllsample-dxfeed-plugin)




