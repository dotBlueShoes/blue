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


r32 OUT_LUT [256] {
    0.000000000000000000f,
    0.012271538285719925f,
    0.024541228522912288f,
    0.036807222941358830f,
    0.049067674327418015f,
    0.061320736302208580f,
    0.073564563599667430f,
    0.085797312344439900f,
    0.098017140329560600f,
    0.110222207293883060f,
    0.122410675199216200f,
    0.134580708507126170f,
    0.146730474455361750f,
    0.158858143333861450f,
    0.170961888760301220f,
    0.183039887955140950f,
    0.195090322016128250f,
    0.207111376192218560f,
    0.219101240156869800f,
    0.231058108280671100f,
    0.242980179903263870f,
    0.254865659604514570f,
    0.266712757474898370f,
    0.278519689385053060f,
    0.290284677254462330f,
    0.302005949319228100f,
    0.313681740398891500f,
    0.325310292162262900f,
    0.336889853392220050f,
    0.348418680249434560f,
    0.359895036534988100f,
    0.371317193951837540f,
    0.382683432365089800f,
    0.393992040061048100f,
    0.405241314004989860f,
    0.416429560097637150f,
    0.427555093430282100f,
    0.438616238538527660f,
    0.449611329654606540f,
    0.460538710958240000f,
    0.471396736825997640f,
    0.482183772079122700f,
    0.492898192229784040f,
    0.503538383725717600f,
    0.514102744193221700f,
    0.524589682678469000f,
    0.534997619887097200f,
    0.545324988422046500f,
    0.555570233019602200f,
    0.565731810783613100f,
    0.575808191417845300f,
    0.585797857456438900f,
    0.595699304492433400f,
    0.605511041404325500f,
    0.615231590580626800f,
    0.624859488142386300f,
    0.634393284163645500f,
    0.643831542889791400f,
    0.653172842953776800f,
    0.662415777590171800f,
    0.671558954847018300f,
    0.680600997795453f,
    0.6895405447370668f,
    0.6983762494089728f,
    0.7071067811865476f,
    0.7157308252838186f,
    0.7242470829514669f,
    0.7326542716724128f,
    0.7409511253549591f,
    0.7491363945234593f,
    0.7572088465064846f,
    0.765167265622459f,
    0.7730104533627369f,
    0.7807372285720945f,
    0.7883464276266062f,
    0.7958369046088835f,
    0.8032075314806448f,
    0.8104571982525948f,
    0.8175848131515837f,
    0.8245893027850253f,
    0.8314696123025452f,
    0.838224705554838f,
    0.844853565249707f,
    0.8513551931052652f,
    0.8577286100002721f,
    0.8639728561215867f,
    0.8700869911087113f,
    0.8760700941954066f,
    0.8819212643483549f,
    0.8876396204028539f,
    0.8932243011955153f,
    0.8986744656939538f,
    0.9039892931234433f,
    0.9091679830905223f,
    0.9142097557035307f,
    0.9191138516900578f,
    0.9238795325112867f,
    0.9285060804732156f,
    0.9329927988347388f,
    0.937339011912575f,
    0.9415440651830208f,
    0.9456073253805213f,
    0.9495281805930367f,
    0.9533060403541938f,
    0.9569403357322089f,
    0.9604305194155658f,
    0.9637760657954398f,
    0.9669764710448521f,
    0.970031253194544f,
    0.9729399522055601f,
    0.9757021300385286f,
    0.9783173707196277f,
    0.9807852804032304f,
    0.9831054874312163f,
    0.9852776423889412f,
    0.9873014181578584f,
    0.989176509964781f,
    0.99090263542778f,
    0.99247953459871f,
    0.9939069700023561f,
    0.9951847266721968f,
    0.996312612182778f,
    0.9972904566786902f,
    0.9981181129001492f,
    0.9987954562051724f,
    0.9993223845883495f,
    0.9996988186962042f,
    0.9999247018391445f,
    1.0f,
    0.9999247018391445f,
    0.9996988186962042f,
    0.9993223845883495f,
    0.9987954562051724f,
    0.9981181129001492f,
    0.9972904566786902f,
    0.996312612182778f,
    0.9951847266721969f,
    0.9939069700023561f,
    0.99247953459871f,
    0.99090263542778f,
    0.989176509964781f,
    0.9873014181578584f,
    0.9852776423889412f,
    0.9831054874312163f,
    0.9807852804032304f,
    0.9783173707196277f,
    0.9757021300385286f,
    0.9729399522055602f,
    0.970031253194544f,
    0.9669764710448521f,
    0.9637760657954398f,
    0.9604305194155659f,
    0.9569403357322089f,
    0.9533060403541939f,
    0.9495281805930367f,
    0.9456073253805214f,
    0.9415440651830208f,
    0.937339011912575f,
    0.9329927988347388f,
    0.9285060804732156f,
    0.9238795325112867f,
    0.9191138516900578f,
    0.9142097557035307f,
    0.9091679830905225f,
    0.9039892931234434f,
    0.8986744656939539f,
    0.8932243011955152f,
    0.8876396204028539f,
    0.881921264348355f,
    0.8760700941954066f,
    0.8700869911087115f,
    0.8639728561215868f,
    0.8577286100002721f,
    0.8513551931052652f,
    0.8448535652497072f,
    0.8382247055548382f,
    0.8314696123025453f,
    0.8245893027850252f,
    0.8175848131515837f,
    0.8104571982525948f,
    0.8032075314806449f,
    0.7958369046088836f,
    0.7883464276266063f,
    0.7807372285720946f,
    0.7730104533627371f,
    0.7651672656224591f,
    0.7572088465064847f,
    0.7491363945234593f,
    0.740951125354959f,
    0.7326542716724128f,
    0.7242470829514669f,
    0.7157308252838187f,
    0.7071067811865476f,
    0.6983762494089729f,
    0.689540544737067f,
    0.6806009977954532f,
    0.6715589548470186f,
    0.662415777590172f,
    0.6531728429537766f,
    0.6438315428897914f,
    0.6343932841636455f,
    0.6248594881423863f,
    0.6152315905806269f,
    0.6055110414043257f,
    0.5956993044924335f,
    0.585797857456439f,
    0.5758081914178454f,
    0.5657318107836135f,
    0.5555702330196022f,
    0.5453249884220464f,
    0.5349976198870972f,
    0.524589682678469f,
    0.5141027441932218f,
    0.5035383837257176f,
    0.49289819222978415f,
    0.4821837720791229f,
    0.4713967368259978f,
    0.4605387109582402f,
    0.4496113296546069f,
    0.43861623853852755f,
    0.42755509343028203f,
    0.41642956009763715f,
    0.4052413140049899f,
    0.39399204006104815f,
    0.3826834323650899f,
    0.3713171939518377f,
    0.35989503653498833f,
    0.3484186802494348f,
    0.33688985339222033f,
    0.32531029216226326f,
    0.3136817403988914f,
    0.30200594931922803f,
    0.2902846772544624f,
    0.27851968938505317f,
    0.2667127574748985f,
    0.2548656596045147f,
    0.24298017990326407f,
    0.23105810828067133f,
    0.21910124015687005f,
    0.20711137619221884f,
    0.1950903220161286f,
    0.1830398879551409f,
    0.17096188876030122f,
    0.15885814333386147f,
    0.1467304744553618f,
    0.13458070850712628f,
    0.12241067519921635f,
    0.11022220729388324f,
    0.09801714032956083f,
    0.08579731234444016f,
    0.07356456359966773f,
    0.06132073630220849f,
    0.049067674327417966f,
    0.03680722294135883f,
    0.024541228522912326f,
    0.012271538285720007f,
};

//  ABOUT
// 8bit Wave to 32bit Real
constexpr inline void w8r32 (
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


//  ABOUT
// 8bit Normal to 32bit Real
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


//  ABOUT
// 16bit Wave to 32bit Real
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


//  ABOUT
// 16bit Normal to 32bit Real
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
