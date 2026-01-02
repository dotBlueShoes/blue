// Created 2024.11.13 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "debug.hpp"

//  'About'
// - Implements a simple wrapper around 'malloc'
// - Implements a custom 'atexit' implementation that allows sending the parameter. 
//

#ifndef MEMORY_EXIT_SIZE
    #define MEMORY_EXIT_SIZE 64
#endif


#ifndef MEMORY_TYPE
    #define MEMORY_TYPE u32
#endif


#define DEALLOC_TYPE void
#define DEALLOC_RET  


#ifdef MEMORY_TYPE_NOT_SIZED
    #define DEALLOC_ARGS INOUT void* data
#else
    #define DEALLOC_ARGS IN	MEMORY_TYPE	size, IT void* data
#endif


void FREE (DEALLOC_ARGS);


#if DDEBUG (DEBUG_FLAG_MEMORY)

    s32 allocationsCounter = 0;

    #if DDEBUG (DEBUG_FLAG_LOGGING)

        #include "log.hpp"

        #define LOGMEMORY() { \
            LOGWARN ("Missed Deallocations: %d\n", allocationsCounter); \
        }

    #else
        #define LOGMEMORY() {} // dummy
    #endif

    #define INCALLOCCO() ++allocationsCounter;
    #define DECALLOCCO() --allocationsCounter;

    template <typename Type>
    void _ALLOCATE ( OT Type* REF address, IN u64   REF size );


    #ifdef BLUELIB_IMPLEMENTATION

    template <typename Type>
    void _ALLOCATE ( 
        OT Type* REF address, 
        IN u64   REF size
    ) {
        ++allocationsCounter;
        address = (Type*) malloc (size);
    }

    void FREE (DEALLOC_ARGS) {
        --allocationsCounter;
        free (data);
    }

    #endif


    #define ALLOCATE(type, address, size) _ALLOCATE<type> (address, size)

#else

    #define ALLOCATE(type, address, size) address = (type*) malloc (size)

    #ifdef BLUELIB_IMPLEMENTATION
    void FREE (DEALLOC_ARGS) { free (data); }
    #endif

    #define LOGMEMORY() {} // dummy
    #define INCALLOCCO() // dummy
    #define DECALLOCCO() // dummy

#endif

// namespace MEMORY {
// 
//     template <typename T>
//     void Construct2 (
//         OT                 T*    REF newArray, 
//         IN                 u32   REF aArrayLength, 
//         INN (aArrayLength) void* CEF aArray, 
//         IN                 u32   REF bArrayLength, 
//         INN (bArrayLength) void* CEF bArray
//     ) {
//         ALLOCATE (T, newArray, aArrayLength + bArrayLength);
//         memcpy (newArray, aArray, aArrayLength);
//         memcpy (newArray + aArrayLength, bArray, bArrayLength);
//     }
// 
//     template <typename T>
//     void Construct3 (
//         OT                 T*    REF newArray, 
//         IN                 u32   REF aArrayLength, 
//         INN (aArrayLength) void* CEF aArray, 
//         IN                 u32   REF bArrayLength, 
//         INN (bArrayLength) void* CEF bArray,
//         IN                 u32   REF cArrayLength, 
//         INN (cArrayLength) void* CEF cArray
//     ) {
//         ALLOCATE (T, newArray, aArrayLength + bArrayLength + cArrayLength);
//         memcpy (newArray, aArray, aArrayLength);
//         memcpy (newArray + aArrayLength, bArray, bArrayLength);
//         memcpy (newArray + aArrayLength + bArrayLength, cArray, cArrayLength);
//     }
// 
// }
