// Created 2026.03.26 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "../compilerlog.hpp"
#include "../basetypes.hpp"

#if defined(__clang__) || defined(__GNUC__)

    codeblock void bswap16b ( IT u16 REF value) {
        __asm__ volatile (
            "bswap %0" : "+r"(value)
        );
    }

    codeblock void bswap32b ( IT u32 REF value) {
        __asm__ volatile (
            "bswap %0" : "+r"(value)
        );
    }

    codeblock void bswap64b ( IT u64 REF value) {
        __asm__ volatile (
            "bswap %0" : "+r"(value)
        );
    }

#else

    codeblock void bswap16b ( IT u16 REF value ) {
        value = _byteswap_ushort(value);
    }

    codeblock void bswap32b ( IT u32 REF value ) {
        value = _byteswap_ulong(value);
    }

    codeblock void bswap64b ( IT u64 REF value ) {
        value = _byteswap_uint64(value);
    }

#endif
