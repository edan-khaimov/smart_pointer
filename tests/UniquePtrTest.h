#pragma once
#include "cassert"
#include "../move.h"
#include "../UniquePtr.h"

void testUniquePtrCtors() {
    UniquePtr<int> a;
    assert(a == nullptr);
    auto b = UniquePtr<double>(new double(8.0));
    assert(*b == 8.0);
}

void testUniquePtrMoveCtor() {
    auto a = UniquePtr<int>(new int(8));
    auto b = UniquePtr<int>(move(a));
    assert(a == nullptr);
    assert(*b == 8);
}

void testUniquePtrMoveAssignmentOperator() {
    auto a = UniquePtr<int>(new int(8));
    auto b = UniquePtr<int>(new int(9));
    b = move(a);
    assert(*b == 8);
    assert(a == nullptr);
}

void testUniquePtrIndirectionOperator() {
    auto a = UniquePtr<float>(new float(46.0f));
    assert(*a == 46.0f);
}

void testUniquePtrDereferenceOperator() {
    struct A {
        int a = 8;
    };
    auto b = UniquePtr<A>(new A);
    assert(b->a == 8);
}

void testUniquePtrSubscriptOperator() {
    int* array = new int[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i * 2;
    }
    auto a = UniquePtr<int[]>(array);
    for (int i = 0; i < 10; i++) {
        assert(a[i] == array[i]);
    }
}

void testUniquePtrReset() {
    auto a = UniquePtr<int>(new int(8));
    a.reset(new int(9));
    assert(*a == 9);
}

void testUniquePtrRelease() {
    auto a = UniquePtr<int>(new int(8));
    int* b = a.release();
    assert(a == nullptr);
    assert(*b == 8);
}

void testUniquePtrCompareOperators() {
    auto a = UniquePtr<int>(new int(8));
    auto b = UniquePtr<int>(new int(9));
    auto c = UniquePtr<int>();
    assert((a == a) == true);
    assert((a != a) == false);
    assert((a == b) == false);
    assert((a != b) == true);
    assert((c == nullptr) == true);
    assert((a == nullptr) == false);
    assert((nullptr != a) == true);
}

void testMakeUnique() {
    auto a = makeUnique<int>(8);
    assert(*a == 8);
    auto b = makeUnique<int[]>(2);
    b[0] = 2;
    b[1] = 4;
}