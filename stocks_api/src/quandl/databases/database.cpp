//
// Created by playfulplay on 29/02/16.
//

#include "utils.h"
#include <fstream>
#include <sstream>
#include <quandl/databases/database.h>

std::string _symbolsFile = "sf1_tickers.txt";
std::string _symbolsUrl = "http://www.sharadar.com/meta/tickers.txt";

// Private functions
// =============================================================

/**
 * Gets the file from the given directory
 * This shit is "unestable" because you have to change the path if you move the file
 * So use the other method (getFileFromWeb).
 * */
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

/**
 * Downloads all companies file [.txt]
 * Saves it with given file name
 * Returns the path of the file
 * */
std::string leind::database::sf1::getFileFromWeb()
{
    return leind::utils::download(_symbolsUrl, _symbolsFile);
}

// Public functions
// =============================================================
std::vector<std::string> leind::database::sf1::getAllSymbols()
{
    std::ifstream file(getFileFromWeb());
    std::string line;
    std::vector<std::string> allSymbols;

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        std::string data;

        std::getline(linestream, data, '\t');  // read up-to the first tab (discard tab).
        allSymbols.push_back(data);
    }

    return allSymbols;
}