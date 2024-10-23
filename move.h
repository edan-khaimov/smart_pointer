#pragma once

template<class T>
struct remove_reference {
    using type = T;
};
template<class T>
struct remove_reference<T&> {
    using type = T;
};
template<class T>
struct remove_reference<T&&> {
    using type = T;
};

template<typename T>
typename remove_reference<T>::type&& move(T&& arg) noexcept {
    return static_cast<typename remove_reference<T>::type&&>(arg);
}

template<typename T>
T&& forward(typename remove_reference<T>::type& arg) noexcept {
    return static_cast<T&&>(arg);
}

template<typename T>
T&& forward(typename remove_reference<T>::type&& arg) noexcept {
    return static_cast<T&&>(arg);
}