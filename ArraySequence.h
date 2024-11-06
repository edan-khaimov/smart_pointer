#pragma once
#include "UniquePtr.h"
#include <stdexcept>

template<typename T>
class ArraySequence {
private:
    size_t size;
    size_t capacity;
    UniquePtr<T[]> data;

    void Resize(size_t newCapacity) {
        auto newData = makeUnique<T[]>(newCapacity);
        for (size_t i = 0; i < size; i++) {
            newData[i] = move(data[i]);
        }
        data = move(newData);
        capacity = newCapacity;
    }

public:
    ArraySequence() : size(0), capacity(1), data(makeUnique<T[]>(capacity)) {}

    explicit ArraySequence(size_t size) : size(size), capacity(size + 1), data(makeUnique<T[]>(capacity)) {}

    ArraySequence(const UniquePtr<T[]>& items, size_t size) : ArraySequence(size) {
        for (size_t i = 0; i < size; i++) {
            data[i] = items[i];
        }
    }

    ArraySequence(UniquePtr<T[]>&& items, size_t size) : size(size), capacity(size), data(move(items)) {}

    ArraySequence(const ArraySequence<T>& other) : ArraySequence(other.data, other.size) {}

    ArraySequence(ArraySequence<T>&& other) noexcept : ArraySequence(move(other.data), other.size) {
        other.size = 0;
        other.capacity = 1;
    }

    T Get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Invalid index");
        }
        return data[index];
    }

    [[nodiscard]] size_t GetLength() const {
        return size;
    }

    T GetFirst() const {
        return Get(0);
    }

    T GetLast() const {
        return Get(size - 1);
    }

    ArraySequence<T>& Append(const T& item) {
        if (size == capacity) {
            Resize(capacity * 2);
        }
        data[size++] = item;
        return *this;
    }

    ArraySequence<T>& Prepend(const T& item) {
        if (size == capacity) {
            Resize(capacity * 2);
        }
        for (size_t i = size; i > 0; i--) {
            data[i] = move(data[i - 1]);
        }
        data[0] = item;
        ++size;
        return *this;
    }

    ArraySequence<T>& InsertAt(const T& item, const size_t& index) {
        if (size == capacity) {
            Resize(capacity * 2);
        }
        for (size_t i = index; i < ++size; i++) {
            data[i + 1] = move(data[i]);
        }
        data[index] = item;
        return *this;
    }

    T& operator[](const size_t& index) {
        return data[index];
    }

    ~ArraySequence() = default;
};