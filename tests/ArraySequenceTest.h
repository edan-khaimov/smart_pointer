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

void testArrayGetters() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(arr, 5);
    assert(c.GetLength() == 5);
    c.Append(6);
    assert(c.GetLength() == 6);
    for (int i = 0; i < 5; i++) {
        assert(arr[i] == c.Get(i));
    }
    assert(c.Get(5) == 6);
    assert(c.GetFirst() == 0);
    assert(c.GetLast() == 6);
}

void testArrayAppend() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    c.Append(4);
    c.Append(8);
    assert(c.GetLength() == 7);
    for (int i = 0; i < 5; i++) {
        c[i] = i;
    }
    assert(c[5] == 4 && c[6] == 8);
}

void testArrayPrepend() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    c.Prepend(4);
    c.Prepend(8);
    assert(c.GetLength() == 7);
    for (int i = 2; i < 5; i++) {
        c[i] = i;
    }
    assert(c[0] == 8 && c[1] == 4);
}

void testArrayInsertAt() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    c.InsertAt(4, 1);
    assert(c[0] == 0 && c[1] == 4);
    for (int i = 2; i < 6; i++) {
        assert(c[i] == i - 1);
    }
}

void testArrayIndexOperator() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(arr, 5);
    for (int i = 0; i < 5; i++) {
        assert(c[i] == arr[i]);
    }
}

void testArrayCopyAssignmentOperator() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    auto d = c;
    assert(d.GetLength() == 5);
    for (int i = 0; i < 5; i++) {
        assert(c[i] == d[i]);
    }
}

void testArrayMoveAssignmentOperator() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    auto d = move(c);
    assert(c.GetLength() == 0);
    for (int i = 0; i < 5; i++) {
        assert(i == d[i]);
    }
}

void testArrayGetSubArray() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(move(arr), 5);
    auto d = c.GetSubArray(1, 3);
    assert(d.GetLength() == 3);
    for (int i = 0; i < 3; i++) {
        assert(d[i] == i + 1);
    }
}

void testArrayConcat() {
    auto arr = makeUnique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    ArraySequence<int> c(arr, 5);
    ArraySequence<int> d(arr, 5);
    auto a = c.Concat(d);
    assert(a.GetLength() == 10);
    for (int i = 0; i < 10; i++) {
        assert(a[i] == (i % 5));
    }
}