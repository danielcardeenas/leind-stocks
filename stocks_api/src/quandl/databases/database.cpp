//
// Created by playfulplay on 29/02/16.
//

#include "database.h"
#include <fstream>
#include <sstream>

const std::string _symbolsFile = "databases/sf1_tickers.txt";
const std::string _symbolsUrl = "http://www.sharadar.com/meta/tickers.txt";

std::string leind::database::sf1::getFilePath()
{
    // Get filepath
    char workingDirectory[1024];
    std::string path;
    if (getcwd(workingDirectory, sizeof(workingDirectory)) != NULL)
    {
        std::string converted(workingDirectory);
        path = converted + "/stocks_api/src/quandl/databases/sf1_tickers.txt";
    }

    return path;
}

std::vector<std::string> leind::database::sf1::getAllSymbols()
{
    std::ifstream file(getFilePath());
    std::string line;
    std::vector<std::string> allSymbols;

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        std::string data;

        // If you have truly tab delimited data use getline() with third parameter.
        // If your data is just white space separated data
        // then the operator >> will do (it reads a space separated word into a string).
        std::getline(linestream, data, '\t');  // read up-to the first tab (discard tab).
        allSymbols.push_back(data);
    }

    return allSymbols;
}