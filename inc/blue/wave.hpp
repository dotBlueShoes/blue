// Created 2024.05.06 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "types.hpp"
#include "lut.hpp"

#include <cmath>
# define M_PI 3.14159265358979323846

//  ABOUT
// Wave types are defined in 4 different ways. Each can be accessed via preprocessor definition.
//  - (default) (avoids bitfields and braches)
//  - WAVE_LUT_OPT (uses lut)
//  - WAVE_BITWISE_SCALING_OPT (might outperform normal multiply in some embedded cases)
//  - WAVE_NO_OPT (uses the easy to understand solution without much opts)
// We distiguish between signed and unsigned wave type. Where unsigned wave is called a 
//  `normal` and signed variant simply a `wave`
// #define NEW_WAY_WAVE

//  TODO
// 1. This code could be further optimized via SIMD use.
// 2. Could introduce `nBitr32` & `wBitr32` methods that take extra param/s
//  but allow specifing wave bit-range.


union w8 {
    u8 value;
    struct {
        u8 wave 	: 7;
        u8 phase 	: 1;
    } bitmask;
};


union n8 {
    u8 value;
    struct {
        u8 wave 	: 6;
        u8 phase 	: 1;
        u8 sign 	: 1;
    } bitmask;
};


union w16 {
    u16 value;
    struct {
        u16 wave 	: 15;
        u16 phase 	: 1;
    } bitmask;
};


union n16 {
    u16 value;
    struct {
        u16 wave 	: 14;
        u16 phase 	: 1;
        u16 sign 	: 1;
    } bitmask;
};


union u32r32 {
    r32 value;
    union {
        u32 value;
        struct {
            u32 mantissa 	: 23;
            u32 exponent	: 8;
            u32 sign 		: 1;
        } bitmask;
        } base;
};


