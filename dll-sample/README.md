# dxFeed Graal CXX API DLL Sample

## Project Info

The project consists of 4 parts:
1) `plugin-api`: contains header files that describe data structures and event identifiers that will be passed from the plugin to the application, as well as prototypes of functions exported by the plugin.
2) `dxfeed-plugin`: a plugin implementation that uses the dxFeed Graal CXX API to access exchange data. The plugin implements the functions according to `plugin-api`.
3) `sample`: a sample application that loads the `plugin` using `LoadLibrary`, accesses the functions exported by the plugin and uses the plugin to subscribe to exchange data.
4) `third_party`: contains libraries `dxFeedGraalCxxApi.dll`, `DxFeedGraalNativeSdk.dll`, `dxfeed-jni-native-sdk-0.1.0.jar`, include header files of dxFeed Graal CXX API and 8 JDK x86-32:
    - `dxfeed-jni-native-sdk-0.1.0.jar` contains the necessary parts of the dxFeed Java API and wrappers to access them via the JNI mechanism.
    - `DxFeedGraalNativeSdk.dll` (this is a renamed `DxFeedJniNativeSdk.dll`) contains wrappers to provide unified access to the dxFeed Java API through the generalized GraalVM/JNI interface and mimics the dxFeed Graal Native SDK by converting GraalVM calls into JNI calls.
    - `dxFeedGraalCxxApi.dll` contains wrappers to work with the dxFeed API, using C++\C classes and functions, as well as the memory model and multi-threading.
    - The JDK is used to handle `dxfeed-jni-native-sdk-0.1.0.jar` from `DxFeedGraalNativeSdk.dll`.

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
- Change the directory to the directory where `dllsample-sample.exe` is located. Set JAVA_HOME. Run `dllsample-sample.exe` 
```shell
@cd <PATH_TO_DIR_WHERE_SAMPLE_IS_LOCATED>
@set JAVA_HOME=<PATH_TO_JDK>
dllsample-sample.exe
```

or

- Install JDK 8 x86_32 globally
- Change the directory to the directory where `dllsample-sample.exe` is located and run it.
```shell
@cd <PATH_TO_DIR_WHERE_SAMPLE_IS_LOCATED>
dllsample-sample.exe
```

## Run the pre-built program

```shell
./bin/run.cmd
```

or

```shell
./bin/run.cmd demo.dxfeed.com:7300 AAPL
```

Output:

```shell
Connecting to demo.dxfeed.com:7300
Use JAVA_HOME from ENV: C:\w\dxfeed-jni-cxx-api-samples\dll-sample\bin\..\third_party\dxfeed-graal-cxx-api\jdk\zulu8.80.0.17-ca-jdk8.0.422-win_i686
APP_RUNTIME_PATH: "C:\\w\\dxfeed-jni-cxx-api-samples\\dll-sample\\bin"
DxFeed JAR path: "C:\\w\\dxfeed-jni-cxx-api-samples\\dll-sample\\bin\\dxfeed-jni-native-sdk-0.1.0.jar"
Run cmd "java -Djava.class.path=C:\w\dxfeed-jni-cxx-api-samples\dll-sample\bin\dxfeed-jni-native-sdk-0.1.0.jar;C:\w\dxfeed-jni-cxx-api-samples\dll-sample\bin"
I 241001 154808.467 [main] QD - Using QDS-UNKNOWN, (C) Devexperts
I 241001 154808.532 [main] QD - Using scheme com.dxfeed.api.impl.DXFeedScheme Ao7i0mLrB7RbnGZ43PGWcWWLGeKJ79lOVlbtAxAaXTI
I 241001 154808.597 [main] MARS - Started JVM self-monitoring
I 241001 154809.117 [main] QD - monitoring with collectors [Ticker, Stream, History]
I 241001 154809.237 [main] ClientSocket-Distributor - Starting ClientSocketConnector to demo.dxfeed.com:7300
Subscribing to AAPL
I 241001 154809.240 [demo.dxfeed.com:7300-Reader] ClientSocketConnector - Resolving IPs for demo.dxfeed.com
I 241001 154809.295 [demo.dxfeed.com:7300-Reader] ClientSocketConnector - Connecting to 208.93.103.170:7300
I 241001 154809.298 [demo.dxfeed.com:7300-Reader] ClientSocketConnector - Connected to 208.93.103.170:7300
D 241001 154809.715 [demo.dxfeed.com:7300-Reader] QD - Distributor received protocol descriptor multiplexor@nYDlu [type=qtp, version=QDS-3.327, opt=hs, mars.root=mdd.demo-amazon.multiplexor-demo1] sending [TICKER, STREAM, HISTORY, DATA] from 208.93.103.170
Quote{AAPL, bid_price = 229.9, bid_size = 3, ask_price = 230.04, ask_size = 1}
Trade{AAPL, price = 233, size = nan, dayVolume = 1086442}
Trade{AAPL, price = 233, size = nan, dayVolume = 1086484}
Quote{AAPL, bid_price = 229.9, bid_size = 3, ask_price = 229.99, ask_size = 1}
Quote{AAPL, bid_price = 229.9, bid_size = 3, ask_price = 230.04, ask_size = 1}
Trade{AAPL, price = 233, size = nan, dayVolume = 1086489}
Trade{AAPL, price = 233, size = nan, dayVolume = 1086496}
```