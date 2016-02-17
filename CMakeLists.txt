cmake_minimum_required(VERSION 2.8.7)
project(StockMarketAnalysis)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(SOURCE_FILES main.cpp
        stocks/codes.cpp stocks/codes.h
        stocks/symbol.cpp stocks/symbol.h
        table/table_printer.cpp
        table/table_printer.h)

add_executable(StockMarketAnalysis ${SOURCE_FILES})