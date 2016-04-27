#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/stocks_api/include/)
include_directories(${CPR_INCLUDE_DIRS})
include_directories(${JSON_INCLUDE_DIRS})

set(LIB_FILES
        src/stock.cpp
        include/stock.h
        include/quandl/quandl.h
        src/quandl/quandl.cpp
        include/libstocks.h src/quandl/databases/database.cpp include/quandl/databases/database.h include/utils.h src/quandl/response.cpp include/quandl/response.h)

add_library(stocksApi ${LIB_FILES})
target_link_libraries(stocksApi ${CPR_LIBRARIES})