const r32 OUT_LUT [256] {
    0.000000000000000000f, 0.012271538285719925f, 0.024541228522912288f, 0.036807222941358830f,
    0.049067674327418015f, 0.061320736302208580f, 0.073564563599667430f, 0.085797312344439900f,
    0.098017140329560600f, 0.110222207293883060f, 0.122410675199216200f, 0.134580708507126170f,
    0.146730474455361750f, 0.158858143333861450f, 0.170961888760301220f, 0.183039887955140950f,
    0.195090322016128250f, 0.207111376192218560f, 0.219101240156869800f, 0.231058108280671100f,
    0.242980179903263870f, 0.254865659604514570f, 0.266712757474898370f, 0.278519689385053060f,
    0.290284677254462330f, 0.302005949319228100f, 0.313681740398891500f, 0.325310292162262900f,
    0.336889853392220050f, 0.348418680249434560f, 0.359895036534988100f, 0.371317193951837540f,
    0.382683432365089800f, 0.393992040061048100f, 0.405241314004989860f, 0.416429560097637150f,
    0.427555093430282100f, 0.438616238538527660f, 0.449611329654606540f, 0.460538710958240000f,
    0.471396736825997640f, 0.482183772079122700f, 0.492898192229784040f, 0.503538383725717600f,
    0.514102744193221700f, 0.524589682678469000f, 0.534997619887097200f, 0.545324988422046500f,
    0.555570233019602200f, 0.565731810783613100f, 0.575808191417845300f, 0.585797857456438900f,
    0.595699304492433400f, 0.605511041404325500f, 0.615231590580626800f, 0.624859488142386300f,
    0.634393284163645500f, 0.643831542889791400f, 0.653172842953776800f, 0.662415777590171800f,
    0.671558954847018300f, 0.680600997795453000f, 0.689540544737066800f, 0.698376249408972800f,
    0.707106781186547600f, 0.715730825283818600f, 0.724247082951466900f, 0.732654271672412800f,
    0.740951125354959100f, 0.749136394523459300f, 0.757208846506484600f, 0.765167265622459000f,
    0.773010453362736900f, 0.780737228572094500f, 0.788346427626606200f, 0.795836904608883500f,
    0.803207531480644800f, 0.810457198252594800f, 0.817584813151583700f, 0.824589302785025300f,
    0.831469612302545200f, 0.838224705554838000f, 0.844853565249707000f, 0.851355193105265200f,
    0.857728610000272100f, 0.863972856121586700f, 0.870086991108711300f, 0.876070094195406600f,
    0.881921264348354900f, 0.887639620402853900f, 0.893224301195515300f, 0.898674465693953800f,
    0.903989293123443300f, 0.909167983090522300f, 0.914209755703530700f, 0.919113851690057800f,
    0.923879532511286700f, 0.928506080473215600f, 0.932992798834738800f, 0.937339011912575000f,
    0.941544065183020800f, 0.945607325380521300f, 0.949528180593036700f, 0.953306040354193800f,
    0.956940335732208900f, 0.960430519415565800f, 0.963776065795439800f, 0.966976471044852100f,
    0.970031253194544000f, 0.972939952205560100f, 0.975702130038528600f, 0.978317370719627700f,
    0.980785280403230400f, 0.983105487431216300f, 0.985277642388941200f, 0.987301418157858400f,
    0.989176509964781000f, 0.990902635427780000f, 0.992479534598710000f, 0.993906970002356100f,
    0.995184726672196800f, 0.996312612182778000f, 0.997290456678690200f, 0.998118112900149200f,
    0.998795456205172400f, 0.999322384588349500f, 0.999698818696204200f, 0.999924701839144500f,

    1.000000000000000000f, 0.999924701839144500f, 0.999698818696204200f, 0.999322384588349500f,
    0.998795456205172400f, 0.998118112900149200f, 0.997290456678690200f, 0.996312612182778000f,
    0.995184726672196900f, 0.993906970002356100f, 0.992479534598710000f, 0.990902635427780000f,
    0.989176509964781000f, 0.987301418157858400f, 0.985277642388941200f, 0.983105487431216300f,
    0.980785280403230400f, 0.978317370719627700f, 0.975702130038528600f, 0.972939952205560200f,
    0.970031253194544000f, 0.966976471044852100f, 0.963776065795439800f, 0.960430519415565900f,
    0.956940335732208900f, 0.953306040354193900f, 0.949528180593036700f, 0.945607325380521400f,
    0.941544065183020800f, 0.937339011912575000f, 0.932992798834738800f, 0.928506080473215600f,
    0.923879532511286700f, 0.919113851690057800f, 0.914209755703530700f, 0.909167983090522500f,
    0.903989293123443400f, 0.898674465693953900f, 0.893224301195515200f, 0.887639620402853900f,
    0.881921264348355000f, 0.876070094195406600f, 0.870086991108711500f, 0.863972856121586800f,
    0.857728610000272100f, 0.851355193105265200f, 0.844853565249707200f, 0.838224705554838200f,
    0.831469612302545300f, 0.824589302785025200f, 0.817584813151583700f, 0.810457198252594800f,
    0.803207531480644900f, 0.795836904608883600f, 0.788346427626606300f, 0.780737228572094600f,
    0.773010453362737100f, 0.765167265622459100f, 0.757208846506484700f, 0.749136394523459300f,
    0.740951125354959000f, 0.732654271672412800f, 0.724247082951466900f, 0.715730825283818700f,
    0.707106781186547600f, 0.698376249408972900f, 0.689540544737067000f, 0.680600997795453200f,
    0.671558954847018600f, 0.662415777590172000f, 0.653172842953776600f, 0.643831542889791400f,
    0.634393284163645500f, 0.624859488142386300f, 0.615231590580626900f, 0.605511041404325700f,
    0.595699304492433500f, 0.585797857456439000f, 0.575808191417845400f, 0.565731810783613500f,
    0.555570233019602200f, 0.545324988422046400f, 0.534997619887097200f, 0.524589682678469000f,
    0.514102744193221800f, 0.503538383725717600f, 0.492898192229784150f, 0.482183772079122900f,
    0.471396736825997800f, 0.460538710958240200f, 0.449611329654606900f, 0.438616238538527550f,
    0.427555093430282030f, 0.416429560097637150f, 0.405241314004989900f, 0.393992040061048150f,
    0.382683432365089900f, 0.371317193951837700f, 0.359895036534988330f, 0.348418680249434800f,
    0.336889853392220330f, 0.325310292162263260f, 0.313681740398891400f, 0.302005949319228030f,
    0.290284677254462400f, 0.278519689385053170f, 0.266712757474898500f, 0.254865659604514700f,
    0.242980179903264070f, 0.231058108280671330f, 0.219101240156870050f, 0.207111376192218840f,
    0.195090322016128600f, 0.183039887955140900f, 0.170961888760301220f, 0.158858143333861470f,
    0.146730474455361800f, 0.134580708507126280f, 0.122410675199216350f, 0.110222207293883240f,
    0.098017140329560830f, 0.085797312344440160f, 0.073564563599667730f, 0.061320736302208490f,
    0.049067674327417966f, 0.036807222941358830f, 0.024541228522912326f, 0.012271538285720007f,
};


