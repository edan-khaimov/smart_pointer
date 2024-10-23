#pragma once

#include "Deleters.h"
#include "removeExtent.h"
#include "SharedPtr.h"

template<typename T, typename Deleter>
class WeakPtr {
    using U = removeExtentT<T>;

private:
    U* ptr = nullptr;
    ControlBlock* cb = nullptr;

    void release();
    friend class SharedPtr<T, Deleter>;
public:
    WeakPtr() = default;
    explicit WeakPtr(SharedPtr<T, Deleter>& shared);
    WeakPtr(const WeakPtr<T, Deleter>& other);
    WeakPtr& operator=(const WeakPtr<T, Deleter>& other);
    WeakPtr(WeakPtr<T, Deleter>&& other) noexcept;
    WeakPtr& operator=(WeakPtr<T, Deleter>&& other) noexcept;
    void reset();
    [[nodiscard]] bool isExpired() const;
    SharedPtr<T, Deleter> lock() const;
    size_t getUsageCount() const;
    ~WeakPtr();
};

template<typename T, typename Deleter>
void WeakPtr<T, Deleter>::release() {
    if (cb) {
        if (--cb->weakCount == 0 && cb->strongCount == 0) {
            delete cb;
        }
    }
}

template<typename T, typename Deleter>
WeakPtr<T, Deleter>::WeakPtr(SharedPtr<T, Deleter>& shared) : ptr(shared.ptr), cb(shared.cb) {
    if (cb) {
        ++(cb->weakCount);
    }
}

template<typename T, typename Deleter>
WeakPtr<T, Deleter>::WeakPtr(const WeakPtr<T, Deleter>& other) : ptr(other.ptr), cb(other.cb) {
    if (cb) {
        ++(cb->weakCount);
    }
}

template<typename T, typename Deleter>
WeakPtr<T, Deleter>& WeakPtr<T, Deleter>::operator=(const WeakPtr<T, Deleter>& other) {
    if (this != &other) {
        release();
        ptr = other.ptr;
        cb = other.cb;
        if (cb) {
            ++(cb->weakCount);
        }
    }
    return *this;
}

template<typename T, typename Deleter>
WeakPtr<T, Deleter>::WeakPtr(WeakPtr<T, Deleter>&& other) noexcept : ptr(other.ptr), cb(other.cb) {
    other.ptr = nullptr;
    other.cb = nullptr;
}

template<typename T, typename Deleter>
WeakPtr<T, Deleter>& WeakPtr<T, Deleter>::operator=(WeakPtr<T, Deleter>&& other) noexcept {
    if (this != &other) {
        release();
        ptr = other.ptr;
        cb = other.cb;
        other.cb = nullptr;
        other.ptr = nullptr;
    }
    return *this;
}

template<typename T, typename Deleter>
void WeakPtr<T, Deleter>::reset() {
    release();
    ptr = nullptr;
    cb = nullptr;
}

template<typename T, typename Deleter>
bool WeakPtr<T, Deleter>::isExpired() const {
    if (cb) {
        return cb->strongCount == 0;
    }
    return false;
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter> WeakPtr<T, Deleter>::lock() const {
    return SharedPtr<T, Deleter>(*this);
}

template<typename T, typename Deleter>
size_t WeakPtr<T, Deleter>::getUsageCount() const {
    if (cb) {
        return cb->weakCount;
    }
    return 0;
}

template<typename T, typename Deleter>
WeakPtr<T, Deleter>::~WeakPtr() {
    release();
}
