#pragma once

#include "utility"
#include <stdexcept>

template<typename T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(size_t index) const = 0;
    [[nodiscard]] virtual size_t GetLength() const = 0;
    virtual Sequence<T>* Append(T& item) = 0;
    virtual Sequence<T>* Prepend(T& item) = 0;
    virtual Sequence<T>* InsertAt(T& item, size_t& index) = 0;
    virtual Sequence<T>* GetSubSequence(size_t& startIndex, size_t& endIndex) const = 0;
    virtual Sequence<T>* Concat(Sequence<T>& seq) = 0;
    virtual ~Sequence() = 0;

    T& operator[](size_t& index) {
        if (index < 0 || index >= GetLength()) {
            throw std::out_of_range("Index out of range");
        }
        return Get(index);
    }

    bool operator==(const Sequence<T>& seq) {
        if (GetLength() != seq.GetLength()) {
            return false;
        }
        for (size_t i = 0; i < GetLength(); i++) {
            if (*this[i] != seq[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Sequence<T>& seq) {
        return !(*this == seq);
    }
};