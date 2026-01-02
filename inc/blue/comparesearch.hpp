// Created 2024.10.28 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "types.hpp"

namespace COMPARESEARCH {

    void ArrayPartFirstMatch (
        IN void* CEF compered,
        IN u16   REF comperedCount,
        IN u8    REF comperedSize,
        OT u32   REF index,
        IN u32   REF elementsCount,
        IN void* CEF elements
    );

    void ArrayPartFirstMatchVector (
        IN void*        CEF compered,
        IN u16          REF comperedCount,
        IN u8           REF comperedSize,
        OT u32          REF index,
        IN u32          REF elementsCount,
        IN void* const* CEF elements
    );

    void ArrayPartFirstMatchVectorLowCase (
        IN void*        CEF compered,
        IN u16          REF comperedCount,
        IN u8           REF comperedSize,
        OT u32          REF index,
        IN u32          REF elementsCount,
        IN void* const* CEF elements
    );

}

#ifdef BLUELIB_IMPLEMENTATION
namespace COMPARESEARCH {

    void ArrayPartFirstMatch (
        IN void* CEF compered,
        IN u16   REF comperedCount,
        IN u8    REF comperedSize,
        OT u32   REF index,
        IN u32   REF elementsCount,
        IN void* CEF elements
    ) {
        auto& iElement = index;
        u8 collision = 1;

        for (; iElement < (elementsCount * collision); ++iElement) {

            for (u8 iInner = 0; iInner < comperedCount * comperedSize; ++iInner) {
                const auto& array = ((u8**)elements)[iElement];
                const u8& byte =  array[iInner * comperedSize];

                collision += ((u8*)compered)[iInner * comperedSize] == byte;
            }
                
            collision = ((collision - 1) != comperedCount);
        }

        --iElement;
    }

    void ArrayPartFirstMatchVector (
        IN void*        CEF compered,
        IN u16          REF comperedCount,
        IN u8           REF comperedSize,
        OT u32          REF index,
        IN u32          REF elementsCount,
        IN void* const* CEF elements
    ) {
        auto& iElement = index;
        u8 collision = 1;

        for (; iElement < (elementsCount * collision); ++iElement) {

            for (u8 iInner = 0; iInner < comperedCount * comperedSize; ++iInner) {

                const auto& array = (u8*) (elements[iElement]);
                const u8& byte = array[iInner * comperedSize];

                collision += ((u8*)compered)[iInner * comperedSize] == byte;
            }

            collision = ((collision - 1) != comperedCount);
        }

        --iElement;
        index += collision;
    }

    void ArrayPartFirstMatchVectorLowCase (
        IN void*        CEF compered,
        IN u16          REF comperedCount,
        IN u8           REF comperedSize,
        OT u32          REF index,
        IN u32          REF elementsCount,
        IN void* const* CEF elements
    ) {
        auto& iElement = index;
        u8 collision = 1;

        for (; iElement < (elementsCount * collision); ++iElement) {

            for (u8 iInner = 0; iInner < comperedCount * comperedSize; ++iInner) {

                const auto& array = (u8*) (elements[iElement]);
                const u8& byte = array[iInner * comperedSize];
                const u8 lowCaseByte = tolower (byte);

                collision += ((u8*)compered)[iInner * comperedSize] == lowCaseByte;
            }

            collision = ((collision - 1) != comperedCount);
        }

        --iElement;
        index += collision;
    }

}
#endif
