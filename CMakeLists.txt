cmake_minimum_required(VERSION 2.8.7)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(StockMarketAnalysis)
add_subdirectory(modules)
add_subdirectory(stocks_api)
add_subdirectory(main_project)