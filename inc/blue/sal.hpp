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

// HACK. for now.
#define OSWINDOWS

#ifdef OSWINDOWS

    #include <sal.h>

    // SAL - FUNCTION ARGUMENT IN 
    #define IN _In_ const
    // SAL - FUNCTION ARGUMENT OUT 
    #define OT _Out_
    // SAL - FUNCTION ARGUMENT IN & OUT
    #define IT _Inout_

    #define INN(count) _Out_writes_bytes_(count)
    #define OTN(count) _In_reads_bytes_(count)
    #define ITN(count) _Inout_updates_bytes_(count)

#else

    // SAL - FUNCTION ARGUMENT IN 
    #define IN
    // SAL - FUNCTION ARGUMENT OUT 
    #define OT
    // SAL - FUNCTION ARGUMENT IN & OUT
    #define IT

#endif
