// Created 2025.05.07 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//

//
#define WAVE_NO_OPT // this is the fastest on debug build
//#define WAVE_LUT_OPT
//#define WAVE_BITWISE_SCALING_OPT
//
#include <blue/wave.hpp>
#include <blue/error.hpp>
//
#include <gtest/gtest.h>

s32 add(s32 a, s32 b) { return a + b; }

TEST (MathTests, Addition) {
    EXPECT_EQ (add(2, 3), 5);
}


//s32 main (s32 argumentsCount, c8** arguments) {
//
//	{ // BLUE START
//		TIMESTAMP_BEGIN = TIMESTAMP::GetCurrent ();
//		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align fututre debug-logs
//		LOGINFO ("Application Statred!\n");
//	}
//
//	{ // TYPE TESTING
//		if (sizeof (w8) 	!= 1 ) { LOGERROR ("Incorrect type size!"); }
//		if (sizeof (n8) 	!= 1 ) { LOGERROR ("Incorrect type size!"); }
//		if (sizeof (w16) 	!= 2 ) { LOGERROR ("Incorrect type size!"); }
//		if (sizeof (n16) 	!= 2 ) { LOGERROR ("Incorrect type size!"); }
//		if (sizeof (u32r32) != 4 ) { LOGERROR ("Incorrect type size!"); }
//	}
//
//	{ // WAVE TYPE TESTING
//		TIMESTAMP::Timestamp before = TIMESTAMP::GetCurrent ();
//		r32 val;
//
//		for (u64 i = 0; i < 65536 * 2; ++i) {
//
//			auto& data = *(u8*)&i;
//			//w8r32 (data, val);
//			n8r32 (data, val);
//
//			//auto& data = *(u16*)&i;
//			//w16r32 (data, val);
//			//n16r32 (data, val);
//
//			// //LOGINFO ("i: %f, %llu\n", val, i);
//
//			//if (val <= 0.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val >= 1.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val == 0.5f) LOGINFO ("i: %f, %llu\n", val, i);
//
//			//if (val <= -1.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val >=  1.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val == -0.5f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val ==  0.5f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val ==  0.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			
//		}
//
//		r32 timePassed = TIMESTAMP::GetElapsed (before);
//		LOGINFO ("val: %f, %f\n", timePassed, val);
//	}
//
//	//LOGINFO  ("Hello World\n");
//	//LOGWARN  ("Hello World\n");
//	//LOGERROR ("Hello World\n");
//
//	{ // BLUE EXIT
//		LOGMEMORY ();
//		LOGINFO ("Finalized Execution\n");
//		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align debug-logs
//	}
//
//	return 0;
//}
