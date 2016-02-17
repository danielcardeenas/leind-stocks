//
// Created by leind on 2/17/16.
//

#include "curl_util.h"
#include "exception/exception.h"

namespace quote {
    namespace detail {
        namespace curl_util {
            std::shared_ptr<CURL> createCurlHandle() {
                std::shared_ptr<CURL> curlHandle(curl_easy_init(), curl_easy_cleanup);
                if (curlHandle.get() == nullptr) {
                    throw exception::LogicException(__FILE__, __LINE__, __func__, "curl_easy_init() failure");
                }
                return curlHandle;
            };

            void perform(CURL *handle) {
                CURLcode code = curl_easy_perform(handle);
                if (code != CURLE_OK) {
                    throw exception::LogicException(__FILE__, __LINE__, __func__, std::string("curl_easy_perform error: ") + curl_easy_strerror(code));
                }
            }
            
            size_t writeToStringCallBack(void *buffer, size_t size, size_t nmemb, void *string) {
                const size_t sizeInBytes = size*nmemb;
                static_cast<std::string *>(string)->append(static_cast<const char * >(buffer), sizeInBytes);
                return sizeInBytes;
            }
            
            std::string getUrlData(const std::string url) {
                std::shared_ptr<CURL> curlHandle = detail::curl_util::createCurlHandle();
                detail::curl_util::setOpt(curlHandle.get(), CURLOPT_URL, url.c_str());
                detail::curl_util::setOpt(curlHandle.get(), CURLOPT_FOLLOWLOCATION, 1L);
                std::string data;
                detail::curl_util::setOpt(curlHandle.get(), CURLOPT_NOBODY, 0L);
                detail::curl_util::setOpt(curlHandle.get(), CURLOPT_WRITEDATA, &data);
                detail::curl_util::setOpt(curlHandle.get(), CURLOPT_WRITEFUNCTION, detail::curl_util::writeToStringCallBack);
                detail::curl_util::perform(curlHandle.get());
                return std::move(data);
            }
        }
    }
}
