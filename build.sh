#!/bin/bash -e
# Build and run script

mkdir -p build && cd build/
cmake ../ && make
echo ""
echo "-----------------------------------------"
echo "Build succeed"
echo "-----------------------------------------"
echo ""

./main_project/StockMarketAnalysis
