#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/stocks_api/include/)

set(LIB_FILES
        src/stock.cpp
        src/libs/quandl/quandl.cpp
        src/libs/quandl/quandl.h
        src/libs/json/json.h src/libs/quandl/databases/database.h)

add_library(stocksApi ${LIB_FILES})