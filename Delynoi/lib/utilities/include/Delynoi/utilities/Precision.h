#ifndef UTILITIES_PRECISION_H
#define UTILITIES_PRECISION_H

// ReSharper disable once CppEnforceNestedNamespacesStyle
namespace Delynoi { // Nested namespaces requires C++ std17. This is 14+ NOLINT(*-concat-nested-namespaces)
    namespace Precision {
        enum precision {
            small = 6,
            mid = 10,
            large = 16
        };
    } // namespace Precision
} // namespace Delynoi

#endif
