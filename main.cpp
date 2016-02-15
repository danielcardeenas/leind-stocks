/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include "stocks/codes.h"

using namespace std;

int main() {
    for (auto &code : Codes::stocks)
    {
        cout << code << endl;
    }

    return 0;
}