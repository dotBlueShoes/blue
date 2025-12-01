// Created 2025.12.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once 
#include "types.hpp"

namespace STRINGCASE {

    void TransformToLower (
        IN            u32 REF length,
        IO_N (length) c8* REF data
    ) {
        for (u32 i = 0; i < length; ++i) {
            data[i] = tolower (data[i]);
        }
    }

    void TransformToUpper (
        IN            u32 REF length,
        IO_N (length) c8* REF data
    ) {
        // TODO
    }

}
