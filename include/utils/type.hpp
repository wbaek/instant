#ifndef __UTILS_TYPE_HPP__
#define __UTILS_TYPE_HPP__

#include <string>
#include <stdlib.h>
#include <cxxabi.h>

namespace instant {
    namespace Utils {
        class Type {
            public:
                // https://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-type-util.h#60
                // GetTypeName<T>() returns a human-readable name of type T.
                template <typename T>
                static const std::string GetTypeName() {
                    const char* const name = typeid(T).name();
                    return Demangle(name);
                }
                
                template <typename T>
                static const std::string GetTypeName(T* type) {
                    const char* const name = typeid(*type).name();
                    return Demangle(name);
                }

                static const std::string Demangle(const char* name) {
                    int status = 0;
                    // gcc's implementation of typeid(T).name() mangles the type name,
                    // so we have to demangle it.
                    char* const readable_name = abi::__cxa_demangle(name, 0, 0, &status);
                    const std::string name_str(status == 0 ? readable_name : name);
                    free(readable_name);
                    return name_str;
                }
         };
    }
}

#endif // __UTILS_TYPE_HPP__
