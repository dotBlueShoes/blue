// Created 2025.03.12 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once

//  About
// (SAL) Source-Code Annotation Language.
//
// Natively, C and C++ provide only limited ways for developers to 
//  consistently express intent and invariance. By using SAL 
//  annotations, you can describe your functions in greater detail 
//  so that developers who are consuming them can better understand 
//  how to use them.
// https://learn.microsoft.com/en-us/cpp/code-quality/understanding-sal?view=msvc-170
//

// TODO
// _Out_writes_() & _In_reads_() and other.

// HACK. for now.
#define OSWINDOWS

#ifdef OSWINDOWS

    #include <sal.h>

    // SAL - FUNCTION ARGUMENT IN 
    //#define IN _In_
    // SAL - FUNCTION ARGUMENT OUT 
    //#define OUT _Out_
    // SAL - FUNCTION ARGUMENT IN & OUT
    //#define INOUT _Inout_

    // SAL - FUNCTION ARGUMENT IN 
    #define IN _In_ const
    // SAL - FUNCTION ARGUMENT OUT 
    #define OT _Out_
    // SAL - FUNCTION ARGUMENT IN & OUT
    #define IT _Inout_

    #define IN_N(count) _Out_writes_bytes_(count)
    #define OT_N(count) _In_reads_bytes_(count)
    #define IT_N(count) _Inout_updates_bytes_(count)

    //#define _ARG2(_0, _1, N, ...) N
    //#define _HAS_ARGS(...) _ARG2(__VA_ARGS__, 1, 0)
    //#define foo_dispatch(hasargs, ...) foo_dispatch_(hasargs, __VA_ARGS__)
    //#define foo_dispatch_(hasargs, ...) IN_##hasargs(__VA_ARGS__)
    //#define AA(...) foo_dispatch(_HAS_ARGS(__VA_ARGS__), __VA_ARGS__)

    //#define AA(...) foo_OVERLOAD(__VA_ARGS__)
    //#define AA AA()
    //#define foo_OVERLOAD(...) foo_SELECT(__VA_ARGS__, foo_with_arg, foo_noargs)
    //#define foo_SELECT(a, b, NAME, ...) NAME
    //#define foo_noargs IN_0()
    //#define foo_with_arg(x) IN_1(x)

#else

    // SAL - FUNCTION ARGUMENT IN 
    #define IN
    // SAL - FUNCTION ARGUMENT OUT 
    #define OT
    // SAL - FUNCTION ARGUMENT IN & OUT
    #define IT

#endif

// SAL - STATING THAT IT WAS TESTED THAT BRANCHLESS
// IMPLEMENTATION HERE IS IN FACT BETTER.
//#define BRANCHLESS
// SAL - STATING THAT IT WAS TESTED THAT BRANCH
// IMPLEMENTATION HERE IS IN FACT BETTER.
//#define BRANCH
