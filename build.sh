#!/bin/bash -e
# Build and run script

mkdir -p build && cd build/
/usr/local/Cellar/cmake/3.5.0/bin/cmake ../ && make
echo ""
echo "-----------------------------------------"
echo "Build succeed"
echo "-----------------------------------------"
echo ""

./main_project/StockMarketAnalysis
