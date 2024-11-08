#pragma once
#include "removeExtent.h"
#include "type_traits"


struct trueType {
    static const bool value = true;
    using type = trueType;
};

struct falseType {
    static const bool value = false;
    using type = falseType;
};

template<typename T>
struct isArrayType : falseType {};

template<typename T>
struct isArrayType<T[]> : trueType {};

template<typename T, std::size_t N>
struct isArrayType<T[N]> : trueType {};

template<typename T>
concept isArray = isArrayType<T>::value;