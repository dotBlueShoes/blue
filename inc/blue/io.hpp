// Created 2024.10.28 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "error.hpp"

namespace IO {

    bool IsExisting (
        IN c16* CEF name
    ) {
        struct _stat64i32 buffer;   
          return (_wstat (name, &buffer) == 0); 
    }

    bool IsExisting (
        IN c8* CEF name
    ) {
        struct stat buffer;   
          return (stat (name, &buffer) == 0); 
    }

    void CreateEmpty (
        IN c16* CEF pathname
    ) {
        std::wofstream outfile (pathname);
        outfile.close ();
    }

    void CreateEmpty (
        IN c8* CEF pathname
    ) {
        std::ofstream outfile (pathname);
        outfile.close ();
    }

    void CreateAdd (
        IN c16* CEF pathname,
        IN c16* CEF context
    ) {
        std::wofstream outfile (pathname);
        outfile << context << std::endl;
        outfile.close ();
    }

    void CreateAdd (
        IN c8* CEF pathname,
        IN c8* CEF context
    ) {
        std::ofstream outfile (pathname);
        outfile << context << std::endl;
        outfile.close ();
    }

    void Read (
        IN c16*  CEF pathname,
        OT FILE* REF file
    ) {
        file = _wfopen (pathname, L"rb");
        if (file == nullptr) ERROR ("File could not be opened - '%ls'." ERROR_NEW_LINE, pathname);
    }

    void Close (
        IT	FILE* REF file
    ) {
        fclose (file);
    }

}
