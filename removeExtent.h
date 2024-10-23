#pragma once

#include <cstddef>

template<class T>
struct removeExtent {
    using type = T;
};

template<class T>
struct removeExtent<T[]> {
    using type = T;
};

template<class T, size_t N>
struct removeExtent<T[N]> {
    using type = T;
};

template<class T>
using removeExtentT = typename removeExtent<T>::type;