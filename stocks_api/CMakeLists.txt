#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/stocks_api/include/)

set(LIB_FILES
        src/conversion.cpp
        src/core.cpp
        src/curl_util.cpp
        src/string_util.cpp
        src/exception/exception.h)

add_library(stocksApi ${LIB_FILES})