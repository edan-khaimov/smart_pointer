#pragma once
#include "UniquePtrTest.h"
#include "SharedPtrTest.h"
#include "WeakPtrTest.h"
#include "ArraySequenceTest.h"

void testUniquePtr() {
    testUniquePtrCtors();
    testUniquePtrMoveCtor();
    testUniquePtrMoveAssignmentOperator();
    testUniquePtrIndirectionOperator();
    testUniquePtrDereferenceOperator();
    testUniquePtrSubscriptOperator();
    testUniquePtrReset();
    testUniquePtrRelease();
    testUniquePtrCompareOperators();
    testMakeUnique();
}

void testSharedPtr() {
    testSharedPtrCtors();
    testSharedPtrCopyCtor();
    testSharedPtrMoveCtor();
    testSharedPtrCopyAssignmentOperator();
    testSharedPtrMoveAssignmentOperator();
    testSharedPtrIndirectionOperator();
    testSharedPtrDereferenceOperator();
    testSharedPtrSubscriptOperator();
    testSharedPtrReset();
    testSharedPtrGetUsageCount();
    testSharedPtrIsUnique();
    testSharedPtrCompareOperators();
    testMakeShared();
}

void testWeakPtr() {
    testWeakPtrCtors();
    testWeakPtrCopyCtor();
    testWeakPtrMoveCtor();
    testWeakPtrCopyAssignmentOperator();
    testWeakPtrMoveAssignmentOperator();
    testWeakPtrReset();
    testWeakPtrIsExpired();
    testWeakPtrLock();
    testWeakPtrGetUsageCount();
}

void testArraySequence() {
    testArrayCtors();
    testArrayCopyCtor();
    testArrayMoveCtor();
    testArrayGetters();
    testArrayAppend();
    testArrayPrepend();
    testArrayInsertAt();
    testArrayIndexOperator();
    testArrayCopyAssignmentOperator();
    testArrayMoveAssignmentOperator();
    testArrayGetSubArray();
    testArrayConcat();
}