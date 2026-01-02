// Created 2025.01.14 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "types.hpp"

#define CHECK_PROPERTY(error, propertyName) { if (error != ERROR_SUCCESS) \
    ERROR ("Setting up property '%ls' failed.\n\n", propertyName); }

namespace WINDOWS::REGISTRY {

    void CreateKeyMachine (
        OT HKEY    REF key, 
        OT LSTATUS REF error, 
        OT DWORD   REF status,
        IN c16*    CEF keyName
    );

    void CreatePropertyC16 (
        OT HKEY    REF key, 
        OT LSTATUS REF error,
        IN c16*    CEF property,
        IN c16*    CEF data,
        IN u32     REF dataLength
    );

    void CreatePropertyS32 (
        OT HKEY    REF key, 
        OT LSTATUS REF error,
        IN c16*    CEF property,
        IN u32     REF data
    );

}

#ifdef BLUELIB_IMPLEMENTATION
namespace WINDOWS::REGISTRY {

    //bool IsAdmin () {
    //	
    //	HANDLE currentProcessToken = nullptr;
    //	BOOL isAdmin = false;
    //	BOOL error = false;
    //	
    //	error = OpenProcessToken (GetCurrentProcess (), TOKEN_QUERY, &currentProcessToken);
    //	if (!error) return false;
    //
    //	//  LOGIC
    //	// We're checking if User is in Administrators group.
    //	//
    //
    //	LOGINFO ("AAA!\n");
    //
    //	SID_IDENTIFIER_AUTHORITY authority = SECURITY_NT_AUTHORITY;
    //	PSID administratorsGroup = nullptr;
    //
    //	error = AllocateAndInitializeSid (
    //		&authority, 2, 
    //		SECURITY_BUILTIN_DOMAIN_RID, 
    //		DOMAIN_ALIAS_RID_ADMINS, 
    //		0, 0, 0, 0, 0, 0, 
    //		&administratorsGroup
    //	);
    //
    //	if (!error) { CloseHandle (currentProcessToken); return false;}
    //
    //	LOGINFO ("BBBB!\n");
    //
    //	error = CheckTokenMembership (currentProcessToken, administratorsGroup, &isAdmin);
    //		
    //	if (error) {
    //		FreeSid (administratorsGroup);
    //		CloseHandle (currentProcessToken); 
    //		return false;
    //	}
    //
    //	LOGINFO ("HERE!\n");
    //
    //	FreeSid (administratorsGroup);
    //	CloseHandle (currentProcessToken);
    //
    //	LOGINFO ("HERE %d!\n", (u8)isAdmin);
    //
    //	return isAdmin;
    //}

    void CreateKeyMachine (
        OT HKEY    REF key, 
        OT LSTATUS REF error, 
        OT DWORD   REF status,
        IN c16*    CEF keyName
    ) {
        error = RegCreateKeyExW (
            HKEY_LOCAL_MACHINE, 			// Type
            keyName, 						// Path
            0, 								// RESERVED
            NULL, 							// optional. Class Type
            REG_OPTION_NON_VOLATILE, 		// default - store data in file not in RAM.
            KEY_WRITE | KEY_QUERY_VALUE, 	// Access rights for the key to be created.
            NULL, 							// Security descriptor for the new key.
            &key, 							// A pointer to a variable that receives a handle to the opened or created key.
            &status							// Was key created or was it only opened because it already existed.
        );
    }


    void CreatePropertyC16 (
        OT HKEY    REF key, 
        OT LSTATUS REF error,
        IN c16*    CEF property,
        IN c16*    CEF data,
        IN u32     REF dataLength
    ) {
        error = RegSetValueExW (
            key, 							// catalog (key)
            property, 						// name
            0, 								//  RESERVED
            REG_EXPAND_SZ, 					// data type - https://learn.microsoft.com/en-us/windows/win32/sysinfo/registry-value-types
            (LPCBYTE) data, 				// data
            dataLength						// data length
        );
    }


    void CreatePropertyS32 (
        OT HKEY    REF key, 
        OT LSTATUS REF error,
        IN c16*    CEF property,
        IN u32     REF data
    ) {
        error = RegSetValueExW (
            key, 							// catalog (key)
            property, 						// name
            0, 								//  RESERVED
            REG_DWORD, 						// data type - https://learn.microsoft.com/en-us/windows/win32/sysinfo/registry-value-types
            (LPCBYTE) &data, 				// data
            sizeof (data)					// data length
        );
    }

}
#endif
