cmake_minimum_required(VERSION 3.28)
project(smart_pointers)

set(CMAKE_CXX_STANDARD 23)

add_executable(smart_pointers main.cpp
        UniquePtr.h
        removeExtent.h
        isArray.h
        SharedPtr.h
        Sequence.h
        WeakPtr.h
        tests/UniquePtrTest.h
        tests/test.h
        tests/SharedPtrTest.h
        tests/WeakPtrTest.h
        ArraySequence.h
        ArraySequence.h
)

target_compile_options(smart_pointers PRIVATE -fconcepts)