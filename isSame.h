#pragma once
#include "removeExtent.h"

template<typename T, typename U>
struct isSame {
    static const bool value = false;
};

template<typename T>
struct isSame<T, T> {
    static const bool value = true;
};

template<typename T, typename U>
const bool isSameV = isSame<T, U>::value;