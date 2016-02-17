//
// Created by leind on 2/17/16.
//

#include "string_util.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>
#include <string>

namespace quote {
    namespace detail {
        namespace string_util {
            // trim functions from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring/217605#217605
            
            // trim from start
            std::string & trimLeft(std::string &s) {
                s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
                return s;
            }
            
            // trim from end
            std::string & trimRight(std::string &s) {
                s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
                return s;
            }
            
            // trim from both ends
            std::string & trim(std::string &s) {
                return trimLeft(trimRight(s));
            }
        }
    }
}