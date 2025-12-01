// Created 2025.12.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once 

//  ABOUT
// Keep track of how big created datatypes are. This is a diagnostic to only inform the programmer 
//  easily how big certain elements he creates are. And whether it could be problematic or not.
// TODO: Link to note about cache pages, function call stack, page sizes, cache misses, other re/loading problems
//
#define BB(x)

//  ABOUT
// A simple struct wrapper meant for additional testing and byte size control.
//
#define STRUCT(x, y) enum { _BLUE_STRUCT_##y##_TEST_SIZE = x }; struct y


//  ABOUT
// Check if bytesize calculated by the programmer is equal to the actual bytesize at runtime.
//
#define BSTRUCT_TEST(ns, x) sizeof (ns::x) * 8 == ns::_BLUE_STRUCT_ ##x## _TEST_SIZE

//  ABOUT
// Provide an information on wheater or not sait struct has proper bytesize information provided.
//
#define BSTRUCT_TESTLOG(ns, x) if (!(BSTRUCT_TEST (ns, x))) { \
    LOGWARN ("Struct size predictment inncorect: '%s::%s' is %lld\n", #ns, #x, sizeof (ns::x) * 8); \
}

#if defined(_MSC_VER) // MSVC

    #define UNALIGNED_START __pragma(pack(push, 1))
    #define UNALIGNED_END __pragma(pack(pop))

#elif defined(__clang__) || defined(__GNUC__) // GCC/Clang:

    #define UNALIGNED_START
    #define UNALIGNED_END __attribute__((packed))
    
#else
    #error "Unknown compiler"
#endif

//  ABOUT
// Makes struct bytes unaligned.
//
#define UNALIGNED_STRUCT(bytes, name, code) \
    UNALIGNED_START \
    STRUCT (bytes, name) \
    code \
    UNALIGNED_END;
