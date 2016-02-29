#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/stocks_api/include/)

set(LIB_FILES
        src/stock.cpp
        src/quandl/databases/database.h
        src/quandl/quandl.h
        src/quandl/quandl.cpp)

add_library(stocksApi ${LIB_FILES})