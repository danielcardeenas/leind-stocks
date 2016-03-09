#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/stocks_api/include)
include_directories(../modules/stocks_table/include)
include_directories(${CPR_INCLUDE_DIRS})
include_directories(${JSON_INCLUDE_DIRS})

set(SOURCE_FILES src/test.cpp src/canslim/canslim.h src/model/quarter.h src/canslim/utils.h src/canslim/canslim.cpp)

add_executable(StockMarketAnalysis ${SOURCE_FILES})
target_link_libraries(StockMarketAnalysis stocksApi stocksTable ${CPR_LIBRARIES})