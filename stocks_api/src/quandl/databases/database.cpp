//
// Created by leind on 29/02/16.
//

#include "utils.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <quandl/databases/database.h>

//==============================================================================
// SF1 Database only features
//==============================================================================

// Private functions
// =============================================================
std::string leind::database::sf1::_symbolsFile = "sf1_tickers.txt";
std::string leind::database::sf1::_symbolsUrl = "http://www.sharadar.com/meta/tickers.txt";

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
        path = converted + "/stocks_api/src/quandl/databases/" + _symbolsFile;
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

    // Ingore first line
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        std::string data;

        std::getline(linestream, data, '\t');  // read up-to the first tab (discard tab).
        allSymbols.push_back(data);
    }

    return allSymbols;
}

std::vector<Stock> leind::database::sf1::getAllStocks()
{
    std::ifstream file(leind::database::sf1::getFileFromWeb());
    std::string line;
    std::vector<Stock> allSymbols;

    std::string _ticker;
    std::string _name;
    std::string _cusip;
    std::string _isin;
    std::string _currency;
    std::string _sector;
    std::string _industry;

    // Ingore first line
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        std::getline(linestream, _ticker, '\t');
        std::getline(linestream, _name, '\t');
        std::getline(linestream, _cusip, '\t');
        std::getline(linestream, _isin, '\t');
        std::getline(linestream, _currency, '\t');
        std::getline(linestream, _sector, '\t');
        std::getline(linestream, _industry, '\t');

        Stock stock(_ticker, _name, _sector, _industry);
        allSymbols.push_back(stock);
    }

    return allSymbols;
}

//==============================================================================
// WIKI Database only features
//==============================================================================

// Private functions
// =============================================================
std::string leind::database::wiki::_symbolsFile = "wiki-tickers.csv";
std::string leind::database::wiki::_symbolsUrl = "https://s3.amazonaws.com/quandl-static-content/Ticker+CSV%27s/WIKI_tickers.csv";

/**
 * Gets the file from the given directory
 * This shit is "unestable" because you have to change the path if you move the file
 * So use the other method (getFileFromWeb).
 * */
std::string leind::database::wiki::getFilePath()
{
    // Get filepath
    char workingDirectory[1024];
    std::string path;
    if (getcwd(workingDirectory, sizeof(workingDirectory)) != NULL)
    {
        std::string converted(workingDirectory);
        path = converted + "/stocks_api/src/quandl/databases/" + _symbolsFile;
    }

    return path;
}

/**
 * Downloads all companies file [.csv]
 * Saves it with given file name
 * Returns the path of the file
 * */
std::string leind::database::wiki::getFileFromWeb()
{
    return leind::utils::download(_symbolsUrl, _symbolsFile);
}

// Public functions
// =============================================================
std::vector<std::string> leind::database::wiki::getAllSymbols()
{
    std::ifstream file(leind::database::wiki::getFileFromWeb());
    std::string line;
    std::vector<std::string> allSymbols;

    // Ingore first line
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        std::string data;

        std::getline(linestream, data); // Get whole line
        data = data.substr(data.find("/") + 1); // Get everything before "/"
        data = data.substr(0, data.find(",")); // Remove everything after ","

        allSymbols.push_back(data);
    }

    return allSymbols;
}
