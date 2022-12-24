#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"

#ifndef UTILITIES_MAPUTILS_H
#define UTILITIES_MAPUTILS_H

namespace Delynoi {
    namespace map_utils {
        struct GetKeys {
            template<typename T>
            typename T::first_type operator()(T keyValuePair) const {
                return keyValuePair.first;
            }
        };

        struct GetValues {
            template<typename T>
            typename T::first_type operator()(T keyValuePair) const {
                return keyValuePair.second;
            }
        };
    }
}

#endif
#pragma clang diagnostic pop
