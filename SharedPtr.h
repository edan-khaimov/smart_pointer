#pragma once

#include "Deleters.h"
#include "isSame.h"
#include "move.h"
#include "removeExtent.h"

struct ControlBlock {
    size_t strongCount;
    size_t weakCount;
};

template<typename T, typename Deleter = DefaultDelete<T>>
class WeakPtr;

template<typename T, typename Deleter = DefaultDelete<T>>
class SharedPtr {
    using U = removeExtentT<T>;

private:
    U* ptr = nullptr;
    ControlBlock* cb = nullptr;
    void release();
    friend class WeakPtr<T, Deleter>;
public:
    SharedPtr() = default;
    explicit SharedPtr(U* ptr);
    explicit SharedPtr(const WeakPtr<U, Deleter>& weak);
    SharedPtr(const SharedPtr& other);
    SharedPtr& operator=(const SharedPtr<T, Deleter>& other);
    SharedPtr(SharedPtr<T, Deleter>&& other) noexcept;
    SharedPtr& operator=(SharedPtr<T, Deleter>&& other) noexcept;
    U& operator*() const
        requires isSameV<T, U>;
    U* operator->() const
        requires isSameV<T, U>;
    U& operator[](size_t index) const
        requires(!isSameV<T, U>);
    explicit operator bool() const;
    Deleter getDeleter() const;
    const U* get() const;
    void reset();
    void reset(U* newPtr);
    [[nodiscard]] size_t getUsageCount() const;
    [[nodiscard]] bool isUnique() const;
    ~SharedPtr();
};

template<typename T, typename Deleter>
void SharedPtr<T, Deleter>::release() {
    if (cb) {
        if (--(cb->strongCount) == 0) {
            getDeleter()(ptr);
            ptr = nullptr;
            if (cb->weakCount == 0) {
                delete cb;
            }
        }
    }
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>::SharedPtr(SharedPtr::U* ptr) : ptr(ptr) {
    if (ptr) {
        cb = new ControlBlock{1, 0};
    } else {
        cb = nullptr;
    }
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>::SharedPtr(const WeakPtr<U, Deleter>& weak) : ptr(weak.ptr), cb(weak.cb) {
    if (cb) {
        ++(cb->strongCount);
    }
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>::SharedPtr(const SharedPtr& other) : ptr(other.ptr), cb(other.cb) {
    if (cb) {
        ++(cb->strongCount);
    }
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>& SharedPtr<T, Deleter>::operator=(const SharedPtr<T, Deleter>& other) {
    if (this != &other) {
        release();
        ptr = other.ptr;
        cb = other.cb;
        if (cb) {
            ++(cb->strongCount);
        }
    }
    return *this;
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>::SharedPtr(SharedPtr<T, Deleter>&& other) noexcept : ptr(other.ptr), cb(other.cb) {
    other.ptr = nullptr;
    other.cb = nullptr;
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>& SharedPtr<T, Deleter>::operator=(SharedPtr<T, Deleter>&& other) noexcept {
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
typename SharedPtr<T, Deleter>::U& SharedPtr<T, Deleter>::operator*() const
    requires isSameV<T, U>
{
    return *ptr;
}

template<typename T, typename Deleter>
typename SharedPtr<T, Deleter>::U* SharedPtr<T, Deleter>::operator->() const
    requires isSameV<T, U>
{
    return ptr;
}

template<typename T, typename Deleter>
typename SharedPtr<T, Deleter>::U& SharedPtr<T, Deleter>::operator[](size_t index) const
    requires(!isSameV<T, U>)
{
    return ptr[index];
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>::operator bool() const {
    return ptr;
}

template<typename T, typename Deleter>
Deleter SharedPtr<T, Deleter>::getDeleter() const {
    return Deleter();
}

template<typename T, typename Deleter>
const typename SharedPtr<T, Deleter>::U* SharedPtr<T, Deleter>::get() const {
    return ptr;
}

template<typename T, typename Deleter>
void SharedPtr<T, Deleter>::reset() {
    release();
    ptr = nullptr;
    cb = nullptr;
}

template<typename T, typename Deleter>
void SharedPtr<T, Deleter>::reset(SharedPtr::U* newPtr) {
    release();
    ptr = newPtr;
    if (newPtr) {
        cb = new ControlBlock{1, 0};
    }
}

template<typename T, typename Deleter>
size_t SharedPtr<T, Deleter>::getUsageCount() const {
    if (cb) {
        return cb->strongCount;
    }
    return 0;
}

template<typename T, typename Deleter>
bool SharedPtr<T, Deleter>::isUnique() const {
    return cb->strongCount == 1;
}

template<typename T, typename Deleter>
SharedPtr<T, Deleter>::~SharedPtr() {
    release();
}

template<typename T, typename Deleter = DefaultDelete<T>, typename... Args>
SharedPtr<T, Deleter> makeShared(Args... args)
    requires isSameV<T, removeExtentT<T>>
{
    return SharedPtr<T, Deleter>(new T(forward<Args>(args)...));
}

template<typename T, typename Deleter = DefaultDelete<T>>
SharedPtr<T, Deleter> makeShared(size_t size)
    requires(!isSameV<T, removeExtentT<T>>)
{
    return SharedPtr<T, Deleter>(new removeExtentT<T>[size]());
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator==(const SharedPtr<T, Deleter>& ptr1, const SharedPtr<T, Deleter>& ptr2) {
    return ptr1.get() == ptr2.get();
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator!=(const SharedPtr<T, Deleter>& ptr1, const SharedPtr<T, Deleter>& ptr2) {
    return ptr1.get() != ptr2.get();
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator==(const SharedPtr<T, Deleter>& ptr, std::nullptr_t) {
    return ptr.get() == nullptr;
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator!=(const SharedPtr<T, Deleter>& ptr, std::nullptr_t) {
    return ptr.get() != nullptr;
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator==(std::nullptr_t, const SharedPtr<T, Deleter>& ptr) {
    return ptr.get() == nullptr;
}

template<typename T, typename Deleter = DefaultDelete<T>>
bool operator!=(std::nullptr_t, const SharedPtr<T, Deleter>& ptr) {
    return ptr.get() != nullptr;
}