//
// Created by leind on 2/17/16.
//

#ifndef STOCKMARKETANALYSIS_EXCEPTION_H
#define STOCKMARKETANALYSIS_EXCEPTION_H

#include <stdexcept>
#include <string>
#include <type_traits>

namespace exception {
    template<typename T>
    class Exception : public T {
        static_assert(std::is_base_of<std::exception, T>::value == true,
                      "exception::Exception<T>: typename T must be derived from std::exception");

    public:
        Exception(const std::string &fileName,
                  unsigned lineNumber,
                  const std::string &functionName,
                  const std::string &errorMessage);
    };

    using RuntimeException = Exception<std::runtime_error>;
    using LogicException = Exception<std::logic_error>;

    template<typename T>
    Exception<T>::Exception(const std::string &fileName,
                            unsigned lineNumber,
                            const std::string &functionName,
                            const std::string &errorMessage) : T(errorMessage + " at " + fileName + ":" + std::to_string(lineNumber) + ":(" + functionName + ")") {}
}

#endif //STOCKMARKETANALYSIS_EXCEPTION_H
