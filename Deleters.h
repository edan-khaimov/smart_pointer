#pragma once

template <typename T>
struct DefaultDelete {
    void operator()(T* ptr) const;
};

template <typename T>
struct DefaultDelete<T[]> {
    void operator()(T* ptr) const;
};

template <typename T>
void DefaultDelete<T>::operator()(T* ptr) const {
    delete ptr;
}

template <typename T>
void DefaultDelete<T[]>::operator()(T* ptr) const {
    delete[] ptr;
}