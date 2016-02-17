cmake_minimum_required(VERSION 3.3)
project(StockMarketAnalysis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        stocks/codes.cpp stocks/codes.h
        stocks/symbol.cpp stocks/symbol.h
        table/table_printer.cpp
        table/table_printer.h)

add_executable(StockMarketAnalysis ${SOURCE_FILES})