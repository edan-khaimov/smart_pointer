#pragma once

#include "Deleters.h"
#include "isSame.h"
#include "move.h"
#include "removeExtent.h"

template<typename T, typename Deleter = DefaultDelete<T>>
class UniquePtr {
    using U = removeExtentT<T>;

private:
    U* ptr = nullptr;

public:
    UniquePtr() = default;
    explicit UniquePtr(U* ptr);
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr<T, Deleter>& other) = delete;
    UniquePtr(UniquePtr<T, Deleter>&& other) noexcept;
    UniquePtr& operator=(UniquePtr<T, Deleter>&& other) noexcept;
    U& operator*() const
        requires isSameV<T, U>;
    U* operator->() const
        requires isSameV<T, U>;
    U& operator[](size_t index) const
        requires(!isSameV<T, U>);
    explicit operator bool() const;
    Deleter getDeleter() const;
    U* get() const;
    void reset(U* other);
    U* release();
    ~UniquePtr();
};

template<typename T, typename Deleter>
UniquePtr<T, Deleter>::UniquePtr(UniquePtr::U* ptr) : ptr(ptr) {}

template<typename T, typename Deleter>
UniquePtr<T, Deleter>::UniquePtr(UniquePtr<T, Deleter>&& other) noexcept
    : ptr(other.ptr) {
    other.ptr = nullptr;
}

template<typename T, typename Deleter>
UniquePtr<T, Deleter>& UniquePtr<T, Deleter>::operator=(UniquePtr<T, Deleter>&& other) noexcept {
    if (this != &other) {
        getDeleter()(ptr);
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template<typename T, typename Deleter>
typename UniquePtr<T, Deleter>::U& UniquePtr<T, Deleter>::operator*() const
    requires isSameV<T, U>
{
    return *ptr;
}

template<typename T, typename Deleter>
typename UniquePtr<T, Deleter>::U* UniquePtr<T, Deleter>::operator->() const
    requires isSameV<T, U>
{
    return ptr;
}

template<typename T, typename Deleter>
typename UniquePtr<T, Deleter>::U& UniquePtr<T, Deleter>::operator[](size_t index) const
    requires(!isSameV<T, U>)
{
    return ptr[index];
}

template<typename T, typename Deleter>
UniquePtr<T, Deleter>::operator bool() const {
    return ptr;
}

template<typename T, typename Deleter>
Deleter UniquePtr<T, Deleter>::getDeleter() const {
    return Deleter();
}

template<typename T, typename Deleter>
typename UniquePtr<T, Deleter>::U* UniquePtr<T, Deleter>::get() const {
    return ptr;
}

template<typename T, typename Deleter>
typename UniquePtr<T, Deleter>::U* UniquePtr<T, Deleter>::release() {
    U* buf = ptr;
    ptr = nullptr;
    return buf;
}

template<typename T, typename Deleter>
void UniquePtr<T, Deleter>::reset(UniquePtr::U* other) {
    U* oldPtr = ptr;
    ptr = other;
    getDeleter()(oldPtr);
}

template<typename T, typename Deleter>
UniquePtr<T, Deleter>::~UniquePtr() {
    getDeleter()(ptr);
    ptr = nullptr;
}

template<typename T, typename Deleter = DefaultDelete<T>, typename... Args>
UniquePtr<T, Deleter> makeUnique(Args... args)
    requires isSameV<T, removeExtentT<T>>
{
    return UniquePtr<T, Deleter>(new T(forward<Args>(args)...));
}

template<typename T, typename Deleter = DefaultDelete<T>>
UniquePtr<T, Deleter> makeUnique(size_t size)
    requires(!isSameV<T, removeExtentT<T>>)
{
    return UniquePtr<T, Deleter>(new removeExtentT<T>[size]());
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator==(const UniquePtr<T, Deleter>& ptr1, const UniquePtr<T, Deleter>& ptr2) {
    return ptr1.get() == ptr2.get();
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator!=(const UniquePtr<T, Deleter>& ptr1, const UniquePtr<T, Deleter>& ptr2) {
    return ptr1.get() != ptr2.get();
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator==(const UniquePtr<T, Deleter>& ptr, std::nullptr_t) {
    return ptr.get() == nullptr;
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator!=(const UniquePtr<T, Deleter>& ptr, std::nullptr_t) {
    return ptr.get() != nullptr;
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator==(std::nullptr_t, const UniquePtr<T, Deleter>& ptr) {
    return ptr.get() == nullptr;
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator!=(std::nullptr_t, const UniquePtr<T, Deleter>& ptr) {
    return ptr.get() != nullptr;
}