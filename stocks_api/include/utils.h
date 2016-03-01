//
// Created by leind on 29/02/16.
//

#ifndef STOCKMARKETANALYSIS_UTILS_H
#define STOCKMARKETANALYSIS_UTILS_H

#include <iostream>
#include <curl/curl.h>

namespace leind
{
    namespace utils
    {

        static size_t writeData(void *ptr, size_t size, size_t nmemb, FILE *stream)
        {
            size_t written = fwrite(ptr, size, nmemb, stream);
            return written;
        }

        static std::string download(std::string &url, std::string &outName)
        {
            CURL *curl; FILE *fp; CURLcode res;
            curl = curl_easy_init();

            if (curl)
            {
                fp = fopen(outName.c_str(), "wb");
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                res = curl_easy_perform(curl);

                // Cleanup
                curl_easy_cleanup(curl);
                fclose(fp);
            }

            return outName;
        }
    }
}


#endif //STOCKMARKETANALYSIS_UTILS_H
