#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/stocks/include)
include_directories(${PROJECT_SOURCE_DIR}/stocks_api/include)
include_directories(${PROJECT_SOURCE_DIR}/stocks_table/include)

set(SOURCE_FILES src/test.cpp
        src/codes.cpp
        src/symbol.cpp)

add_executable(StockMarketAnalysis ${SOURCE_FILES})
target_link_libraries(StockMarketAnalysis stocksApi stocksTable curl)