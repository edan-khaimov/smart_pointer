#pragma once
#include "../ArraySequence.h"
#include <cassert>

void testArrayCtors() {
    ArraySequence<int> a;
    ArraySequence<int> b(4);
    assert(b.GetLength() == 4);
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(arr, 5);
    for (int i = 0; i < 5; i++) {
        assert(c.Get(i) == i);
    }
    ArraySequence<int> d(move(arr), 5);
    for (int i = 0; i < 5; i++) {
        assert(d.Get(i) == i);
    }
}

void testArrayCopyCtor() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    ArraySequence<int> d(c);
    for (int i = 0; i < 5; i++) {
        assert(c[i] == d[i]);
    }
}

void testArrayMoveCtor() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    ArraySequence<int> d(move(c));
    for (int i = 0; i < 5; i++) {
        assert(d[i] == i);
    }
    assert(c.GetLength() == 0);
}

