#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(include/)

set(LIB_FILES
        src/stocks_table.cpp)

add_library(stocksTable ${LIB_FILES})