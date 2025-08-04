// Created 2025.05.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "memory.hpp"


//  ABOUT
// We're defining 2 systems. SIZED and NOT_SIZED. It's important to note that both connot be used at the same time.
//  Because of allocation order importance. Therefore as a programmer u have to decide on one and 
//  ensure reusing that system in every dealloc method.

//  ABOUT - MEMORY_TYPE_NOT_SIZED
// By default use not sized variant for memory exiting. 
// We cannot use both systems because it's important to dealloc memory in order of allocation!
// #define MEMORY_TYPE_NOT_SIZED 

#ifdef MEMORY_TYPE_NOT_SIZED

    namespace MEMORY::EXIT {

        using DeleteFunction = void (*) (DEALLOC_ARGS);

        u8 memoryCounter = 0;

        DeleteFunction functions [MEMORY_EXIT_SIZE];
        void* memories	[MEMORY_EXIT_SIZE];

        void ATEXIT () {
            for (u8 i = memoryCounter; i != 0; --i) {
                auto& func		= functions	[i - 1];
                auto& memory	= memories	[i - 1];

                auto&& _func = (DeleteFunction)func;
                _func (memory);
            }
        }

        void PUSH (
            DeleteFunction function, 
            void* memory
        ) {
            functions[memoryCounter] 	= function;
            memories[memoryCounter] 	= memory;

            ++memoryCounter;
        }

        void POP () {
            --memoryCounter;
        }

    }

#else

    namespace MEMORY::EXIT {

        // bop/push -> pop

        //  ABOUT
        //
        // ---  lasting  ---
        // Elements placed on the stack will be deallocated from the newest to the oldest.
        //  -> push() - pop()
        //
        // --- temporary ---
        // Elements placed on the temporary range will be deallocated from the oldes to the newest.
        //  When temporary range is not being used anymore we can reset it using -> clear().
        //  -> add() - rem()
        //  Elements added onto temporary range exist only to help create elements on the stack!
        //  Or to keep track of elements that are ment to be deallocated mid execution.
        //  In some cases it might be required to call clear() and add() to readd elements that are still
        //  supposed to be tracked.

        u8 backCounter = MEMORY_EXIT_SIZE;
        u8 tempCounter = MEMORY_EXIT_SIZE;
        u8 memoryCounter = 0;

        using DeleteFunction = void (*) (DEALLOC_ARGS);

        DeleteFunction  functions   [MEMORY_EXIT_SIZE];
        void*           memories    [MEMORY_EXIT_SIZE];
        u32             sizes		[MEMORY_EXIT_SIZE];

        void ATEXIT () {
            // abc -> cba memory deallocation.
            //
            for (u8 i = memoryCounter; i != 0; --i) {
                auto& func		= functions	[i - 1];
                auto& memory	= memories	[i - 1];
                auto& size		= sizes 	[i - 1];

                auto&& _func = (DeleteFunction)func;
                _func (size, memory);
            }

            // abc -> abc memory deallocation.
            //
            for (u8 i = tempCounter; i < backCounter; ++i) {
                auto& func		= functions	[i];
                auto& memory	= memories	[i];
                auto& size		= sizes 	[i];

                auto&& _func = (DeleteFunction)func;
                _func (size, memory);
            }
        }

        // Lasting variant (elements are pushed or poped from a stack).
        //
        void PUSH (
            DeleteFunction  function, 
            MEMORY_TYPE     size, 
            void*           memory
        ) {
            functions   [memoryCounter] = function;
            memories    [memoryCounter] = memory;
            sizes       [memoryCounter] = size;

            ++memoryCounter;
        }

        // Lasting variant (elements are pushed or poped from a stack).
        //
        void POP () {
            --memoryCounter;
        }

        // Temporary variant (elements are added)
        //
        void ADD (
            DeleteFunction  function, 
            MEMORY_TYPE     size, 
            void*           memory
        ) {
            --tempCounter;

            functions   [tempCounter] = function;
            memories    [tempCounter] = memory;
            sizes       [tempCounter] = size;
        }

        // Temporary variant 
        //
        void REM () {
            --backCounter;
        }

        // Temporary variant 
        //
        void CLEAR () {
            tempCounter = MEMORY_EXIT_SIZE;
            backCounter = MEMORY_EXIT_SIZE;
        }

    }

#endif

#define DEALLOC(name, body) \
    DEALLOC_TYPE name (DEALLOC_ARGS) { \
        body \
        DEALLOC_RET \
    }
//#define end
