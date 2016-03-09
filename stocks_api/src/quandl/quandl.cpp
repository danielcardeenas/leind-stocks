//
// Created by leind on 26/02/16.
//

#include <cpr/cprtypes.h>
#include <cpr/api.h>
#include <quandl/quandl.h>

leind::quandl::core::core() { }

void leind::quandl::core::auth(std::string authCode)
{
    _authCode = authCode;
}

std::string leind::quandl::core::request(std::string code)
{
    std::string uri = buildRequestUrl(code);
    auto response = cpr::Get(cpr::Url{uri});
    return response.text;
}

std::string leind::quandl::core::request(std::string code, std::string startDate, std::string endDate)
{
    std::string uri = buildRequestUrl(code, startDate, endDate);
    auto response = cpr::Get(cpr::Url{uri});
    return response.text;
}

std::string leind::quandl::core::buildRequestUrl(std::string& code)
{
    std::string uri = _baseUrl + code + ".json?";

    if (_authCode != "")
        uri += "api_key=" + _authCode;

    return uri;
}

std::string leind::quandl::core::buildRequestUrl(std::string& code, std::string& startDate, std::string& endDate)
{
    std::string uri = _baseUrl + code + ".json?";

    if (_authCode != "")
        uri += "api_key=" + _authCode;

    if (startDate != "")
        uri += "&start_date=" + startDate;

    if (endDate != "")
        uri += "&end_date=" + endDate;

    return uri;
}
