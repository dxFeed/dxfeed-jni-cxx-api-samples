# dxFeed Graal CXX API DLL Sample

## Prerequisites

- Visual Studio 2019 and higher
- JDK 8 x86_32 [Download](https://cdn.azul.com/zulu/bin/zulu8.80.0.17-ca-jdk8.0.422-win_i686.zip)
- CMake

## Installation

- Open Visual Studio
- File -> Open -> CMake
- `dll-sample/CMakeLists.txt`
- Project -> CMake settings for `dllsample`
- Change the Configuration name to `x86-Release`. Change the Configuration type to `Release` and Toolset to `msvc_x86`
- Ctrl+S


## Build

- Select Startup Project `dllsample-sample.exe`
- Build

## Run

- Extract JDK 8 somewhere
- Change the directory to the directory where `dllsample-sample.exe` is located. Set JAVA_HOME, PATH, CLASSPATH. Run `dllsample-sample.exe` 
```shell
@ cd <PATH_TO_DIR_WHERE_SAMPLE_IS_LOCATED>
@set JAVA_HOME=<PATH_TO_JDK>
@set PATH=%JAVA_HOME%;%PATH%
@set CLASSPATH=.;dxfeed-jni-native-sdk-0.1.0.jar;%JAVA_HOME%\jre\lib;%JAVA_HOME%\lib
dllsample-sample.exe
```

or

- Install JDK 8 x86_32 globally
- Change the directory to the directory where `dllsample-sample.exe` is located and run it.
```shell
@ cd <PATH_TO_DIR_WHERE_SAMPLE_IS_LOCATED>
dllsample-sample.exe
```