void w8r32  ( IN u8  REF waveIn, OT r32 REF waveOt ); // 8bit  Wave   to 32bit Real
void n8r32  ( IN u8  REF waveIn, OT r32 REF waveOt ); // 8bit  Normal to 32bit Real
void w16r32 ( IN u16 REF waveIn, OT r32 REF waveOt ); // 16bit Wave   to 32bit Real
void n16r32 ( IN u16 REF waveIn, OT r32 REF waveOt ); // 16bit Normal to 32bit Real


#ifdef BLUELIB_IMPLEMENTATION

    void w8r32 (
        IN u8  REF waveIn,
        OT r32 REF waveOt
    ) {

        #ifdef NEW_WAY_WAVE

            // TODO LUT could reduce it to possibly 1-2 cycles or fewer, depending on memory/cache access.
            //waveOt = sinf ((waveIn / 256.0f) * M_PI / 2);
            waveOt = OUT_LUT[waveIn];

        #else
            const r32 STEP7 = 1.0f / 128.0f;

            auto& real = *(u32r32*)&waveOt;
            const auto& base = *(const w8*)&waveIn;

            #ifdef WAVE_NO_OPT
                if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 128 + 1) * STEP7; } // 129 -> 255
                else { real.value = base.bitmask.wave * STEP7; } // for 0 -> 127
            #else
                const auto& value = base.value;			// Don't use bitfields.
                u8 wave 	= value & 0x7F;				// Extract wave 	(bits 0-6)
                u8 phase 	= (value >> 7);				// Extract sign 	(bit  7  )

                #ifdef WAVE_LUT_OPT
                    u8 phasedWave = phase ? (128 - wave) : wave;	// Branchless
                    real.value = DIV128LUT[phasedWave];				// LUT
                #else
                    u8 phasedWave = phase ? (~wave - (0x7F)) : wave; 	// Branchless
                    #ifdef WAVE_BITWISE_SCALING_OPT
                        // Weird. Might be faster.
                        real.value = (r32)(phasedWave << 17) * 0x1p-24f;
                    #else
                        real.value = (r32)phasedWave * STEP7;		// u8 to r32 cast.
                    #endif
                #endif
            #endif
        #endif
    }


    void n8r32 (
        IN u8  REF waveIn,
        OT r32 REF waveOt
    ) {

        const r32 STEP6 = 1.0f / 64.0f;

        auto& real = *(u32r32*)&waveOt;
        const auto& base = *(const n8*)&waveIn;

        #ifdef WAVE_NO_OPT
            if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 64 + 1) * STEP6; } // 65 -> 127
            else { real.value = base.bitmask.wave * STEP6; } // for 0 -> 63
            real.base.bitmask.sign = base.bitmask.sign;
        #else
            const auto& value = base.value;			// Don't use bitfields.
            u8 wave 	= value & 0x3F;				// Extract wave 	(bits 0-5)
            u8 phase 	= (value >> 6) & 1;			// Extract phase 	(bit  6  )
            u8 sign 	= (value >> 7);				// Extract sign 	(bit  7  )

            #ifdef WAVE_LUT_OPT
                u8 phasedWave = phase ? (64 - wave) : wave;		// Branchless
                real.value = DIV64LUT[phasedWave];				// LUT
            #else
                u8 phasedWave = phase ? (~wave - (0x80 + 0x40 - 1)) : wave; 	// Branchless
                #ifdef WAVE_BITWISE_SCALING_OPT
                    // Weird. Might be faster.
                    real.value = (r32)(phasedWave << 18) * 0x1p-24f;
                #else
                    real.value = (r32)phasedWave * STEP6;		// u8 to r32 cast.
                #endif
            #endif

            // Set sign bit directly without the use of bitfields.
            ((u32*)&real.value)[0] = (((u32*)&real.value)[0] & 0x7FFFFFFF) | (sign << 31);
        #endif
    }


    void w16r32 (
        IN u16 REF waveIn,
        OT r32 REF waveOt
    ) {

        const r32 STEP15 = 1.0f / 32768.0f;

        auto& real = *(u32r32*)&waveOt;
        const auto& base = *(w16*)&waveIn;

        #ifdef WAVE_NO_OPT
            if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 32768 + 1) * STEP15; } // 32769 -> 65 535
            else { real.value = base.bitmask.wave * STEP15; } // for 0 -> 32767
        #else
            const auto& value = base.value;			// Don't use bitfields.
            u16 wave 	= value & 0x7FFF;			// Extract wave 	(bits 0-14)
            u16 phase 	= (value >> 15);			// Extract sign 	(bit  15  )

            u16 phasedWave = phase ? (~wave - (0x7FFF)) : wave; 	// Branchless
            #ifdef WAVE_BITWISE_SCALING_OPT
                // Weird. Might be faster.
                real.value = (r32)(phasedWave << 9) * 0x1p-24f;
            #else
                real.value = (r32)phasedWave * STEP15;		// u8 to r32 cast.
            #endif
        #endif
    }


    void n16r32 (
        IN u16 REF waveIn,
        OT r32 REF waveOt
    ) {

        const r32 STEP14 = 1.0f / 16384.0f;

        auto& real = *(u32r32*)&waveOt;
        const auto& base = *(n16*)&waveIn;

        #ifdef WAVE_NO_OPT
            if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 16384 + 1) * STEP14; } // 16385 -> 32767
            else { real.value = base.bitmask.wave * STEP14; } // for 0 -> 16383
            real.base.bitmask.sign = base.bitmask.sign;
        #else
            const auto& value = base.value;			// Don't use bitfields.
            u16 wave 	= value & 0x3FFF;			// Extract wave 	(bits 0-13)
            u16 phase 	= (value >> 14) & 1;		// Extract phase 	(bit  14  )
            u16 sign 	= (value >> 15);			// Extract sign 	(bit  15  )

            u16 phasedWave = phase ? (~wave - (0x8000 + 0x4000 - 1)) : wave; 	// Branchless
            #ifdef WAVE_BITWISE_SCALING_OPT
                // Weird. Might be faster.
                real.value = (r32)(phasedWave << 10) * 0x1p-24f;
            #else
                real.value = (r32)phasedWave * STEP14;		// u8 to r32 cast.
            #endif

            // Set sign bit directly without the use of bitfields.
            ((u32*)&real.value)[0] = (((u32*)&real.value)[0] & 0x7FFFFFFF) | (sign << 31);
        #endif
    }

#endif
