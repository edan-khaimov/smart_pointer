#pragma once
#include "cassert"
#include "../move.h"
#include "../SharedPtr.h"
#include "../WeakPtr.h"

void testSharedPtrCtors() {
    auto a = SharedPtr<int>();
    assert(a == nullptr);
    auto b = SharedPtr<int>(new int(8));
    assert(*b == 8);
    auto c = WeakPtr<int>(b);
    auto d = SharedPtr<int>(c);
    assert(*d == 8);
}

void testSharedPtrCopyCtor() {
    auto a = SharedPtr<int>(new int(8));
    auto b = SharedPtr<int>(a);
    assert(b.getUsageCount() == 2);
    assert(*b == *a);
}

void testSharedPtrMoveCtor() {
    auto a = SharedPtr<int>(new int(8));
    auto b = SharedPtr<int>(move(a));
    assert(b.getUsageCount() == 1);
    assert(a == nullptr);
}

void testSharedPtrCopyAssignmentOperator() {
    int *ptr = new int(8);
    auto a = SharedPtr<int>(ptr);
    auto b = SharedPtr<int>(new int(9));
    auto c = SharedPtr<int>(new int(10));
    a = b;
    assert(b.getUsageCount() == 2);
    assert(c.getUsageCount() == 1);
    assert(*a == 9);
}

void testSharedPtrMoveAssignmentOperator() {
    int *ptr = new int(8);
    auto a = SharedPtr<int>(ptr);
    auto b = SharedPtr<int>(new int(9));
    auto c = SharedPtr<int>(new int(10));
    a = move(b);
    assert(a.getUsageCount() == 1);
    assert(c.getUsageCount() == 1);
    assert(*a == 9);
}

void testSharedPtrIndirectionOperator() {
    auto* ptr = new double(8.0);
    auto a = SharedPtr<double>(ptr);
    assert(*a == 8.0);
}

void testSharedPtrDereferenceOperator() {
    struct A {
        int b = 8;
    };
    auto a = SharedPtr<A>(new A);
    assert(a->b == 8);
}

void testSharedPtrSubscriptOperator() {
    int* array = new int[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i * 2;
    }
    auto a = SharedPtr<int[]>(array);
    for (int i = 0; i < 10; i++) {
        assert(a[i] == array[i]);
    }
}

void testSharedPtrReset() {
    int* ptr = new int(8);
    auto a = SharedPtr<int>(ptr);
    SharedPtr<int> b = a;
    SharedPtr<int> c = a;
    assert(a.getUsageCount() == 3);
    b.reset();
    assert(a.getUsageCount() == 2);
    assert(b == nullptr);
    int* ptr2 = new int(9);
    c.reset(ptr2);
    assert(a.getUsageCount() == 1);
    assert(*c == 9);
}

void testSharedPtrGetUsageCount() {
    auto a = SharedPtr<int>(new int(9));
    assert(a.getUsageCount() == 1);
    SharedPtr<int> b = a;
    assert(b.getUsageCount() == 2);
    {
        SharedPtr<int> c = b;
        assert(c.getUsageCount() == 3);
    }
    assert(b.getUsageCount() == 2);
}

void testSharedPtrIsUnique() {
    auto a = SharedPtr<int>(new int(4));
    assert(a.isUnique() == true);
    SharedPtr<int> b = a;
    assert(a.isUnique() == false);
}

void testSharedPtrCompareOperators() {
    auto a = SharedPtr<int>(new int(8));
    auto b = SharedPtr<int>(new int(9));
    auto c = SharedPtr<int>();
    assert((a == a) == true);
    assert((a != a) == false);
    assert((a == b) == false);
    assert((a != b) == true);
    assert((c == nullptr) == true);
    assert((a == nullptr) == false);
    assert((nullptr != a) == true);
}

void testMakeShared() {
    auto a = makeShared<int>(8);
    assert(*a == 8);
    auto b = makeShared<int[]>(2);
    b[0] = 2;
    b[1] = 4;
}