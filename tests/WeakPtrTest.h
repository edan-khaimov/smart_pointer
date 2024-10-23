#pragma once
#include "../WeakPtr.h"
#include <cassert>

void testWeakPtrCtors() {
    auto a = WeakPtr<int>();
    auto b = SharedPtr<int>(new int(9));
    auto c = WeakPtr<int>(b);
    assert(c.getUsageCount() == 1);
};

void testWeakPtrCopyCtor() {
    auto b = SharedPtr<int>(new int(9));
    auto c = WeakPtr<int>(b);
    WeakPtr<int> d = c;
    assert(c.getUsageCount() == 2);
}

void testWeakPtrMoveCtor() {
    auto b = SharedPtr<int>(new int(9));
    auto c = WeakPtr<int>(b);
    WeakPtr<int> d = move(c);
    assert(d.getUsageCount() == 1);
}

void testWeakPtrCopyAssignmentOperator() {
    auto b = SharedPtr<int>(new int(9));
    auto c = WeakPtr<int>(b);
    auto d = WeakPtr<int>();
    d = c;
    assert(c.getUsageCount() == 2);
}

void testWeakPtrMoveAssignmentOperator() {
    auto b = SharedPtr<int>(new int(9));
    auto c = WeakPtr<int>(b);
    auto d = WeakPtr<int>();
    d = move(c);
    assert(d.getUsageCount() == 1);
}

void testWeakPtrReset() {
    auto b = SharedPtr<int>(new int(9));
    auto c = WeakPtr<int>(b);
    auto d = WeakPtr<int>(b);
    d.reset();
    assert(c.getUsageCount() == 1);
}

void testWeakPtrIsExpired() {
    auto a = WeakPtr<int>();
    assert(a.isExpired() == false);
    {
        auto b = SharedPtr<int>(new int(9));
        a = WeakPtr<int>(b);
        assert(a.isExpired() == false);
    }
    assert(a.isExpired() == true);
}

void testWeakPtrLock() {
    auto a = SharedPtr<int>(new int(8));
    auto b = WeakPtr<int>(a);
    auto c = b.lock();
    assert(a.getUsageCount() == 2);
    assert(b.getUsageCount() == 1);
}

void testWeakPtrGetUsageCount() {
    auto a = SharedPtr<int>(new int(8));
    auto b = WeakPtr<int>(a);
    assert(b.getUsageCount() == 1);
    auto c = b;
    assert(c.getUsageCount() == 2);
    {
        auto d = c;
        assert(d.getUsageCount() == 3);
    }
    assert(c.getUsageCount() == 2);
}