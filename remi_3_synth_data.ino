/*
 * Module:       remi_synth2_data.c
 *
 * Overview:     Patch parameter tables and waveform definitions.
 *
 * ================================================================================================
 */
#include "remi_3_synth.h"


// Pre-defined Patch "Programs" -- Array of patch parameter tables in flash memory
// ```````````````````````````````````````````````````````````````````````````````
const  PatchParamTable_t  g_PatchProgram[] =
{
    //--------  R E C O R D E R S,  F L U T E S   &   P I P E S  ---------
    {
        10,     // Patch ID Number
        "Recorder",
        13,     // W1: OSC1 Wave-table ID (0..99) = recorder_alto
        13,     // W2: OSC2 Wave-table ID (0..99) = recorder_alto
        0,      // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        50,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        10,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        11,     // Patch ID Number
        "Recorder celeste",
        2,      // W1: OSC1 Wave-table ID (0..99) = square_wave
        13,     // W2: OSC2 Wave-table ID (0..99) = recorder_alto
        -3,     // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        20,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        30,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        10,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },    

    {
        12,     // Patch ID Number
        "Clean Bright Flute",
        6,      // W1: OSC1 Wave-table ID (0..99)
        6,      // W2: OSC2 Wave-table ID (0..99)
        0,      // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        50,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        10,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        13,     // Patch ID Number
        "Mellow Pipe",
        12,     // W1: OSC1 Wave-table ID (0..99)
        12,     // W2: OSC2 Wave-table ID (0..99)
        -3,     // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        20,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        10,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },

    //---------------  R E E D E D   W O O D W I N D S  --------------------
    {
        21,     // Patch ID Number
        "Reeded Woodwind",  // Breath-controlled wave morph... sax-like
        2,      // W1: OSC1 Wave-table ID (0..99)
        9,      // W2: OSC2 Wave-table ID (0..99)
        -3,     // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time (5..5000+ ms)

        3,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        80,     // CS: Contour Env Start level (0..100 %)
        5,      // CD: Contour Env Delay time (5..5000+ ms)
        500,    // CR: Contour Env Ramp time (5..5000+ ms)
        50,     // CH: Contour Env Hold level (0..100 %)

        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Ctrl (0:Fixed, 1:Contour, 2:Env+, 3:Env-, 4:LFO, 5:Modn)
        9700,   // FR: Filter Resonance x10000  (0..9990, 0:Bypass)
        15,     // FF: Filter Freq/Offset (semitone#, 0..108)
        1,      // FT: Filter Note Tracking (0:Off, 1:On)

        20,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        23,     // Patch ID Number
        "Saxophoney",  // Sounds too simple... Needs work !!!  ***********************************
        9,      // W1: OSC1 Wave-table ID (0..99)
        9,      // W2: OSC2 Wave-table ID (0..99)
        0,      // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        20,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },

    {
        24,     // Patch ID Number
        "Mellow Reed",
        23,     // W1: OSC1 Wave-table ID (0..99)
        23,     // W2: OSC2 Wave-table ID (0..99)
        -3,     // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        20,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        10,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },

    {
        25,     // Patch ID Number   
        "Psychedelic Oboe",
        9,      // W1: OSC1 Wave-table ID (0..99)
        10,     // W2: OSC2 Wave-table ID (0..99)
        -7,     // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        300,    // VR: Vibrato Ramp time, (5..5000+ ms)

        3,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        50,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        10,     // CS: Contour Env Start level (0..100 %)
        50,     // CD: Contour Env Delay time (5..5000+ ms)
        500,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        20,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },

    {
        26,     // Patch ID Number  
        "Electric Clarinet",  
        12,     // W1: OSC1 Wave-table ID (0..99)
        11,     // W2: OSC2 Wave-table ID (0..99)
        3,      // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        3,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        50,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        100,    // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        9700,   // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        9,      // FF: Filter Freq/Offset (semitone#, 0..108)
        1,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        20,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    //----------------  B O W E D   S T R I N G   I N S T R U M E N T S  ------------
    {
        30,     // Patch ID Number
        "Vinyl-cello",
        3,      // W1: OSC1 Wave-table ID (0..99) 
        3,      // W2: OSC2 Wave-table ID (0..99)   
        3,      // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        300,    // VR: Vibrato Ramp time, (5..5000+ ms)

        1,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        50,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        20,     // CS: Contour Env Start level (0..100 %)
        10,     // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        9500,   // FR: Filter Resonance x10000  (0..9990, 0:Bypass)
        60,     // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        30,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        10,     // ED: Envelope Decay time (5..5000+ ms)
        10,     // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },

    //------------------  O R G A N S   &  A C C O R D I O N  -----------------
    {
        40,     // Patch ID Number
        "Jazz Organ celeste",  // Experiment with wave-tables  **************************
        14,     // W1: OSC1 Wave-table ID (0..99) = jazz_organ_v1
        14,     // W2: OSC2 Wave-table ID (0..99) = jazz_organ_v1
        -6,     // OD: OSC2 Detune, cents (+/-1200)
        50,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        30,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        5,      // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        5,      // ED: Envelope Decay time (5..5000+ ms)
        10,     // ER: Envelope Release time (5..5000+ ms)
        80,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        41,     // Patch ID Number
        "Jazz-Rock Organ 1",  // Classic Hammond rock organ tone.  Slightly percussive.
        17,     // W1: OSC1 Wave-table ID (0..99)   
        17,     // W2: OSC2 Wave-table ID (0..99) 
        0,      // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        50,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        5,      // EA: Envelope Attack time (5..5000+ ms)
        50,     // EP: Envelope Peak time (0..5000+ ms)
        100,    // ED: Envelope Decay time (5..5000+ ms)
        50,     // ER: Envelope Release time (5..5000+ ms)
        70,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },

    {
        42,     // Patch ID Number
        "Jazz-Rock Organ 2",  // Classic Hammond rock organ tone.  Slightly percussive.
        18,     // W1: OSC1 Wave-table ID (0..99)   
        18,     // W2: OSC2 Wave-table ID (0..99)   
        0,      // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        25,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        5,      // EA: Envelope Attack time (5..5000+ ms)
        50,     // EP: Envelope Peak time (0..5000+ ms)
        100,    // ED: Envelope Decay time (5..5000+ ms)
        50,     // ER: Envelope Release time (5..5000+ ms)
        70,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        43,     // Patch ID Number
        "Jazz-Rock Organ 3",  // Classic Hammond rock organ tone.  Slightly percussive.
        14,     // W1: OSC1 Wave-table ID (0..99)   
        14,     // W2: OSC2 Wave-table ID (0..99)   
        -5,     // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        25,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        5,      // EA: Envelope Attack time (5..5000+ ms)
        50,     // EP: Envelope Peak time (0..5000+ ms)
        100,    // ED: Envelope Decay time (5..5000+ ms)
        50,     // ER: Envelope Release time (5..5000+ ms)
        70,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        44,     // Patch ID Number
        "Theatre Organ",  // "All stops out" -- rich & deep harmonic content
        21,     // W1: OSC1 Wave-table ID (0..99)   
        21,     // W2: OSC2 Wave-table ID (0..99)   
        -5,     // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        20,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        5,      // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        5,      // ED: Envelope Decay time (5..5000+ ms)
        10,     // ER: Envelope Release time (5..5000+ ms)
        90,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        45,     // Patch ID Number
        "Pink Floyd Organ",  // Essential Preset Patch! -- complex etherial flutey tone
        20,     // W1: OSC1 Wave-table ID (0..99)   
        20,     // W2: OSC2 Wave-table ID (0..99)   
        -5,     // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        50,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        10,     // EA: Envelope Attack time (5..5000+ ms)
        50,     // EP: Envelope Peak time (0..5000+ ms)
        100,    // ED: Envelope Decay time (5..5000+ ms)
        10,     // ER: Envelope Release time (5..5000+ ms)
        70,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        46,     // Patch ID Number
        "Bauer Organ",  // Bright, rich tone  (experiment with detune, contour, etc)
        22,     // W1: OSC1 Wave-table ID (0..99)   
        23,     // W2: OSC2 Wave-table ID (0..99) -- experiment with morph  *************
        7,      // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        3,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        20,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        10,     // EA: Envelope Attack time (5..5000+ ms)
        50,     // EP: Envelope Peak time (0..5000+ ms)
        100,    // ED: Envelope Decay time (5..5000+ ms)
        10,     // ER: Envelope Release time (5..5000+ ms)
        70,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        47,     // Patch ID Number
        "Hammond Organ 1",  // Classic Hammond organ tone.  Slightly percussive.
        15,     // W1: OSC1 Wave-table ID (0..99)   
        15,     // W2: OSC2 Wave-table ID (0..99)   
        -5,     // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        25,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        5,      // EA: Envelope Attack time (5..5000+ ms)
        50,     // EP: Envelope Peak time (0..5000+ ms)
        100,    // ED: Envelope Decay time (5..5000+ ms)
        50,     // ER: Envelope Release time (5..5000+ ms)
        70,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
    
    {
        48,     // Patch ID Number
        "Hammond Organ 2",  // Classic Hammond organ tone.  Slightly percussive.
        16,     // W1: OSC1 Wave-table ID (0..99)   
        16,     // W2: OSC2 Wave-table ID (0..99)   
        -5,     // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        30,     // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        25,     // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        200,    // CR: Contour Env Ramp time (5..5000+ ms)
        80,     // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9990, 0:Bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        5,      // EA: Envelope Attack time (5..5000+ ms)
        50,     // EP: Envelope Peak time (0..5000+ ms)
        100,    // ED: Envelope Decay time (5..5000+ ms)
        50,     // ER: Envelope Release time (5..5000+ ms)
        70,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
   
    //---------------  T E S T   &   D E M O   P A T C H E S  ------------------------
    {
        90,     // Patch ID Number
        "Test Patch (ID 90)",  // NB: Do not edit -- patch is used by diagnostics
        1,      // W1: OSC1 Wave-table ID (0..99)  <------ sinewave
        3,      // W2: OSC2 Wave-table ID (0..99)  <------ sawtooth
        0,      // OD: OSC2 Detune, cents (+/-1200)
        70,     // LF: LFO Freq x10 Hz (1..250)
        0,      // VD: Vibrato Depth, cents (0..200)
        500,    // VR: Vibrato Ramp time, (5..5000+ ms)

        0,      // MC: Mixer Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // ML: Mixer OSC2 Level in Fixed mode (0..100 %)
        0,      // CS: Contour Env Start level (0..100 %)
        0,      // CD: Contour Env Delay time (5..5000+ ms)
        1000,   // CR: Contour Env Ramp time (5..5000+ ms)
        100,    // CH: Contour Env Hold level (0..100 %)
        
        0,      // NM: Noise Mode (0:Off, 1:Noise, 2:Add wave, 3:Mix wave; +4:Pitch)
        0,      // NC: Noise Level Ctrl (0:Fixed, 1:Ampld.Env, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FC: Filter Control (0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn)
        0,      // FR: Filter Resonance x10000 (0..9999, 0:Off/bypass)
        0,      // FF: Filter Freq/Offset (semitone#, 0..108)
        0,      // FT: Filter Note Tracking (0:Off, 1:On)
                
        50,     // EA: Envelope Attack time (5..5000+ ms)
        0,      // EP: Envelope Peak time (0..5000+ ms)
        1000,   // ED: Envelope Decay time (5..5000+ ms)
        100,    // ER: Envelope Release time (5..5000+ ms)
        80,     // ES: Envelope Sustain level (0..100 %)
        100,    // AL: Audio Level Adjust (10..250 %)
    },
	
};


// Function returns the number of Predefined Patch definitions in flash PM
//
int  GetNumberOfPatchesDefined()
{
    return  sizeof(g_PatchProgram) / sizeof(g_PatchProgram[0]);
}


// ================================================================================================
//                   F L A S H - B A S E D   W A V E - T A B L E S
/*
 * Wave-table definition ...
 * Waveform name: pure_sine_wave, size: 1260 samples
 * Osc. Freq. Divider:   1.0000
 * 
 * NB: This wave-table is also used as a general-purpose sine-wave LUT (e.g. for LFO).
 * Peak value:  +/-31,680
 */
const  int16  g_sinewave[] =
{
         0,    157,    315,    473,    631,    789,    947,   1104,   1263,   1420,
      1579,   1736,   1893,   2051,   2209,   2367,   2524,   2681,   2839,   2996,
      3154,   3310,   3467,   3625,   3781,   3938,   4095,   4252,   4408,   4564,
      4721,   4877,   5033,   5189,   5345,   5500,   5655,   5811,   5966,   6122,
      6276,   6432,   6586,   6740,   6895,   7048,   7203,   7356,   7510,   7663,
      7817,   7969,   8122,   8275,   8427,   8579,   8731,   8883,   9034,   9186,
      9337,   9488,   9638,   9789,   9939,  10089,  10238,  10388,  10537,  10686,
     10834,  10983,  11130,  11279,  11426,  11573,  11720,  11867,  12013,  12159,
     12304,  12450,  12595,  12740,  12884,  13029,  13172,  13316,  13460,  13602,
     13745,  13886,  14029,  14170,  14311,  14452,  14592,  14733,  14872,  15011,
     15150,  15289,  15427,  15564,  15702,  15840,  15975,  16112,  16247,  16383,
     16518,  16652,  16787,  16921,  17054,  17187,  17320,  17451,  17583,  17715,
     17845,  17975,  18106,  18234,  18364,  18492,  18620,  18747,  18875,  19002,
     19127,  19253,  19379,  19503,  19627,  19751,  19875,  19998,  20119,  20241,
     20363,  20484,  20603,  20723,  20843,  20961,  21080,  21197,  21314,  21431,
     21547,  21663,  21778,  21892,  22006,  22119,  22232,  22344,  22456,  22568,
     22677,  22787,  22897,  23006,  23114,  23222,  23329,  23436,  23542,  23648,
     23752,  23857,  23959,  24063,  24165,  24267,  24368,  24469,  24569,  24668,
     24767,  24865,  24963,  25060,  25156,  25252,  25347,  25442,  25536,  25629,
     25722,  25813,  25905,  25995,  26085,  26174,  26263,  26351,  26438,  26525,
     26611,  26697,  26781,  26865,  26948,  27031,  27114,  27195,  27275,  27355,
     27434,  27514,  27592,  27669,  27745,  27821,  27897,  27971,  28044,  28117,
     28190,  28262,  28333,  28404,  28473,  28542,  28610,  28678,  28744,  28810,
     28876,  28940,  29004,  29067,  29129,  29192,  29252,  29312,  29372,  29431,
     29489,  29546,  29603,  29659,  29714,  29769,  29822,  29875,  29927,  29979,
     30029,  30080,  30128,  30177,  30224,  30272,  30317,  30363,  30408,  30452,
     30494,  30537,  30579,  30620,  30660,  30699,  30738,  30776,  30813,  30849,
     30885,  30919,  30954,  30987,  31019,  31051,  31082,  31112,  31141,  31170,
     31197,  31225,  31251,  31277,  31301,  31325,  31348,  31371,  31392,  31413,
     31433,  31453,  31471,  31488,  31505,  31521,  31537,  31552,  31566,  31579,
     31590,  31602,  31612,  31622,  31631,  31640,  31647,  31654,  31660,  31665,
     31670,  31673,  31676,  31678,  31679,  31680,  31679,  31678,  31676,  31673,
     31670,  31665,  31660,  31654,  31647,  31640,  31631,  31622,  31612,  31602,
     31590,  31579,  31566,  31552,  31537,  31521,  31505,  31488,  31471,  31453,
     31433,  31413,  31392,  31371,  31348,  31325,  31301,  31277,  31251,  31225,
     31197,  31170,  31141,  31112,  31082,  31051,  31019,  30987,  30954,  30919,
     30885,  30849,  30813,  30776,  30738,  30699,  30660,  30620,  30579,  30537,
     30494,  30452,  30408,  30363,  30317,  30272,  30224,  30177,  30128,  30080,
     30029,  29979,  29927,  29875,  29822,  29769,  29714,  29659,  29603,  29546,
     29489,  29431,  29372,  29312,  29252,  29192,  29129,  29067,  29004,  28940,
     28876,  28810,  28744,  28678,  28610,  28542,  28473,  28404,  28333,  28262,
     28190,  28117,  28044,  27971,  27897,  27821,  27745,  27669,  27592,  27514,
     27434,  27355,  27275,  27195,  27114,  27031,  26948,  26865,  26781,  26697,
     26611,  26525,  26438,  26351,  26263,  26174,  26085,  25995,  25905,  25813,
     25722,  25629,  25536,  25442,  25347,  25252,  25156,  25060,  24963,  24865,
     24767,  24668,  24569,  24469,  24368,  24267,  24165,  24063,  23959,  23857,
     23752,  23648,  23542,  23436,  23329,  23222,  23114,  23006,  22897,  22787,
     22677,  22568,  22456,  22344,  22232,  22119,  22006,  21891,  21778,  21663,
     21547,  21431,  21314,  21197,  21080,  20961,  20843,  20723,  20603,  20484,
     20363,  20241,  20119,  19998,  19875,  19751,  19627,  19503,  19379,  19253,
     19127,  19002,  18875,  18747,  18620,  18492,  18364,  18234,  18106,  17975,
     17845,  17715,  17583,  17451,  17320,  17187,  17054,  16921,  16787,  16652,
     16518,  16383,  16247,  16112,  15975,  15840,  15702,  15564,  15427,  15289,
     15150,  15011,  14872,  14733,  14592,  14452,  14311,  14170,  14029,  13886,
     13745,  13602,  13460,  13316,  13172,  13029,  12884,  12740,  12595,  12450,
     12304,  12159,  12013,  11867,  11720,  11573,  11426,  11279,  11130,  10983,
     10834,  10686,  10537,  10388,  10238,  10089,   9939,   9789,   9638,   9488,
      9337,   9186,   9034,   8883,   8731,   8579,   8427,   8275,   8122,   7969,
      7817,   7663,   7510,   7356,   7203,   7048,   6895,   6740,   6586,   6432,
      6276,   6122,   5966,   5811,   5655,   5500,   5345,   5189,   5033,   4877,
      4721,   4564,   4408,   4252,   4095,   3938,   3781,   3625,   3467,   3310,
      3154,   2996,   2839,   2681,   2524,   2367,   2209,   2051,   1893,   1736,
      1579,   1420,   1263,   1104,    947,    789,    631,    473,    315,    157,
         0,   -157,   -315,   -473,   -631,   -789,   -947,  -1104,  -1263,  -1420,
     -1579,  -1736,  -1893,  -2051,  -2209,  -2367,  -2524,  -2681,  -2839,  -2996,
     -3154,  -3310,  -3467,  -3625,  -3781,  -3938,  -4095,  -4252,  -4408,  -4564,
     -4721,  -4877,  -5033,  -5189,  -5345,  -5500,  -5655,  -5811,  -5966,  -6122,
     -6276,  -6432,  -6586,  -6740,  -6895,  -7048,  -7203,  -7356,  -7510,  -7663,
     -7817,  -7969,  -8122,  -8275,  -8427,  -8579,  -8731,  -8883,  -9034,  -9186,
     -9337,  -9488,  -9638,  -9789,  -9939, -10089, -10238, -10388, -10537, -10686,
    -10834, -10983, -11131, -11279, -11426, -11573, -11720, -11867, -12013, -12159,
    -12304, -12450, -12595, -12740, -12884, -13029, -13172, -13316, -13460, -13602,
    -13745, -13886, -14029, -14170, -14311, -14452, -14592, -14733, -14872, -15011,
    -15150, -15289, -15427, -15564, -15702, -15840, -15975, -16112, -16247, -16383,
    -16518, -16652, -16787, -16921, -17054, -17187, -17320, -17451, -17583, -17715,
    -17845, -17975, -18106, -18234, -18364, -18492, -18620, -18747, -18875, -19002,
    -19127, -19253, -19379, -19503, -19627, -19751, -19875, -19998, -20119, -20241,
    -20363, -20484, -20603, -20723, -20843, -20961, -21080, -21197, -21314, -21431,
    -21547, -21663, -21778, -21892, -22006, -22119, -22232, -22344, -22456, -22568,
    -22677, -22787, -22897, -23006, -23114, -23222, -23329, -23436, -23542, -23648,
    -23753, -23857, -23959, -24063, -24165, -24267, -24368, -24469, -24569, -24668,
    -24767, -24865, -24963, -25060, -25156, -25252, -25347, -25442, -25536, -25629,
    -25722, -25813, -25905, -25995, -26085, -26174, -26263, -26351, -26438, -26525,
    -26611, -26697, -26781, -26865, -26948, -27031, -27114, -27195, -27275, -27355,
    -27434, -27514, -27592, -27669, -27745, -27821, -27897, -27971, -28044, -28117,
    -28190, -28262, -28333, -28404, -28473, -28542, -28610, -28678, -28744, -28810,
    -28876, -28940, -29004, -29067, -29129, -29192, -29252, -29312, -29372, -29431,
    -29489, -29546, -29603, -29659, -29714, -29769, -29822, -29875, -29927, -29979,
    -30029, -30080, -30128, -30177, -30224, -30272, -30317, -30363, -30408, -30452,
    -30494, -30537, -30579, -30620, -30660, -30699, -30738, -30776, -30813, -30849,
    -30885, -30919, -30954, -30987, -31019, -31051, -31082, -31112, -31141, -31170,
    -31197, -31225, -31251, -31277, -31301, -31325, -31348, -31371, -31392, -31413,
    -31433, -31453, -31471, -31488, -31505, -31521, -31537, -31552, -31566, -31579,
    -31590, -31602, -31612, -31622, -31631, -31640, -31647, -31654, -31660, -31665,
    -31670, -31673, -31676, -31678, -31679, -31680, -31679, -31678, -31676, -31673,
    -31670, -31665, -31660, -31654, -31647, -31640, -31631, -31622, -31612, -31602,
    -31590, -31579, -31566, -31552, -31537, -31521, -31505, -31488, -31471, -31453,
    -31433, -31413, -31392, -31371, -31348, -31325, -31301, -31277, -31251, -31225,
    -31197, -31170, -31141, -31112, -31082, -31051, -31019, -30987, -30954, -30919,
    -30885, -30849, -30813, -30776, -30738, -30699, -30660, -30620, -30579, -30537,
    -30494, -30452, -30408, -30363, -30317, -30272, -30224, -30177, -30128, -30080,
    -30029, -29979, -29927, -29875, -29822, -29769, -29714, -29659, -29603, -29546,
    -29489, -29431, -29372, -29312, -29252, -29192, -29129, -29067, -29004, -28940,
    -28876, -28810, -28744, -28678, -28610, -28542, -28473, -28404, -28333, -28262,
    -28190, -28117, -28044, -27971, -27897, -27821, -27745, -27669, -27592, -27514,
    -27434, -27355, -27275, -27195, -27114, -27031, -26948, -26865, -26781, -26697,
    -26611, -26525, -26438, -26351, -26263, -26174, -26085, -25995, -25905, -25813,
    -25722, -25629, -25536, -25442, -25347, -25252, -25156, -25060, -24963, -24865,
    -24767, -24668, -24569, -24469, -24368, -24267, -24165, -24063, -23959, -23857,
    -23752, -23648, -23542, -23436, -23329, -23222, -23114, -23006, -22897, -22787,
    -22677, -22568, -22456, -22344, -22232, -22119, -22006, -21891, -21778, -21663,
    -21547, -21431, -21314, -21197, -21080, -20961, -20843, -20723, -20603, -20484,
    -20363, -20241, -20119, -19998, -19875, -19751, -19627, -19503, -19379, -19253,
    -19127, -19002, -18875, -18747, -18620, -18492, -18364, -18234, -18106, -17975,
    -17845, -17715, -17583, -17451, -17320, -17187, -17054, -16921, -16787, -16652,
    -16518, -16383, -16247, -16112, -15975, -15839, -15702, -15564, -15427, -15289,
    -15150, -15011, -14872, -14733, -14592, -14452, -14311, -14170, -14029, -13886,
    -13745, -13602, -13460, -13316, -13172, -13029, -12884, -12740, -12595, -12450,
    -12304, -12159, -12013, -11867, -11720, -11573, -11426, -11279, -11130, -10983,
    -10834, -10686, -10537, -10388, -10238, -10089,  -9939,  -9789,  -9638,  -9488,
     -9337,  -9186,  -9034,  -8883,  -8731,  -8579,  -8427,  -8275,  -8122,  -7969,
     -7817,  -7663,  -7510,  -7356,  -7203,  -7048,  -6895,  -6740,  -6586,  -6432,
     -6276,  -6122,  -5966,  -5811,  -5655,  -5500,  -5345,  -5189,  -5033,  -4877,
     -4721,  -4564,  -4408,  -4252,  -4095,  -3939,  -3781,  -3625,  -3467,  -3310,
     -3154,  -2996,  -2839,  -2681,  -2524,  -2367,  -2209,  -2051,  -1893,  -1736,
     -1579,  -1420,  -1263,  -1104,   -947,   -789,   -631,   -473,   -315,   -157
};

/*
 * Waveform name: square_wave, size: 1260 samples
 * Anti-Alias filter params: K = 50, N = 2
 */
const  int16  square_wave[] =
{
    -30400, -30400, -30375, -30327, -30254, -30156, -30035, -29889, -29719, -29524,
    -29305, -29062, -28794, -28503, -28186, -27846, -27481, -27092, -26679, -26241,
    -25779, -25292, -24782, -24247, -23687, -23104, -22496, -21863, -21207, -20526,
    -19820, -19091, -18337, -17559, -16756, -15929, -15078, -14202, -13303, -12378,
    -11430, -10457,  -9460,  -8439,  -7393,  -6323,  -5228,  -4110,  -2967,  -1799,
      -608,    608,   1799,   2967,   4110,   5228,   6323,   7393,   8439,   9460,
     10457,  11430,  12378,  13303,  14202,  15078,  15929,  16756,  17559,  18337,
     19091,  19820,  20526,  21207,  21863,  22496,  23104,  23687,  24247,  24782,
     25292,  25779,  26241,  26679,  27092,  27481,  27846,  28186,  28503,  28794,
     29062,  29305,  29524,  29719,  29889,  30035,  30156,  30254,  30327,  30375,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,  30400,
     30400,  30400,  30375,  30327,  30254,  30156,  30035,  29889,  29719,  29524,
     29305,  29062,  28794,  28503,  28186,  27846,  27481,  27092,  26679,  26241,
     25779,  25292,  24782,  24247,  23687,  23104,  22496,  21863,  21207,  20526,
     19820,  19091,  18337,  17559,  16756,  15929,  15078,  14202,  13303,  12378,
     11430,  10457,   9460,   8439,   7393,   6323,   5228,   4110,   2967,   1799,
       608,   -608,  -1799,  -2967,  -4110,  -5228,  -6323,  -7393,  -8439,  -9460,
    -10457, -11430, -12378, -13303, -14202, -15078, -15929, -16756, -17559, -18337,
    -19091, -19820, -20526, -21207, -21863, -22496, -23104, -23687, -24247, -24782,
    -25292, -25779, -26241, -26679, -27092, -27481, -27846, -28186, -28503, -28794,
    -29062, -29305, -29524, -29719, -29889, -30035, -30156, -30254, -30327, -30375,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400,
    -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400, -30400
};

/*
 * Waveform name: sawtooth_wave, size: 1260 samples
 * Anti-Alias filter params: K = 60, N = 2
 */
const  int16  sawtooth_wave[] =
{
     27455,  27503,  27534,  27549,  27546,  27527,  27491,  27438,  27368,  27281,
     27177,  27056,  26919,  26765,  26593,  26405,  26200,  25978,  25739,  25483,
     25211,  24921,  24615,  24292,  23951,  23594,  23220,  22830,  22422,  21997,
     21556,  21097,  20622,  20130,  19621,  19095,  18552,  17992,  17416,  16822,
     16212,  15585,  14940,  14279,  13601,  12907,  12195,  11466,  10721,   9958,
      9179,   8383,   7570,   6740,   5893,   5029,   4149,   3251,   2337,   1406,
       457,   -507,  -1455,  -2386,  -3300,  -4198,  -5079,  -5942,  -6789,  -7619,
     -8432,  -9228, -10008, -10770, -11515, -12244, -12956, -13651, -14328, -14990,
    -15634, -16261, -16871, -17465, -18041, -18601, -19144, -19670, -20179, -20671,
    -21146, -21605, -22046, -22471, -22879, -23270, -23644, -24001, -24341, -24664,
    -24970, -25260, -25533, -25788, -26027, -26249, -26454, -26642, -26814, -26968,
    -27106, -27226, -27330, -27417, -27487, -27540, -27576, -27595, -27598, -27583,
    -27552, -27504, -27456, -27407, -27359, -27311, -27263, -27214, -27166, -27118,
    -27069, -27021, -26973, -26925, -26876, -26828, -26780, -26732, -26683, -26635,
    -26587, -26539, -26490, -26442, -26394, -26346, -26297, -26249, -26201, -26153,
    -26104, -26056, -26008, -25960, -25911, -25863, -25815, -25767, -25718, -25670,
    -25622, -25574, -25525, -25477, -25429, -25381, -25332, -25284, -25236, -25188,
    -25139, -25091, -25043, -24995, -24946, -24898, -24850, -24802, -24753, -24705,
    -24657, -24609, -24560, -24512, -24464, -24416, -24367, -24319, -24271, -24223,
    -24174, -24126, -24078, -24029, -23981, -23933, -23885, -23836, -23788, -23740,
    -23692, -23643, -23595, -23547, -23499, -23450, -23402, -23354, -23306, -23257,
    -23209, -23161, -23113, -23064, -23016, -22968, -22920, -22871, -22823, -22775,
    -22727, -22678, -22630, -22582, -22534, -22485, -22437, -22389, -22341, -22292,
    -22244, -22196, -22148, -22099, -22051, -22003, -21955, -21906, -21858, -21810,
    -21762, -21713, -21665, -21617, -21569, -21520, -21472, -21424, -21376, -21327,
    -21279, -21231, -21183, -21134, -21086, -21038, -20989, -20941, -20893, -20845,
    -20796, -20748, -20700, -20652, -20603, -20555, -20507, -20459, -20410, -20362,
    -20314, -20266, -20217, -20169, -20121, -20073, -20024, -19976, -19928, -19880,
    -19831, -19783, -19735, -19687, -19638, -19590, -19542, -19494, -19445, -19397,
    -19349, -19301, -19252, -19204, -19156, -19108, -19059, -19011, -18963, -18915,
    -18866, -18818, -18770, -18722, -18673, -18625, -18577, -18529, -18480, -18432,
    -18384, -18336, -18287, -18239, -18191, -18143, -18094, -18046, -17998, -17949,
    -17901, -17853, -17805, -17756, -17708, -17660, -17612, -17563, -17515, -17467,
    -17419, -17370, -17322, -17274, -17226, -17177, -17129, -17081, -17033, -16984,
    -16936, -16888, -16840, -16791, -16743, -16695, -16647, -16598, -16550, -16502,
    -16454, -16405, -16357, -16309, -16261, -16212, -16164, -16116, -16068, -16019,
    -15971, -15923, -15875, -15826, -15778, -15730, -15682, -15633, -15585, -15537,
    -15489, -15440, -15392, -15344, -15296, -15247, -15199, -15151, -15103, -15054,
    -15006, -14958, -14909, -14861, -14813, -14765, -14716, -14668, -14620, -14572,
    -14523, -14475, -14427, -14379, -14330, -14282, -14234, -14186, -14137, -14089,
    -14041, -13993, -13944, -13896, -13848, -13800, -13751, -13703, -13655, -13607,
    -13558, -13510, -13462, -13414, -13365, -13317, -13269, -13221, -13172, -13124,
    -13076, -13028, -12979, -12931, -12883, -12835, -12786, -12738, -12690, -12642,
    -12593, -12545, -12497, -12449, -12400, -12352, -12304, -12256, -12207, -12159,
    -12111, -12063, -12014, -11966, -11918, -11869, -11821, -11773, -11725, -11676,
    -11628, -11580, -11532, -11483, -11435, -11387, -11339, -11290, -11242, -11194,
    -11146, -11097, -11049, -11001, -10953, -10904, -10856, -10808, -10760, -10711,
    -10663, -10615, -10567, -10518, -10470, -10422, -10374, -10325, -10277, -10229,
    -10181, -10132, -10084, -10036,  -9988,  -9939,  -9891,  -9843,  -9795,  -9746,
     -9698,  -9650,  -9602,  -9553,  -9505,  -9457,  -9409,  -9360,  -9312,  -9264,
     -9216,  -9167,  -9119,  -9071,  -9023,  -8974,  -8926,  -8878,  -8829,  -8781,
     -8733,  -8685,  -8636,  -8588,  -8540,  -8492,  -8443,  -8395,  -8347,  -8299,
     -8250,  -8202,  -8154,  -8106,  -8057,  -8009,  -7961,  -7913,  -7864,  -7816,
     -7768,  -7720,  -7671,  -7623,  -7575,  -7527,  -7478,  -7430,  -7382,  -7334,
     -7285,  -7237,  -7189,  -7141,  -7092,  -7044,  -6996,  -6948,  -6899,  -6851,
     -6803,  -6755,  -6706,  -6658,  -6610,  -6562,  -6513,  -6465,  -6417,  -6369,
     -6320,  -6272,  -6224,  -6176,  -6127,  -6079,  -6031,  -5983,  -5934,  -5886,
     -5838,  -5789,  -5741,  -5693,  -5645,  -5596,  -5548,  -5500,  -5452,  -5403,
     -5355,  -5307,  -5259,  -5210,  -5162,  -5114,  -5066,  -5017,  -4969,  -4921,
     -4873,  -4824,  -4776,  -4728,  -4680,  -4631,  -4583,  -4535,  -4487,  -4438,
     -4390,  -4342,  -4294,  -4245,  -4197,  -4149,  -4101,  -4052,  -4004,  -3956,
     -3908,  -3859,  -3811,  -3763,  -3715,  -3666,  -3618,  -3570,  -3522,  -3473,
     -3425,  -3377,  -3329,  -3280,  -3232,  -3184,  -3136,  -3087,  -3039,  -2991,
     -2943,  -2894,  -2846,  -2798,  -2750,  -2701,  -2653,  -2605,  -2557,  -2508,
     -2460,  -2412,  -2364,  -2315,  -2267,  -2219,  -2171,  -2122,  -2074,  -2026,
     -1978,  -1929,  -1881,  -1833,  -1785,  -1736,  -1688,  -1640,  -1592,  -1543,
     -1495,  -1447,  -1399,  -1350,  -1302,  -1254,  -1206,  -1157,  -1109,  -1061,
     -1013,   -965,   -916,   -868,   -820,   -772,   -723,   -675,   -627,   -579,
      -530,   -482,   -434,   -386,   -338,   -289,   -241,   -193,   -145,    -96,
       -48,      0,     47,     95,    144,    192,    240,    288,    337,    385,
       433,    481,    530,    578,    626,    674,    722,    771,    819,    867,
       915,    964,   1012,   1060,   1108,   1156,   1205,   1253,   1301,   1349,
      1398,   1446,   1494,   1542,   1591,   1639,   1687,   1735,   1784,   1832,
      1880,   1928,   1977,   2025,   2073,   2121,   2170,   2218,   2266,   2314,
      2363,   2411,   2459,   2507,   2556,   2604,   2652,   2700,   2749,   2797,
      2845,   2893,   2942,   2990,   3038,   3086,   3135,   3183,   3231,   3279,
      3328,   3376,   3424,   3472,   3521,   3569,   3617,   3665,   3714,   3762,
      3810,   3858,   3907,   3955,   4003,   4051,   4100,   4148,   4196,   4244,
      4293,   4341,   4389,   4437,   4486,   4534,   4582,   4630,   4679,   4727,
      4775,   4823,   4872,   4920,   4968,   5016,   5065,   5113,   5161,   5209,
      5258,   5306,   5354,   5403,   5451,   5499,   5547,   5596,   5644,   5692,
      5740,   5789,   5837,   5885,   5933,   5982,   6030,   6078,   6126,   6175,
      6223,   6271,   6319,   6368,   6416,   6464,   6512,   6561,   6609,   6657,
      6705,   6754,   6802,   6850,   6898,   6947,   6995,   7043,   7091,   7140,
      7188,   7236,   7284,   7333,   7381,   7429,   7477,   7526,   7574,   7622,
      7670,   7719,   7767,   7815,   7863,   7912,   7960,   8008,   8056,   8105,
      8153,   8201,   8249,   8298,   8346,   8394,   8443,   8491,   8539,   8587,
      8636,   8684,   8732,   8780,   8829,   8877,   8925,   8973,   9022,   9070,
      9118,   9166,   9215,   9263,   9311,   9359,   9408,   9456,   9504,   9552,
      9601,   9649,   9697,   9745,   9794,   9842,   9890,   9938,   9987,  10035,
     10083,  10131,  10180,  10228,  10276,  10324,  10373,  10421,  10469,  10517,
     10566,  10614,  10662,  10710,  10759,  10807,  10855,  10903,  10952,  11000,
     11048,  11096,  11145,  11193,  11241,  11289,  11338,  11386,  11434,  11483,
     11531,  11579,  11627,  11676,  11724,  11772,  11820,  11869,  11917,  11965,
     12013,  12062,  12110,  12158,  12206,  12255,  12303,  12351,  12399,  12448,
     12496,  12544,  12592,  12641,  12689,  12737,  12785,  12834,  12882,  12930,
     12978,  13027,  13075,  13123,  13171,  13220,  13268,  13316,  13364,  13413,
     13461,  13509,  13557,  13606,  13654,  13702,  13750,  13799,  13847,  13895,
     13943,  13992,  14040,  14088,  14136,  14185,  14233,  14281,  14329,  14378,
     14426,  14474,  14523,  14571,  14619,  14667,  14716,  14764,  14812,  14860,
     14909,  14957,  15005,  15053,  15102,  15150,  15198,  15246,  15295,  15343,
     15391,  15439,  15488,  15536,  15584,  15632,  15681,  15729,  15777,  15825,
     15874,  15922,  15970,  16018,  16067,  16115,  16163,  16211,  16260,  16308,
     16356,  16404,  16453,  16501,  16549,  16597,  16646,  16694,  16742,  16790,
     16839,  16887,  16935,  16983,  17032,  17080,  17128,  17176,  17225,  17273,
     17321,  17369,  17418,  17466,  17514,  17563,  17611,  17659,  17707,  17756,
     17804,  17852,  17900,  17949,  17997,  18045,  18093,  18142,  18190,  18238,
     18286,  18335,  18383,  18431,  18479,  18528,  18576,  18624,  18672,  18721,
     18769,  18817,  18865,  18914,  18962,  19010,  19058,  19107,  19155,  19203,
     19251,  19300,  19348,  19396,  19444,  19493,  19541,  19589,  19637,  19686,
     19734,  19782,  19830,  19879,  19927,  19975,  20023,  20072,  20120,  20168,
     20216,  20265,  20313,  20361,  20409,  20458,  20506,  20554,  20603,  20651,
     20699,  20747,  20796,  20844,  20892,  20940,  20989,  21037,  21085,  21133,
     21182,  21230,  21278,  21326,  21375,  21423,  21471,  21519,  21568,  21616,
     21664,  21712,  21761,  21809,  21857,  21905,  21954,  22002,  22050,  22098,
     22147,  22195,  22243,  22291,  22340,  22388,  22436,  22484,  22533,  22581,
     22629,  22677,  22726,  22774,  22822,  22870,  22919,  22967,  23015,  23063,
     23112,  23160,  23208,  23256,  23305,  23353,  23401,  23449,  23498,  23546,
     23594,  23643,  23691,  23739,  23787,  23836,  23884,  23932,  23980,  24029,
     24077,  24125,  24173,  24222,  24270,  24318,  24366,  24415,  24463,  24511,
     24559,  24608,  24656,  24704,  24752,  24801,  24849,  24897,  24945,  24994,
     25042,  25090,  25138,  25187,  25235,  25283,  25331,  25380,  25428,  25476,
     25524,  25573,  25621,  25669,  25717,  25766,  25814,  25862,  25910,  25959,
     26007,  26055,  26103,  26152,  26200,  26248,  26296,  26345,  26393,  26441,
     26489,  26538,  26586,  26634,  26683,  26731,  26779,  26827,  26876,  26924,
     26972,  27020,  27069,  27117,  27165,  27213,  27262,  27310,  27358,  27406
};

/*
 * Waveform name: blunt_sawtooth, size: 1260 samples
 * Anti-Alias filter params: K = 200, N = 2
 */
const  int16  blunt_sawtooth[] =
{
     20699,  20747,  20794,  20839,  20883,  20925,  20966,  21005,  21043,  21079,
     21113,  21146,  21178,  21208,  21236,  21263,  21289,  21313,  21335,  21356,
     21375,  21393,  21409,  21424,  21438,  21449,  21460,  21468,  21476,  21481,
     21485,  21488,  21489,  21489,  21487,  21484,  21479,  21472,  21464,  21455,
     21444,  21431,  21417,  21401,  21384,  21366,  21346,  21324,  21301,  21276,
     21250,  21222,  21193,  21162,  21130,  21096,  21060,  21024,  20985,  20945,
     20904,  20861,  20817,  20771,  20723,  20674,  20623,  20571,  20518,  20463,
     20406,  20348,  20288,  20227,  20164,  20100,  20034,  19967,  19898,  19828,
     19756,  19683,  19608,  19532,  19454,  19374,  19293,  19211,  19127,  19041,
     18954,  18866,  18776,  18684,  18591,  18496,  18400,  18303,  18203,  18103,
     18001,  17897,  17792,  17685,  17576,  17467,  17355,  17242,  17128,  17012,
     16895,  16776,  16655,  16533,  16410,  16285,  16158,  16030,  15901,  15770,
     15637,  15503,  15367,  15230,  15091,  14951,  14809,  14666,  14521,  14375,
     14227,  14078,  13927,  13775,  13621,  13465,  13308,  13150,  12990,  12828,
     12665,  12501,  12335,  12167,  11998,  11828,  11655,  11482,  11307,  11130,
     10952,  10772,  10591,  10408,  10224,  10038,   9850,   9662,   9471,   9279,
      9086,   8891,   8694,   8496,   8297,   8096,   7893,   7689,   7484,   7277,
      7068,   6858,   6646,   6433,   6218,   6002,   5784,   5565,   5344,   5122,
      4898,   4673,   4446,   4218,   3988,   3756,   3523,   3289,   3053,   2816,
      2577,   2336,   2094,   1850,   1605,   1359,   1111,    861,    610,    357,
       103,   -152,   -406,   -659,   -910,  -1160,  -1408,  -1654,  -1900,  -2143,
     -2385,  -2626,  -2865,  -3102,  -3338,  -3573,  -3806,  -4037,  -4267,  -4495,
     -4722,  -4947,  -5171,  -5394,  -5614,  -5834,  -6051,  -6268,  -6482,  -6695,
     -6907,  -7117,  -7326,  -7533,  -7739,  -7943,  -8145,  -8346,  -8546,  -8744,
     -8940,  -9135,  -9328,  -9520,  -9711,  -9900, -10087, -10273, -10457, -10640,
    -10821, -11001, -11179, -11356, -11531, -11705, -11877, -12047, -12216, -12384,
    -12550, -12715, -12878, -13039, -13199, -13358, -13514, -13670, -13824, -13976,
    -14127, -14276, -14424, -14570, -14715, -14859, -15000, -15140, -15279, -15416,
    -15552, -15686, -15819, -15950, -16079, -16207, -16334, -16459, -16583, -16705,
    -16825, -16944, -17061, -17177, -17292, -17404, -17516, -17626, -17734, -17841,
    -17946, -18050, -18152, -18253, -18352, -18449, -18546, -18640, -18733, -18825,
    -18915, -19004, -19091, -19176, -19260, -19343, -19423, -19503, -19581, -19657,
    -19732, -19805, -19877, -19948, -20016, -20084, -20149, -20214, -20276, -20337,
    -20397, -20455, -20512, -20567, -20621, -20673, -20723, -20772, -20820, -20866,
    -20910, -20953, -20995, -21034, -21073, -21110, -21145, -21179, -21211, -21242,
    -21271, -21299, -21325, -21350, -21373, -21395, -21415, -21433, -21451, -21466,
    -21480, -21493, -21504, -21513, -21521, -21528, -21533, -21536, -21538, -21538,
    -21537, -21535, -21530, -21525, -21518, -21509, -21499, -21487, -21474, -21459,
    -21442, -21425, -21405, -21384, -21362, -21338, -21312, -21285, -21257, -21227,
    -21195, -21162, -21128, -21092, -21054, -21015, -20974, -20932, -20888, -20843,
    -20796, -20748, -20700, -20652, -20603, -20555, -20507, -20459, -20410, -20362,
    -20314, -20266, -20217, -20169, -20121, -20073, -20024, -19976, -19928, -19880,
    -19831, -19783, -19735, -19687, -19638, -19590, -19542, -19494, -19445, -19397,
    -19349, -19301, -19252, -19204, -19156, -19108, -19059, -19011, -18963, -18915,
    -18866, -18818, -18770, -18722, -18673, -18625, -18577, -18529, -18480, -18432,
    -18384, -18336, -18287, -18239, -18191, -18143, -18094, -18046, -17998, -17949,
    -17901, -17853, -17805, -17756, -17708, -17660, -17612, -17563, -17515, -17467,
    -17419, -17370, -17322, -17274, -17226, -17177, -17129, -17081, -17033, -16984,
    -16936, -16888, -16840, -16791, -16743, -16695, -16647, -16598, -16550, -16502,
    -16454, -16405, -16357, -16309, -16261, -16212, -16164, -16116, -16068, -16019,
    -15971, -15923, -15875, -15826, -15778, -15730, -15682, -15633, -15585, -15537,
    -15489, -15440, -15392, -15344, -15296, -15247, -15199, -15151, -15103, -15054,
    -15006, -14958, -14909, -14861, -14813, -14765, -14716, -14668, -14620, -14572,
    -14523, -14475, -14427, -14379, -14330, -14282, -14234, -14186, -14137, -14089,
    -14041, -13993, -13944, -13896, -13848, -13800, -13751, -13703, -13655, -13607,
    -13558, -13510, -13462, -13414, -13365, -13317, -13269, -13221, -13172, -13124,
    -13076, -13028, -12979, -12931, -12883, -12835, -12786, -12738, -12690, -12642,
    -12593, -12545, -12497, -12449, -12400, -12352, -12304, -12256, -12207, -12159,
    -12111, -12063, -12014, -11966, -11918, -11869, -11821, -11773, -11725, -11676,
    -11628, -11580, -11532, -11483, -11435, -11387, -11339, -11290, -11242, -11194,
    -11146, -11097, -11049, -11001, -10953, -10904, -10856, -10808, -10760, -10711,
    -10663, -10615, -10567, -10518, -10470, -10422, -10374, -10325, -10277, -10229,
    -10181, -10132, -10084, -10036,  -9988,  -9939,  -9891,  -9843,  -9795,  -9746,
     -9698,  -9650,  -9602,  -9553,  -9505,  -9457,  -9409,  -9360,  -9312,  -9264,
     -9216,  -9167,  -9119,  -9071,  -9023,  -8974,  -8926,  -8878,  -8829,  -8781,
     -8733,  -8685,  -8636,  -8588,  -8540,  -8492,  -8443,  -8395,  -8347,  -8299,
     -8250,  -8202,  -8154,  -8106,  -8057,  -8009,  -7961,  -7913,  -7864,  -7816,
     -7768,  -7720,  -7671,  -7623,  -7575,  -7527,  -7478,  -7430,  -7382,  -7334,
     -7285,  -7237,  -7189,  -7141,  -7092,  -7044,  -6996,  -6948,  -6899,  -6851,
     -6803,  -6755,  -6706,  -6658,  -6610,  -6562,  -6513,  -6465,  -6417,  -6369,
     -6320,  -6272,  -6224,  -6176,  -6127,  -6079,  -6031,  -5983,  -5934,  -5886,
     -5838,  -5790,  -5741,  -5693,  -5645,  -5597,  -5548,  -5500,  -5452,  -5404,
     -5355,  -5307,  -5259,  -5211,  -5162,  -5114,  -5066,  -5018,  -4969,  -4921,
     -4873,  -4825,  -4776,  -4728,  -4680,  -4632,  -4583,  -4535,  -4487,  -4439,
     -4390,  -4342,  -4294,  -4246,  -4197,  -4149,  -4101,  -4053,  -4004,  -3956,
     -3908,  -3860,  -3811,  -3763,  -3715,  -3667,  -3618,  -3570,  -3522,  -3474,
     -3425,  -3377,  -3329,  -3281,  -3232,  -3184,  -3136,  -3088,  -3039,  -2991,
     -2943,  -2895,  -2846,  -2798,  -2750,  -2702,  -2653,  -2605,  -2557,  -2509,
     -2460,  -2412,  -2364,  -2316,  -2268,  -2219,  -2171,  -2123,  -2075,  -2026,
     -1978,  -1930,  -1882,  -1833,  -1785,  -1737,  -1689,  -1640,  -1592,  -1544,
     -1496,  -1447,  -1399,  -1351,  -1303,  -1254,  -1206,  -1158,  -1110,  -1061,
     -1013,   -965,   -917,   -868,   -820,   -772,   -724,   -675,   -627,   -579,
      -531,   -482,   -434,   -386,   -338,   -289,   -241,   -193,   -145,    -96,
       -48,      0,     47,     95,    144,    192,    240,    288,    337,    385,
       433,    481,    530,    578,    626,    674,    723,    771,    819,    867,
       916,    964,   1012,   1060,   1109,   1157,   1205,   1253,   1302,   1350,
      1398,   1446,   1495,   1543,   1591,   1639,   1688,   1736,   1784,   1832,
      1881,   1929,   1977,   2025,   2074,   2122,   2170,   2218,   2267,   2315,
      2363,   2411,   2460,   2508,   2556,   2604,   2652,   2701,   2749,   2797,
      2845,   2894,   2942,   2990,   3038,   3087,   3135,   3183,   3231,   3280,
      3328,   3376,   3424,   3473,   3521,   3569,   3617,   3666,   3714,   3762,
      3810,   3859,   3907,   3955,   4003,   4052,   4100,   4148,   4196,   4245,
      4293,   4341,   4389,   4438,   4486,   4534,   4582,   4631,   4679,   4727,
      4775,   4824,   4872,   4920,   4968,   5017,   5065,   5113,   5161,   5210,
      5258,   5306,   5354,   5403,   5451,   5499,   5547,   5596,   5644,   5692,
      5740,   5789,   5837,   5885,   5933,   5982,   6030,   6078,   6126,   6175,
      6223,   6271,   6319,   6368,   6416,   6464,   6512,   6561,   6609,   6657,
      6705,   6754,   6802,   6850,   6898,   6947,   6995,   7043,   7091,   7140,
      7188,   7236,   7284,   7333,   7381,   7429,   7477,   7526,   7574,   7622,
      7670,   7719,   7767,   7815,   7863,   7912,   7960,   8008,   8056,   8105,
      8153,   8201,   8250,   8298,   8346,   8394,   8443,   8491,   8539,   8587,
      8636,   8684,   8732,   8780,   8829,   8877,   8925,   8973,   9022,   9070,
      9118,   9166,   9215,   9263,   9311,   9359,   9408,   9456,   9504,   9552,
      9601,   9649,   9697,   9745,   9794,   9842,   9890,   9938,   9987,  10035,
     10083,  10131,  10180,  10228,  10276,  10324,  10373,  10421,  10469,  10517,
     10566,  10614,  10662,  10710,  10759,  10807,  10855,  10903,  10952,  11000,
     11048,  11096,  11145,  11193,  11241,  11290,  11338,  11386,  11434,  11483,
     11531,  11579,  11627,  11676,  11724,  11772,  11820,  11869,  11917,  11965,
     12013,  12062,  12110,  12158,  12206,  12255,  12303,  12351,  12399,  12448,
     12496,  12544,  12592,  12641,  12689,  12737,  12785,  12834,  12882,  12930,
     12978,  13027,  13075,  13123,  13171,  13220,  13268,  13316,  13364,  13413,
     13461,  13509,  13557,  13606,  13654,  13702,  13750,  13799,  13847,  13895,
     13943,  13992,  14040,  14088,  14136,  14185,  14233,  14281,  14330,  14378,
     14426,  14474,  14523,  14571,  14619,  14667,  14716,  14764,  14812,  14860,
     14909,  14957,  15005,  15053,  15102,  15150,  15198,  15246,  15295,  15343,
     15391,  15439,  15488,  15536,  15584,  15632,  15681,  15729,  15777,  15825,
     15874,  15922,  15970,  16018,  16067,  16115,  16163,  16211,  16260,  16308,
     16356,  16404,  16453,  16501,  16549,  16597,  16646,  16694,  16742,  16790,
     16839,  16887,  16935,  16983,  17032,  17080,  17128,  17176,  17225,  17273,
     17321,  17370,  17418,  17466,  17514,  17563,  17611,  17659,  17707,  17756,
     17804,  17852,  17900,  17949,  17997,  18045,  18093,  18142,  18190,  18238,
     18286,  18335,  18383,  18431,  18479,  18528,  18576,  18624,  18672,  18721,
     18769,  18817,  18865,  18914,  18962,  19010,  19058,  19107,  19155,  19203,
     19251,  19300,  19348,  19396,  19444,  19493,  19541,  19589,  19637,  19686,
     19734,  19782,  19830,  19879,  19927,  19975,  20023,  20072,  20120,  20168,
     20216,  20265,  20313,  20361,  20410,  20458,  20506,  20554,  20603,  20651
};


/*
 * Waveform name: alto_saxophone, size: 1260 samples
 * Osc. Freq. Divider:   1.0000
 * Waveform Partial Distribution:
 * Order # |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 |
 * Ampld % |  7 | 10 | 26 | 12 | 10 | 16 |  9 |  1 |  3 |  3 |  1 |  3 |
 */
const  int16  alto_saxophone[] =
{
         0,    750,   1506,   2259,   3010,   3757,   4500,   5240,   5973,   6698,
      7416,   8125,   8828,   9518,  10201,  10870,  11527,  12172,  12803,  13421,
     14028,  14615,  15189,  15746,  16287,  16809,  17317,  17805,  18274,  18730,
     19163,  19578,  19975,  20352,  20711,  21050,  21368,  21668,  21947,  22205,
     22446,  22669,  22873,  23055,  23220,  23367,  23493,  23602,  23694,  23766,
     23822,  23861,  23884,  23893,  23881,  23856,  23819,  23764,  23696,  23615,
     23522,  23415,  23298,  23166,  23027,  22877,  22714,  22543,  22365,  22178,
     21982,  21781,  21569,  21355,  21133,  20908,  20674,  20438,  20199,  19955,
     19708,  19461,  19209,  18957,  18703,  18448,  18190,  17932,  17677,  17416,
     17162,  16906,  16651,  16396,  16143,  15892,  15642,  15393,  15146,  14901,
     14660,  14417,  14176,  13941,  13705,  13474,  13242,  13015,  12789,  12564,
     12341,  12124,  11906,  11691,  11476,  11263,  11052,  10844,  10636,  10430,
     10225,  10023,   9820,   9619,   9421,   9221,   9023,   8825,   8628,   8433,
      8237,   8041,   7848,   7655,   7459,   7266,   7075,   6883,   6690,   6498,
      6308,   6116,   5927,   5736,   5548,   5360,   5173,   4985,   4801,   4615,
      4433,   4250,   4070,   3889,   3714,   3538,   3363,   3191,   3023,   2858,
      2693,   2534,   2375,   2219,   2065,   1919,   1773,   1633,   1494,   1362,
      1235,   1110,    991,    874,    764,    660,    559,    466,    377,    291,
       211,    137,     68,      4,    -51,   -102,   -147,   -186,   -222,   -249,
      -272,   -290,   -299,   -305,   -307,   -302,   -293,   -278,   -258,   -236,
      -208,   -174,   -138,    -98,    -52,     -4,     49,    101,    159,    220,
       283,    347,    411,    482,    552,    622,    693,    763,    834,    910,
       983,   1052,   1121,   1191,   1260,   1325,   1390,   1452,   1513,   1570,
      1624,   1677,   1724,   1768,   1808,   1849,   1882,   1911,   1937,   1958,
      1975,   1988,   1993,   1995,   1994,   1985,   1975,   1959,   1934,   1906,
      1877,   1840,   1797,   1747,   1696,   1640,   1578,   1509,   1438,   1363,
      1286,   1203,   1114,   1023,    927,    829,    726,    619,    508,    399,
       283,    167,     47,    -73,   -199,   -325,   -454,   -585,   -714,   -847,
      -981,  -1113,  -1247,  -1381,  -1518,  -1653,  -1787,  -1919,  -2055,  -2186,
     -2320,  -2454,  -2581,  -2711,  -2839,  -2967,  -3095,  -3217,  -3341,  -3460,
     -3581,  -3695,  -3810,  -3924,  -4036,  -4142,  -4250,  -4355,  -4457,  -4558,
     -4653,  -4747,  -4842,  -4932,  -5020,  -5106,  -5188,  -5270,  -5350,  -5425,
     -5501,  -5573,  -5643,  -5709,  -5774,  -5838,  -5898,  -5957,  -6011,  -6066,
     -6119,  -6168,  -6215,  -6257,  -6301,  -6342,  -6380,  -6415,  -6447,  -6480,
     -6506,  -6534,  -6556,  -6578,  -6595,  -6613,  -6625,  -6637,  -6643,  -6647,
     -6649,  -6647,  -6643,  -6634,  -6624,  -6610,  -6592,  -6568,  -6546,  -6518,
     -6485,  -6448,  -6410,  -6364,  -6317,  -6263,  -6207,  -6147,  -6080,  -6011,
     -5935,  -5857,  -5774,  -5687,  -5594,  -5494,  -5392,  -5286,  -5174,  -5057,
     -4934,  -4809,  -4679,  -4543,  -4404,  -4257,  -4110,  -3955,  -3798,  -3635,
     -3468,  -3301,  -3124,  -2949,  -2767,  -2582,  -2395,  -2204,  -2011,  -1815,
     -1616,  -1416,  -1212,  -1010,   -803,   -596,   -387,   -178,     31,    239,
       448,    657,    865,   1072,   1276,   1484,   1683,   1886,   2083,   2278,
      2470,   2659,   2845,   3025,   3207,   3381,   3551,   3715,   3878,   4035,
      4184,   4328,   4468,   4601,   4732,   4851,   4968,   5077,   5179,   5276,
      5365,   5449,   5527,   5596,   5660,   5717,   5767,   5809,   5846,   5879,
      5902,   5919,   5932,   5938,   5938,   5928,   5920,   5900,   5878,   5845,
      5812,   5775,   5732,   5685,   5633,   5579,   5522,   5461,   5400,   5327,
      5258,   5187,   5113,   5040,   4962,   4884,   4807,   4726,   4646,   4568,
      4488,   4410,   4332,   4254,   4178,   4104,   4031,   3959,   3892,   3825,
      3759,   3700,   3641,   3587,   3533,   3482,   3435,   3394,   3353,   3318,
      3282,   3253,   3227,   3206,   3184,   3167,   3155,   3148,   3143,   3138,
      3140,   3145,   3153,   3162,   3175,   3190,   3207,   3228,   3250,   3272,
      3300,   3327,   3354,   3383,   3412,   3446,   3474,   3509,   3539,   3571,
      3603,   3634,   3664,   3694,   3722,   3746,   3772,   3795,   3817,   3838,
      3854,   3870,   3881,   3888,   3899,   3900,   3901,   3899,   3894,   3886,
      3873,   3856,   3840,   3819,   3791,   3762,   3728,   3693,   3651,   3608,
      3564,   3514,   3460,   3404,   3346,   3284,   3220,   3153,   3084,   3012,
      2937,   2860,   2784,   2703,   2622,   2539,   2454,   2370,   2285,   2200,
      2114,   2028,   1942,   1854,   1767,   1684,   1599,   1514,   1432,   1351,
      1272,   1193,   1117,   1039,    967,    897,    828,    761,    698,    636,
       577,    522,    468,    418,    371,    325,    285,    246,    207,    176,
       144,    115,     90,     70,     47,     33,     14,      3,    -10,    -21,
       -28,    -31,    -35,    -39,    -40,    -39,    -39,    -36,    -33,    -30,
       -27,    -24,    -20,    -17,    -13,    -11,     -9,    -10,    -12,    -14,
       -15,    -20,    -29,    -37,    -47,    -62,    -74,    -93,   -109,   -130,
      -157,   -185,   -211,   -246,   -282,   -318,   -360,   -402,   -448,   -500,
      -551,   -606,   -664,   -723,   -786,   -853,   -918,   -987,  -1063,  -1135,
     -1211,  -1287,  -1367,  -1447,  -1530,  -1613,  -1695,  -1780,  -1867,  -1952,
     -2038,  -2124,  -2209,  -2296,  -2379,  -2465,  -2549,  -2632,  -2715,  -2793,
     -2872,  -2949,  -3024,  -3096,  -3165,  -3232,  -3298,  -3360,  -3420,  -3477,
     -3534,  -3581,  -3630,  -3675,  -3716,  -3754,  -3789,  -3821,  -3847,  -3870,
     -3892,  -3911,  -3924,  -3935,  -3942,  -3947,  -3949,  -3944,  -3941,  -3936,
     -3924,  -3913,  -3896,  -3881,  -3861,  -3838,  -3817,  -3794,  -3767,  -3739,
     -3711,  -3680,  -3651,  -3623,  -3590,  -3560,  -3529,  -3501,  -3471,  -3444,
     -3416,  -3389,  -3365,  -3341,  -3319,  -3299,  -3281,  -3267,  -3253,  -3243,
     -3234,  -3229,  -3230,  -3229,  -3231,  -3239,  -3251,  -3266,  -3282,  -3301,
     -3325,  -3355,  -3383,  -3418,  -3452,  -3493,  -3535,  -3583,  -3629,  -3682,
     -3734,  -3793,  -3853,  -3915,  -3979,  -4046,  -4113,  -4182,  -4254,  -4326,
     -4397,  -4471,  -4544,  -4620,  -4695,  -4767,  -4842,  -4915,  -4985,  -5054,
     -5122,  -5189,  -5258,  -5317,  -5377,  -5433,  -5486,  -5538,  -5584,  -5628,
     -5664,  -5699,  -5733,  -5757,  -5778,  -5788,  -5801,  -5805,  -5801,  -5792,
     -5779,  -5762,  -5733,  -5701,  -5665,  -5620,  -5570,  -5511,  -5449,  -5378,
     -5300,  -5217,  -5128,  -5035,  -4933,  -4824,  -4711,  -4588,  -4463,  -4331,
     -4194,  -4052,  -3904,  -3749,  -3591,  -3429,  -3262,  -3089,  -2915,  -2735,
     -2554,  -2368,  -2179,  -1987,  -1791,  -1597,  -1395,  -1196,   -992,   -789,
      -584,   -378,   -172,     34,    241,    447,    654,    858,   1060,   1263,
      1464,   1662,   1860,   2054,   2247,   2435,   2622,   2807,   2985,   3165,
      3335,   3508,   3674,   3837,   3995,   4150,   4301,   4446,   4587,   4723,
      4856,   4985,   5109,   5228,   5340,   5451,   5557,   5656,   5751,   5842,
      5927,   6009,   6087,   6161,   6229,   6292,   6352,   6406,   6458,   6503,
      6546,   6585,   6619,   6648,   6677,   6700,   6718,   6733,   6746,   6753,
      6760,   6761,   6760,   6756,   6747,   6738,   6721,   6705,   6684,   6662,
      6634,   6609,   6576,   6544,   6507,   6468,   6425,   6379,   6333,   6284,
      6231,   6177,   6117,   6058,   5996,   5933,   5865,   5793,   5723,   5648,
      5570,   5489,   5408,   5322,   5236,   5148,   5056,   4962,   4866,   4766,
      4666,   4563,   4457,   4350,   4239,   4125,   4013,   3897,   3777,   3658,
      3538,   3413,   3290,   3162,   3035,   2904,   2773,   2642,   2508,   2378,
      2242,   2106,   1973,   1835,   1702,   1566,   1431,   1294,   1160,   1024,
       892,    759,    627,    500,    370,    244,    119,     -4,   -123,   -241,
      -354,   -466,   -573,   -681,   -783,   -882,   -976,  -1070,  -1156,  -1240,
     -1319,  -1394,  -1465,  -1531,  -1596,  -1653,  -1705,  -1752,  -1796,  -1835,
     -1869,  -1894,  -1918,  -1938,  -1953,  -1958,  -1965,  -1961,  -1957,  -1949,
     -1933,  -1913,  -1890,  -1863,  -1832,  -1798,  -1755,  -1715,  -1669,  -1621,
     -1568,  -1515,  -1456,  -1397,  -1335,  -1271,  -1206,  -1138,  -1070,  -1003,
      -935,   -865,   -792,   -723,   -656,   -586,   -519,   -453,   -386,   -323,
      -262,   -205,   -147,    -93,    -44,      4,     48,     91,    128,    161,
       191,    215,    234,    249,    261,    266,    267,    264,    255,    242,
       221,    197,    167,    130,     88,     41,    -11,    -68,   -132,   -202,
      -275,   -356,   -441,   -531,   -623,   -724,   -827,   -936,  -1050,  -1169,
     -1291,  -1416,  -1545,  -1682,  -1820,  -1961,  -2104,  -2256,  -2408,  -2562,
     -2718,  -2878,  -3040,  -3203,  -3370,  -3541,  -3712,  -3883,  -4058,  -4233,
     -4411,  -4589,  -4770,  -4949,  -5131,  -5316,  -5499,  -5682,  -5868,  -6053,
     -6240,  -6427,  -6613,  -6803,  -6992,  -7181,  -7370,  -7563,  -7754,  -7944,
     -8139,  -8332,  -8526,  -8722,  -8918,  -9115,  -9316,  -9515,  -9716,  -9920,
    -10121, -10328, -10535, -10746, -10956, -11169, -11385, -11604, -11821, -12043,
    -12263, -12490, -12719, -12950, -13183, -13418, -13656, -13897, -14139, -14385,
    -14634, -14882, -15132, -15385, -15640, -15898, -16155, -16416, -16676, -16938,
    -17200, -17462, -17727, -17989, -18253, -18518, -18778, -19038, -19295, -19554,
    -19806, -20057, -20306, -20550, -20791, -21027, -21257, -21481, -21700, -21913,
    -22117, -22315, -22504, -22683, -22854, -23018, -23168, -23307, -23439, -23555,
    -23661, -23752, -23830, -23896, -23948, -23983, -24003, -24012, -24000, -23972,
    -23928, -23867, -23791, -23692, -23577, -23445, -23292, -23120, -22931, -22720,
    -22492, -22244, -21977, -21691, -21382, -21056, -20711, -20344, -19959, -19556,
    -19133, -18692, -18229, -17753, -17258, -16742, -16212, -15664, -15102, -14520,
    -13928, -13315, -12693, -12056, -11407, -10742, -10071,  -9384,  -8690,  -7983,
     -7271,  -6552,  -5824,  -5089,  -4348,  -3604,  -2856,  -2105,  -1352,   -597
};

/*
 * Waveform name: mellow_pipe_v1, size: 1260 samples
 * Osc. Freq. Divider:   1.0000
 * Waveform Partial Distribution:
 * Order # |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 |
 * Ampld % | 64 | 32 | 16 |  8 |    |    |    |    |    |    |    |    |
 */
const  int16  mellow_pipe_v1[] =
{
         0,    330,    663,    993,   1326,   1656,   1987,   2319,   2649,   2979,
      3309,   3637,   3966,   4294,   4621,   4949,   5274,   5599,   5924,   6247,
      6570,   6891,   7210,   7531,   7848,   8165,   8481,   8796,   9109,   9422,
      9733,  10042,  10348,  10655,  10960,  11262,  11562,  11862,  12160,  12456,
     12750,  13043,  13332,  13621,  13908,  14191,  14473,  14753,  15032,  15308,
     15582,  15853,  16123,  16388,  16653,  16916,  17174,  17431,  17686,  17938,
     18188,  18436,  18681,  18922,  19161,  19398,  19631,  19863,  20092,  20317,
     20540,  20759,  20976,  21191,  21402,  21609,  21816,  22019,  22218,  22414,
     22608,  22799,  22986,  23171,  23352,  23532,  23706,  23879,  24048,  24213,
     24376,  24537,  24694,  24847,  24997,  25144,  25288,  25430,  25567,  25701,
     25833,  25961,  26086,  26209,  26328,  26443,  26555,  26665,  26770,  26872,
     26973,  27070,  27163,  27253,  27341,  27425,  27506,  27583,  27659,  27732,
     27799,  27864,  27927,  27987,  28045,  28097,  28148,  28196,  28240,  28284,
     28320,  28357,  28391,  28421,  28449,  28473,  28496,  28515,  28530,  28544,
     28556,  28565,  28569,  28573,  28574,  28571,  28567,  28560,  28550,  28538,
     28523,  28506,  28487,  28465,  28441,  28415,  28386,  28355,  28324,  28289,
     28251,  28211,  28170,  28126,  28081,  28034,  27985,  27932,  27879,  27824,
     27767,  27708,  27647,  27586,  27521,  27457,  27388,  27320,  27250,  27178,
     27105,  27030,  26954,  26876,  26798,  26717,  26635,  26553,  26468,  26384,
     26298,  26209,  26122,  26033,  25941,  25849,  25758,  25665,  25570,  25475,
     25380,  25284,  25186,  25088,  24989,  24891,  24791,  24690,  24589,  24487,
     24386,  24284,  24182,  24079,  23975,  23871,  23768,  23663,  23557,  23454,
     23349,  23244,  23138,  23033,  22929,  22822,  22717,  22611,  22506,  22401,
     22295,  22191,  22086,  21981,  21876,  21772,  21668,  21564,  21461,  21357,
     21254,  21151,  21049,  20948,  20846,  20745,  20646,  20545,  20445,  20347,
     20247,  20150,  20052,  19955,  19858,  19763,  19668,  19573,  19480,  19387,
     19292,  19200,  19109,  19019,  18929,  18840,  18752,  18663,  18577,  18491,
     18405,  18319,  18235,  18152,  18071,  17988,  17908,  17828,  17747,  17668,
     17592,  17515,  17437,  17362,  17287,  17214,  17141,  17069,  16999,  16927,
     16857,  16788,  16720,  16652,  16585,  16519,  16454,  16391,  16327,  16264,
     16203,  16141,  16080,  16021,  15961,  15904,  15845,  15790,  15734,  15678,
     15624,  15569,  15516,  15463,  15411,  15360,  15309,  15259,  15210,  15161,
     15112,  15064,  15018,  14970,  14925,  14880,  14835,  14789,  14746,  14703,
     14659,  14618,  14575,  14533,  14492,  14451,  14411,  14370,  14330,  14292,
     14253,  14213,  14175,  14137,  14099,  14062,  14025,  13988,  13951,  13915,
     13878,  13841,  13805,  13770,  13734,  13698,  13663,  13628,  13593,  13557,
     13523,  13487,  13453,  13417,  13382,  13346,  13311,  13277,  13241,  13206,
     13170,  13135,  13100,  13063,  13028,  12991,  12956,  12919,  12884,  12846,
     12811,  12773,  12737,  12699,  12662,  12624,  12586,  12546,  12509,  12469,
     12430,  12391,  12351,  12310,  12270,  12230,  12189,  12147,  12106,  12063,
     12021,  11979,  11934,  11891,  11847,  11802,  11757,  11713,  11666,  11620,
     11573,  11526,  11479,  11431,  11384,  11335,  11285,  11237,  11186,  11136,
     11084,  11033,  10981,  10928,  10877,  10823,  10769,  10716,  10662,  10606,
     10552,  10495,  10440,  10383,  10326,  10269,  10211,  10153,  10094,  10035,
      9976,   9916,   9856,   9795,   9733,   9673,   9610,   9548,   9486,   9422,
      9359,   9296,   9232,   9168,   9104,   9039,   8973,   8908,   8843,   8776,
      8709,   8644,   8577,   8510,   8441,   8374,   8305,   8238,   8170,   8101,
      8033,   7965,   7896,   7827,   7758,   7689,   7619,   7549,   7479,   7410,
      7339,   7270,   7200,   7130,   7059,   6989,   6918,   6849,   6779,   6709,
      6638,   6568,   6498,   6429,   6358,   6287,   6217,   6149,   6079,   6009,
      5940,   5870,   5802,   5732,   5664,   5595,   5527,   5459,   5391,   5322,
      5255,   5188,   5121,   5053,   4986,   4921,   4855,   4789,   4723,   4658,
      4593,   4530,   4464,   4401,   4337,   4277,   4212,   4149,   4088,   4027,
      3965,   3905,   3843,   3784,   3724,   3664,   3605,   3547,   3490,   3433,
      3376,   3319,   3264,   3207,   3152,   3098,   3044,   2991,   2936,   2883,
      2830,   2780,   2728,   2677,   2626,   2577,   2528,   2479,   2430,   2383,
      2334,   2289,   2242,   2195,   2149,   2106,   2061,   2018,   1973,   1930,
      1888,   1846,   1804,   1763,   1722,   1682,   1643,   1604,   1565,   1527,
      1488,   1450,   1414,   1377,   1341,   1305,   1270,   1235,   1200,   1167,
      1132,   1098,   1066,   1032,   1000,    968,    936,    905,    874,    844,
       813,    784,    753,    724,    695,    665,    636,    609,    580,    553,
       526,    497,    470,    443,    416,    389,    363,    336,    310,    283,
       257,    231,    205,    179,    153,    128,    102,     75,     51,     24,
         0,    -24,    -51,    -75,   -102,   -128,   -153,   -179,   -205,   -231,
      -257,   -283,   -310,   -336,   -363,   -389,   -416,   -443,   -470,   -497,
      -526,   -553,   -580,   -609,   -637,   -665,   -695,   -724,   -753,   -784,
      -813,   -844,   -874,   -905,   -936,   -968,  -1000,  -1032,  -1066,  -1098,
     -1132,  -1167,  -1200,  -1235,  -1270,  -1305,  -1341,  -1377,  -1414,  -1450,
     -1488,  -1527,  -1565,  -1604,  -1643,  -1682,  -1722,  -1763,  -1804,  -1846,
     -1888,  -1930,  -1973,  -2018,  -2061,  -2106,  -2149,  -2195,  -2242,  -2289,
     -2334,  -2383,  -2431,  -2479,  -2528,  -2577,  -2626,  -2677,  -2728,  -2780,
     -2830,  -2883,  -2936,  -2991,  -3044,  -3098,  -3152,  -3207,  -3264,  -3319,
     -3376,  -3433,  -3490,  -3547,  -3605,  -3664,  -3724,  -3784,  -3843,  -3905,
     -3965,  -4027,  -4088,  -4149,  -4212,  -4277,  -4337,  -4401,  -4464,  -4530,
     -4593,  -4658,  -4723,  -4789,  -4855,  -4921,  -4986,  -5053,  -5121,  -5188,
     -5255,  -5322,  -5391,  -5459,  -5527,  -5595,  -5664,  -5732,  -5802,  -5870,
     -5940,  -6009,  -6079,  -6149,  -6217,  -6287,  -6358,  -6429,  -6498,  -6568,
     -6638,  -6709,  -6779,  -6849,  -6918,  -6989,  -7059,  -7130,  -7200,  -7270,
     -7339,  -7410,  -7479,  -7549,  -7619,  -7689,  -7758,  -7827,  -7896,  -7965,
     -8033,  -8101,  -8170,  -8238,  -8305,  -8374,  -8441,  -8510,  -8577,  -8644,
     -8710,  -8776,  -8843,  -8908,  -8973,  -9038,  -9104,  -9168,  -9232,  -9296,
     -9359,  -9422,  -9486,  -9548,  -9610,  -9673,  -9733,  -9795,  -9856,  -9916,
     -9976, -10035, -10094, -10153, -10211, -10269, -10326, -10383, -10440, -10495,
    -10552, -10606, -10662, -10716, -10769, -10823, -10877, -10928, -10981, -11033,
    -11084, -11136, -11186, -11237, -11285, -11335, -11384, -11431, -11479, -11526,
    -11573, -11620, -11666, -11713, -11757, -11802, -11847, -11891, -11934, -11979,
    -12021, -12063, -12106, -12147, -12189, -12230, -12270, -12310, -12351, -12391,
    -12430, -12469, -12509, -12546, -12586, -12623, -12662, -12699, -12737, -12773,
    -12811, -12846, -12884, -12919, -12956, -12991, -13028, -13063, -13100, -13135,
    -13170, -13206, -13241, -13277, -13311, -13346, -13382, -13417, -13453, -13487,
    -13523, -13557, -13593, -13628, -13663, -13698, -13734, -13770, -13805, -13842,
    -13878, -13915, -13951, -13988, -14025, -14062, -14099, -14137, -14175, -14213,
    -14253, -14292, -14330, -14370, -14411, -14451, -14492, -14533, -14575, -14618,
    -14659, -14703, -14746, -14789, -14835, -14880, -14925, -14970, -15018, -15064,
    -15112, -15161, -15210, -15259, -15309, -15360, -15411, -15463, -15516, -15569,
    -15624, -15678, -15734, -15790, -15845, -15904, -15961, -16021, -16080, -16141,
    -16203, -16264, -16327, -16391, -16454, -16519, -16585, -16652, -16720, -16788,
    -16857, -16927, -16999, -17069, -17141, -17214, -17287, -17362, -17437, -17515,
    -17592, -17669, -17747, -17828, -17908, -17988, -18071, -18152, -18235, -18319,
    -18405, -18491, -18577, -18663, -18752, -18840, -18929, -19019, -19109, -19200,
    -19292, -19387, -19480, -19573, -19668, -19763, -19858, -19955, -20052, -20150,
    -20247, -20347, -20445, -20545, -20646, -20745, -20846, -20948, -21049, -21151,
    -21254, -21357, -21461, -21564, -21668, -21772, -21877, -21981, -22086, -22191,
    -22295, -22401, -22506, -22611, -22717, -22822, -22929, -23033, -23138, -23244,
    -23349, -23454, -23557, -23663, -23768, -23871, -23975, -24079, -24182, -24284,
    -24386, -24487, -24589, -24690, -24791, -24891, -24989, -25088, -25186, -25284,
    -25380, -25475, -25570, -25665, -25758, -25849, -25941, -26033, -26122, -26209,
    -26298, -26384, -26468, -26553, -26636, -26717, -26798, -26876, -26954, -27030,
    -27105, -27178, -27250, -27320, -27388, -27457, -27521, -27586, -27647, -27708,
    -27767, -27824, -27879, -27932, -27985, -28034, -28081, -28126, -28170, -28211,
    -28251, -28289, -28324, -28355, -28386, -28415, -28441, -28465, -28487, -28506,
    -28523, -28538, -28550, -28560, -28567, -28571, -28574, -28573, -28569, -28565,
    -28556, -28544, -28530, -28515, -28496, -28473, -28449, -28421, -28391, -28357,
    -28320, -28284, -28240, -28196, -28148, -28097, -28045, -27987, -27927, -27864,
    -27799, -27732, -27659, -27583, -27506, -27425, -27341, -27253, -27163, -27070,
    -26973, -26872, -26770, -26665, -26555, -26442, -26328, -26209, -26086, -25961,
    -25833, -25701, -25567, -25430, -25288, -25144, -24997, -24847, -24694, -24537,
    -24376, -24213, -24048, -23879, -23706, -23532, -23352, -23171, -22986, -22799,
    -22608, -22414, -22218, -22019, -21816, -21609, -21402, -21191, -20976, -20759,
    -20540, -20317, -20092, -19863, -19631, -19398, -19161, -18922, -18681, -18436,
    -18188, -17938, -17686, -17431, -17174, -16916, -16653, -16388, -16123, -15853,
    -15582, -15308, -15032, -14753, -14473, -14191, -13908, -13621, -13332, -13043,
    -12750, -12456, -12160, -11862, -11562, -11261, -10960, -10655, -10348, -10042,
     -9733,  -9422,  -9109,  -8796,  -8481,  -8166,  -7848,  -7531,  -7210,  -6891,
     -6570,  -6247,  -5924,  -5599,  -5274,  -4949,  -4621,  -4294,  -3966,  -3637,
     -3309,  -2979,  -2649,  -2319,  -1987,  -1656,  -1326,   -993,   -663,   -330
};

/*
 * Waveform name: psychedelic_oboe, size: 1260 samples
 * Osc. Freq. Divider:   1.0000
 * Waveform Partial Distribution:
 * Order # |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 |
 * Ampld % | 20 |    |    |    | 10 | 20 | 30 | 20 | 10 |    |    |    |
 */
const  int16  psychedelic_oboe[] =
{
         0,   1033,   2069,   3103,   4131,   5155,   6172,   7182,   8184,   9172,
     10150,  11115,  12066,  13002,  13920,  14823,  15705,  16567,  17407,  18227,
     19035,  19806,  20554,  21275,  21969,  22635,  23274,  23883,  24462,  25011,
     25527,  26014,  26467,  26888,  27274,  27630,  27947,  28235,  28486,  28700,
     28882,  29027,  29138,  29213,  29255,  29261,  29230,  29166,  29068,  28934,
     28768,  28568,  28335,  28071,  27771,  27444,  27082,  26692,  26273,  25812,
     25334,  24830,  24298,  23739,  23158,  22552,  21922,  21271,  20598,  19905,
     19194,  18466,  17720,  16959,  16182,  15392,  14590,  13778,  12953,  12107,
     11267,  10421,   9570,   8716,   7857,   6997,   6138,   5279,   4423,   3568,
      2718,   1877,   1039,    206,   -613,  -1425,  -2224,  -3013,  -3790,  -4561,
     -5308,  -6038,  -6752,  -7447,  -8123,  -8782,  -9419, -10036, -10631, -11205,
    -11754, -12281, -12784, -13262, -13716, -14143, -14544, -14920, -15268, -15591,
    -15883, -16151, -16389, -16600, -16783, -16941, -17065, -17166, -17237, -17283,
    -17298, -17288, -17250, -17186, -17097, -16980, -16836, -16667, -16464, -16245,
    -16003, -15739, -15450, -15141, -14806, -14453, -14078, -13685, -13272, -12843,
    -12392, -11927, -11446, -10951, -10438,  -9914,  -9378,  -8813,  -8254,  -7683,
     -7105,  -6518,  -5922,  -5320,  -4714,  -4099,  -3485,  -2867,  -2243,  -1621,
      -998,   -375,    247,    867,   1485,   2097,   2706,   3321,   3918,   4509,
      5091,   5665,   6232,   6789,   7336,   7872,   8396,   8911,   9411,   9899,
     10374,  10834,  11281,  11714,  12129,  12533,  12917,  13287,  13641,  13976,
     14296,  14599,  14884,  15152,  15405,  15639,  15853,  16053,  16234,  16398,
     16545,  16675,  16787,  16882,  16961,  17023,  17056,  17086,  17099,  17097,
     17078,  17045,  16998,  16936,  16861,  16769,  16666,  16550,  16423,  16282,
     16130,  15968,  15794,  15611,  15416,  15215,  14989,  14769,  14543,  14310,
     14069,  13823,  13570,  13313,  13053,  12787,  12518,  12246,  11972,  11694,
     11416,  11137,  10856,  10578,  10298,  10019,   9730,   9454,   9182,   8911,
      8644,   8379,   8117,   7860,   7607,   7359,   7114,   6878,   6643,   6417,
      6196,   5982,   5774,   5572,   5376,   5189,   5007,   4834,   4669,   4510,
      4357,   4214,   4078,   3950,   3829,   3716,   3612,   3514,   3424,   3341,
      3268,   3199,   3139,   3086,   3039,   3014,   2982,   2957,   2937,   2925,
      2919,   2920,   2926,   2938,   2955,   2978,   3004,   3035,   3074,   3114,
      3160,   3209,   3262,   3317,   3391,   3455,   3519,   3588,   3657,   3728,
      3803,   3877,   3954,   4028,   4108,   4188,   4267,   4347,   4425,   4505,
      4585,   4662,   4741,   4819,   4906,   4981,   5053,   5124,   5196,   5264,
      5331,   5395,   5459,   5517,   5577,   5634,   5687,   5738,   5786,   5833,
      5877,   5920,   5958,   5993,   6028,   6058,   6085,   6111,   6132,   6152,
      6169,   6183,   6196,   6206,   6214,   6219,   6223,   6225,   6224,   6222,
      6217,   6212,   6202,   6181,   6169,   6158,   6143,   6127,   6111,   6095,
      6075,   6056,   6035,   6014,   5994,   5971,   5949,   5925,   5903,   5882,
      5858,   5834,   5811,   5774,   5752,   5729,   5708,   5688,   5665,   5646,
      5626,   5608,   5591,   5572,   5554,   5540,   5525,   5509,   5496,   5482,
      5471,   5460,   5448,   5429,   5419,   5413,   5404,   5399,   5394,   5388,
      5382,   5378,   5374,   5371,   5369,   5366,   5365,   5361,   5360,   5359,
      5357,   5355,   5354,   5352,   5350,   5348,   5345,   5342,   5338,   5334,
      5330,   5323,   5318,   5310,   5301,   5293,   5282,   5270,   5259,   5244,
      5229,   5213,   5207,   5189,   5168,   5145,   5122,   5097,   5070,   5040,
      5011,   4979,   4947,   4911,   4876,   4838,   4797,   4757,   4715,   4669,
      4624,   4593,   4544,   4495,   4443,   4391,   4337,   4282,   4227,   4171,
      4113,   4053,   3996,   3936,   3875,   3814,   3753,   3691,   3631,   3567,
      3507,   3457,   3395,   3335,   3272,   3211,   3152,   3095,   3036,   2979,
      2923,   2866,   2814,   2762,   2711,   2659,   2614,   2568,   2523,   2482,
      2442,   2404,   2369,   2333,   2303,   2273,   2246,   2223,   2200,   2182,
      2164,   2151,   2139,   2130,   2126,   2124,   2124,   2126,   2131,   2138,
      2139,   2152,   2167,   2186,   2207,   2230,   2257,   2283,   2315,   2348,
      2382,   2418,   2459,   2499,   2542,   2586,   2634,   2681,   2730,   2781,
      2816,   2870,   2923,   2978,   3031,   3087,   3143,   3199,   3254,   3310,
      3364,   3419,   3473,   3527,   3581,   3632,   3683,   3732,   3779,   3825,
      3859,   3901,   3943,   3979,   4017,   4051,   4080,   4110,   4135,   4158,
      4176,   4194,   4205,   4216,   4221,   4225,   4223,   4216,   4209,   4196,
      4179,   4159,   4135,   4107,   4073,   4039,   3996,   3952,   3903,   3851,
      3792,   3732,   3665,   3597,   3523,   3444,   3364,   3279,   3188,   3107,
      3011,   2911,   2807,   2702,   2591,   2480,   2361,   2243,   2122,   1997,
      1870,   1741,   1610,   1475,   1339,   1202,   1062,    922,    795,    651,
       510,    368,    221,     75,    -70,   -217,   -363,   -510,   -657,   -801,
      -945,  -1088,  -1231,  -1371,  -1510,  -1651,  -1786,  -1921,  -2041,  -2172,
     -2300,  -2427,  -2549,  -2672,  -2789,  -2902,  -3015,  -3125,  -3228,  -3331,
     -3429,  -3525,  -3616,  -3703,  -3786,  -3869,  -3942,  -4016,  -4084,  -4149,
     -4210,  -4267,  -4320,  -4367,  -4413,  -4455,  -4489,  -4523,  -4550,  -4576,
     -4595,  -4612,  -4625,  -4635,  -4639,  -4642,  -4640,  -4645,  -4639,  -4626,
     -4612,  -4594,  -4573,  -4549,  -4524,  -4494,  -4463,  -4427,  -4390,  -4352,
     -4311,  -4269,  -4224,  -4179,  -4131,  -4081,  -4030,  -3995,  -3942,  -3889,
     -3833,  -3780,  -3725,  -3669,  -3614,  -3556,  -3501,  -3446,  -3392,  -3335,
     -3282,  -3230,  -3177,  -3124,  -3074,  -3024,  -2976,  -2939,  -2892,  -2848,
     -2805,  -2761,  -2722,  -2685,  -2649,  -2612,  -2580,  -2549,  -2521,  -2496,
     -2471,  -2450,  -2430,  -2413,  -2397,  -2384,  -2374,  -2364,  -2359,  -2353,
     -2351,  -2351,  -2353,  -2358,  -2365,  -2372,  -2385,  -2399,  -2413,  -2429,
     -2451,  -2471,  -2494,  -2520,  -2545,  -2572,  -2592,  -2624,  -2656,  -2691,
     -2726,  -2762,  -2802,  -2840,  -2881,  -2923,  -2966,  -3010,  -3056,  -3100,
     -3148,  -3195,  -3242,  -3290,  -3340,  -3375,  -3424,  -3475,  -3525,  -3577,
     -3627,  -3677,  -3730,  -3781,  -3832,  -3885,  -3936,  -3986,  -4038,  -4088,
     -4139,  -4189,  -4241,  -4292,  -4341,  -4379,  -4429,  -4478,  -4527,  -4574,
     -4622,  -4669,  -4717,  -4762,  -4810,  -4856,  -4900,  -4947,  -4992,  -5036,
     -5081,  -5124,  -5168,  -5211,  -5254,  -5297,  -5340,  -5383,  -5425,  -5466,
     -5508,  -5549,  -5590,  -5629,  -5672,  -5711,  -5751,  -5790,  -5828,  -5868,
     -5907,  -5947,  -5985,  -6022,  -6070,  -6109,  -6144,  -6182,  -6217,  -6254,
     -6288,  -6323,  -6358,  -6391,  -6425,  -6457,  -6487,  -6519,  -6550,  -6578,
     -6606,  -6634,  -6660,  -6687,  -6725,  -6748,  -6771,  -6791,  -6810,  -6829,
     -6846,  -6862,  -6873,  -6884,  -6896,  -6904,  -6911,  -6914,  -6917,  -6918,
     -6916,  -6912,  -6905,  -6896,  -6896,  -6882,  -6865,  -6847,  -6825,  -6803,
     -6776,  -6747,  -6714,  -6679,  -6642,  -6601,  -6559,  -6513,  -6464,  -6413,
     -6359,  -6303,  -6243,  -6182,  -6116,  -6048,  -5977,  -5902,  -5827,  -5750,
     -5667,  -5584,  -5499,  -5412,  -5324,  -5232,  -5140,  -5045,  -4951,  -4853,
     -4756,  -4657,  -4557,  -4444,  -4342,  -4242,  -4140,  -4038,  -3936,  -3833,
     -3734,  -3633,  -3534,  -3438,  -3342,  -3248,  -3155,  -3063,  -2978,  -2892,
     -2811,  -2731,  -2641,  -2569,  -2499,  -2436,  -2375,  -2320,  -2270,  -2224,
     -2184,  -2149,  -2121,  -2095,  -2079,  -2069,  -2064,  -2066,  -2075,  -2091,
     -2114,  -2144,  -2171,  -2218,  -2271,  -2334,  -2400,  -2479,  -2564,  -2657,
     -2760,  -2869,  -2987,  -3113,  -3249,  -3390,  -3542,  -3701,  -3868,  -4044,
     -4226,  -4419,  -4618,  -4824,  -5038,  -5260,  -5487,  -5722,  -5964,  -6212,
     -6464,  -6724,  -6988,  -7260,  -7533,  -7813,  -8097,  -8385,  -8676,  -8970,
     -9267,  -9577,  -9878, -10179, -10483, -10788, -11092, -11395, -11697, -11999,
    -12298, -12594, -12889, -13179, -13465, -13746, -14023, -14293, -14558, -14818,
    -15068, -15327, -15562, -15788, -16006, -16214, -16411, -16599, -16774, -16937,
    -17089, -17229, -17356, -17467, -17566, -17651, -17723, -17777, -17815, -17839,
    -17847, -17850, -17824, -17782, -17722, -17646, -17552, -17441, -17312, -17165,
    -16999, -16817, -16616, -16398, -16160, -15907, -15635, -15342, -15035, -14710,
    -14367, -14007, -13631, -13236, -12826, -12401, -11959, -11504, -11032, -10547,
    -10048,  -9536,  -9010,  -8474,  -7924,  -7364,  -6794,  -6214,  -5625,  -5026,
     -4411,  -3798,  -3179,  -2555,  -1925,  -1292,   -656,    -16,    625,   1266,
      1907,   2546,   3183,   3820,   4450,   5076,   5699,   6312,   6919,   7534,
      8124,   8703,   9273,   9829,  10375,  10906,  11423,  11927,  12411,  12880,
     13332,  13768,  14181,  14576,  14950,  15304,  15635,  15946,  16231,  16505,
     16742,  16956,  17144,  17306,  17443,  17555,  17639,  17694,  17722,  17725,
     17699,  17646,  17563,  17453,  17314,  17151,  16953,  16731,  16480,  16202,
     15893,  15560,  15197,  14809,  14393,  13953,  13486,  12994,  12477,  11936,
     11372,  10786,  10177,   9546,   8894,   8224,   7532,   6824,   6086,   5342,
      4583,   3808,   3021,   2219,   1407,    584,   -249,  -1088,  -1939,  -2794,
     -3651,  -4515,  -5382,  -6249,  -7118,  -7985,  -8852,  -9715, -10587, -11440,
    -12286, -13124, -13952, -14773, -15578, -16372, -17152, -17918, -18667, -19399,
    -20111, -20805, -21480, -22133, -22763, -23369, -23952, -24508, -25051, -25555,
    -26030, -26478, -26896, -27283, -27641, -27969, -28261, -28525, -28754, -28950,
    -29113, -29241, -29336, -29396, -29420, -29412, -29366, -29284, -29169, -29017,
    -28831, -28609, -28355, -28065, -27737, -27381, -26987, -26562, -26104, -25613,
    -25090, -24539, -23954, -23341, -22699, -22028, -21330, -20595, -19843, -19066,
    -18269, -17446, -16602, -15738, -14854, -13950, -13029, -12093, -11141, -10175,
     -9197,  -8207,  -7208,  -6197,  -5180,  -4158,  -3115,  -2084,  -1049,    -14
};

/*
 * Waveform name: electric_clarinet, size: 1260 samples
 * Osc. Freq. Divider:   1.0000
 * Waveform Partial Distribution:
 * Order # |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 |
 * Ampld % |  8 | 33 |  8 |  8 | 25 |  8 | 16 |  8 |  8 |    |    |    |
 */
const  int16  electric_clarinet[] =
{
         0,    875,   1754,   2629,   3505,   4373,   5241,   6103,   6958,   7808,
      8649,   9481,  10306,  11119,  11924,  12717,  13498,  14266,  15020,  15759,
     16491,  17200,  17894,  18569,  19230,  19873,  20495,  21102,  21688,  22253,
     22800,  23326,  23830,  24315,  24776,  25217,  25634,  26029,  26401,  26751,
     27079,  27382,  27663,  27921,  28156,  28367,  28555,  28720,  28861,  28981,
     29078,  29151,  29201,  29230,  29238,  29224,  29185,  29127,  29049,  28948,
     28827,  28691,  28533,  28358,  28161,  27950,  27719,  27474,  27212,  26933,
     26641,  26334,  26013,  25680,  25331,  24973,  24602,  24220,  23828,  23421,
     23015,  22597,  22170,  21739,  21302,  20859,  20412,  19959,  19503,  19046,
     18585,  18126,  17663,  17201,  16738,  16277,  15819,  15361,  14906,  14450,
     14004,  13562,  13124,  12694,  12266,  11848,  11437,  11031,  10635,  10245,
      9864,   9493,   9132,   8780,   8437,   8104,   7783,   7471,   7171,   6883,
      6606,   6338,   6084,   5840,   5611,   5391,   5185,   4990,   4809,   4637,
      4476,   4330,   4196,   4072,   3961,   3860,   3772,   3694,   3631,   3576,
      3530,   3496,   3471,   3458,   3455,   3459,   3474,   3496,   3529,   3569,
      3618,   3673,   3734,   3806,   3883,   3965,   4054,   4155,   4255,   4359,
      4467,   4580,   4698,   4815,   4939,   5067,   5194,   5321,   5452,   5586,
      5719,   5852,   5986,   6120,   6253,   6388,   6516,   6651,   6778,   6905,
      7027,   7148,   7267,   7383,   7494,   7601,   7708,   7808,   7905,   8000,
      8088,   8169,   8254,   8328,   8397,   8464,   8523,   8579,   8628,   8675,
      8715,   8749,   8778,   8802,   8822,   8837,   8847,   8851,   8849,   8843,
      8833,   8819,   8801,   8777,   8749,   8716,   8676,   8635,   8590,   8545,
      8494,   8437,   8379,   8318,   8256,   8191,   8122,   8051,   7978,   7907,
      7831,   7754,   7675,   7596,   7516,   7436,   7351,   7269,   7188,   7107,
      7026,   6946,   6867,   6789,   6711,   6633,   6560,   6488,   6414,   6345,
      6276,   6210,   6145,   6084,   6023,   5966,   5906,   5854,   5804,   5756,
      5713,   5670,   5633,   5595,   5562,   5529,   5502,   5477,   5456,   5434,
      5418,   5402,   5391,   5380,   5373,   5369,   5365,   5365,   5366,   5369,
      5374,   5381,   5388,   5398,   5409,   5421,   5435,   5449,   5464,   5479,
      5494,   5510,   5526,   5543,   5556,   5576,   5589,   5603,   5617,   5628,
      5638,   5648,   5656,   5661,   5663,   5665,   5665,   5662,   5657,   5648,
      5637,   5623,   5605,   5586,   5568,   5542,   5512,   5477,   5439,   5397,
      5350,   5300,   5249,   5190,   5128,   5061,   4992,   4916,   4838,   4754,
      4667,   4575,   4479,   4377,   4277,   4166,   4054,   3935,   3813,   3687,
      3557,   3423,   3283,   3143,   2998,   2848,   2695,   2537,   2379,   2217,
      2051,   1881,   1710,   1535,   1357,   1179,    995,    812,    626,    436,
       247,     53,   -137,   -333,   -527,   -726,   -922,  -1119,  -1316,  -1514,
     -1713,  -1913,  -2111,  -2315,  -2513,  -2710,  -2906,  -3102,  -3297,  -3490,
     -3682,  -3874,  -4063,  -4252,  -4440,  -4623,  -4806,  -4988,  -5166,  -5343,
     -5518,  -5688,  -5859,  -6031,  -6195,  -6357,  -6517,  -6672,  -6828,  -6978,
     -7124,  -7268,  -7413,  -7551,  -7688,  -7820,  -7953,  -8078,  -8205,  -8327,
     -8444,  -8562,  -8674,  -8790,  -8897,  -9001,  -9104,  -9201,  -9301,  -9392,
     -9487,  -9577,  -9662,  -9748,  -9829,  -9908,  -9985, -10061, -10134, -10204,
    -10273, -10339, -10404, -10467, -10527, -10586, -10645, -10701, -10754, -10808,
    -10857, -10906, -10953, -11003, -11046, -11090, -11134, -11172, -11212, -11251,
    -11287, -11321, -11350, -11383, -11414, -11442, -11472, -11499, -11524, -11548,
    -11570, -11591, -11610, -11628, -11644, -11658, -11671, -11680, -11688, -11696,
    -11700, -11695, -11695, -11691, -11687, -11681, -11671, -11659, -11644, -11623,
    -11604, -11580, -11553, -11522, -11491, -11453, -11413, -11369, -11320, -11270,
    -11216, -11150, -11087, -11018, -10950, -10875, -10796, -10711, -10622, -10531,
    -10432, -10332, -10223, -10114,  -9998,  -9878,  -9753,  -9625,  -9488,  -9350,
     -9206,  -9057,  -8905,  -8747,  -8585,  -8419,  -8245,  -8071,  -7891,  -7706,
     -7518,  -7324,  -7128,  -6927,  -6723,  -6510,  -6300,  -6086,  -5865,  -5643,
     -5423,  -5195,  -4966,  -4732,  -4497,  -4261,  -4022,  -3781,  -3538,  -3293,
     -3049,  -2804,  -2558,  -2312,  -2065,  -1820,  -1571,  -1327,  -1081,   -838,
      -601,   -361,   -121,    115,    350,    584,    812,   1039,   1262,   1481,
      1695,   1905,   2111,   2315,   2513,   2706,   2893,   3076,   3248,   3419,
      3578,   3737,   3886,   4032,   4171,   4300,   4425,   4540,   4647,   4750,
      4843,   4929,   5004,   5075,   5138,   5191,   5235,   5271,   5301,   5322,
      5335,   5337,   5333,   5319,   5297,   5271,   5231,   5186,   5130,   5070,
      4999,   4923,   4839,   4746,   4646,   4540,   4425,   4305,   4178,   4050,
      3909,   3763,   3614,   3457,   3293,   3127,   2954,   2776,   2597,   2411,
      2222,   2030,   1836,   1637,   1436,   1233,   1029,    822,    620,    411,
       204,     -4,   -214,   -423,   -633,   -839,  -1046,  -1251,  -1455,  -1654,
     -1852,  -2048,  -2241,  -2427,  -2613,  -2795,  -2971,  -3145,  -3307,  -3468,
     -3625,  -3778,  -3923,  -4062,  -4195,  -4323,  -4443,  -4557,  -4664,  -4763,
     -4854,  -4939,  -5015,  -5086,  -5147,  -5202,  -5245,  -5283,  -5313,  -5333,
     -5347,  -5350,  -5345,  -5332,  -5311,  -5283,  -5245,  -5198,  -5142,  -5082,
     -5011,  -4932,  -4843,  -4749,  -4648,  -4537,  -4420,  -4298,  -4164,  -4027,
     -3879,  -3726,  -3566,  -3403,  -3230,  -3051,  -2865,  -2674,  -2478,  -2278,
     -2074,  -1865,  -1650,  -1431,  -1207,   -981,   -750,   -522,   -286,    -46,
       194,    438,    683,    932,   1179,   1432,   1681,   1933,   2185,   2437,
      2690,   2941,   3193,   3444,   3695,   3943,   4190,   4431,   4676,   4917,
      5157,   5394,   5628,   5863,   6091,   6316,   6541,   6759,   6975,   7186,
      7395,   7599,   7799,   7995,   8184,   8375,   8557,   8735,   8909,   9077,
      9242,   9402,   9557,   9709,   9853,   9993,  10129,  10259,  10383,  10507,
     10621,  10734,  10839,  10941,  11039,  11130,  11222,  11302,  11382,  11457,
     11528,  11592,  11652,  11710,  11762,  11809,  11854,  11893,  11929,  11961,
     11990,  12013,  12038,  12055,  12070,  12087,  12094,  12099,  12102,  12101,
     12099,  12092,  12082,  12070,  12057,  12039,  12020,  11998,  11973,  11947,
     11919,  11889,  11856,  11821,  11784,  11750,  11709,  11667,  11622,  11576,
     11530,  11481,  11429,  11375,  11323,  11265,  11206,  11148,  11084,  11021,
     10957,  10892,  10823,  10753,  10681,  10606,  10531,  10455,  10376,  10295,
     10212,  10128,  10042,   9954,   9862,   9770,   9676,   9580,   9480,   9381,
      9278,   9169,   9064,   8952,   8838,   8723,   8607,   8489,   8367,   8244,
      8117,   7990,   7860,   7726,   7594,   7453,   7315,   7172,   7029,   6880,
      6732,   6583,   6430,   6272,   6110,   5950,   5788,   5624,   5459,   5290,
      5123,   4951,   4778,   4604,   4427,   4251,   4073,   3893,   3711,   3529,
      3345,   3163,   2979,   2795,   2605,   2421,   2235,   2049,   1862,   1676,
      1490,   1305,   1120,    937,    754,    573,    389,    210,     30,   -145,
      -323,   -497,   -670,   -840,  -1007,  -1175,  -1337,  -1499,  -1658,  -1812,
     -1967,  -2117,  -2264,  -2406,  -2550,  -2687,  -2823,  -2954,  -3080,  -3206,
     -3327,  -3444,  -3558,  -3663,  -3770,  -3871,  -3970,  -4065,  -4157,  -4243,
     -4326,  -4405,  -4482,  -4553,  -4622,  -4685,  -4747,  -4804,  -4859,  -4906,
     -4954,  -4998,  -5033,  -5070,  -5104,  -5135,  -5162,  -5187,  -5209,  -5229,
     -5247,  -5262,  -5276,  -5286,  -5295,  -5302,  -5307,  -5312,  -5315,  -5316,
     -5316,  -5316,  -5310,  -5308,  -5305,  -5304,  -5301,  -5300,  -5296,  -5293,
     -5291,  -5290,  -5289,  -5289,  -5290,  -5290,  -5294,  -5298,  -5304,  -5312,
     -5322,  -5333,  -5346,  -5361,  -5377,  -5397,  -5417,  -5440,  -5467,  -5494,
     -5525,  -5557,  -5594,  -5630,  -5670,  -5711,  -5758,  -5804,  -5856,  -5907,
     -5962,  -6022,  -6082,  -6144,  -6207,  -6273,  -6341,  -6411,  -6482,  -6555,
     -6628,  -6704,  -6781,  -6861,  -6939,  -7017,  -7099,  -7181,  -7262,  -7344,
     -7426,  -7514,  -7595,  -7676,  -7758,  -7836,  -7914,  -7991,  -8067,  -8141,
     -8215,  -8286,  -8351,  -8418,  -8481,  -8543,  -8601,  -8655,  -8706,  -8755,
     -8801,  -8846,  -8880,  -8913,  -8942,  -8965,  -8986,  -9000,  -9010,  -9015,
     -9015,  -9011,  -9002,  -8989,  -8970,  -8944,  -8914,  -8878,  -8839,  -8793,
     -8743,  -8687,  -8624,  -8559,  -8487,  -8411,  -8328,  -8244,  -8154,  -8054,
     -7957,  -7855,  -7745,  -7633,  -7519,  -7398,  -7277,  -7153,  -7024,  -6893,
     -6755,  -6621,  -6483,  -6344,  -6204,  -6066,  -5921,  -5779,  -5637,  -5496,
     -5356,  -5216,  -5076,  -4940,  -4808,  -4676,  -4545,  -4419,  -4299,  -4174,
     -4060,  -3951,  -3848,  -3749,  -3655,  -3569,  -3489,  -3416,  -3348,  -3292,
     -3242,  -3199,  -3166,  -3140,  -3125,  -3118,  -3123,  -3136,  -3159,  -3189,
     -3235,  -3292,  -3359,  -3439,  -3529,  -3630,  -3744,  -3869,  -4007,  -4155,
     -4316,  -4492,  -4678,  -4875,  -5085,  -5307,  -5542,  -5788,  -6048,  -6318,
     -6602,  -6895,  -7199,  -7515,  -7844,  -8180,  -8529,  -8887,  -9255,  -9631,
    -10017, -10413, -10817, -11227, -11646, -12070, -12503, -12943, -13390, -13840,
    -14294, -14751, -15213, -15679, -16146, -16614, -17083, -17553, -18022, -18493,
    -18958, -19425, -19887, -20347, -20804, -21254, -21700, -22139, -22577, -23004,
    -23422, -23828, -24228, -24618, -24997, -25365, -25719, -26064, -26392, -26707,
    -27008, -27292, -27564, -27819, -28056, -28277, -28479, -28665, -28834, -28981,
    -29105, -29214, -29298, -29364, -29408, -29433, -29434, -29412, -29369, -29304,
    -29216, -29104, -28968, -28812, -28631, -28428, -28200, -27949, -27675, -27378,
    -27059, -26715, -26349, -25960, -25550, -25116, -24661, -24184, -23685, -23166,
    -22625, -22064, -21485, -20885, -20265, -19630, -18975, -18297, -17610, -16904,
    -16184, -15447, -14698, -13934, -13157, -12367, -11568, -10756,  -9936,  -9105,
     -8268,  -7422,  -6568,  -5709,  -4845,  -3974,  -3099,  -2222,  -1346,   -468
};

/*
 * Waveform name: clean_bright_flute, size: 1260 samples
 * Osc. Freq. Divider:   1.0000
 * Waveform Partial Distribution:
 * Order # |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 |
 * Ampld % | 70 |    |    |    |    |    | 20 |    | 20 |    |    |    |
 */
const  int16  clean_bright_flute[] =
{
         0,    621,   1242,   1861,   2478,   3092,   3701,   4306,   4905,   5496,
      6080,   6656,   7224,   7780,   8327,   8863,   9386,   9896,  10393,  10877,
     11346,  11799,  12238,  12660,  13065,  13452,  13822,  14174,  14508,  14823,
     15119,  15395,  15652,  15889,  16105,  16303,  16478,  16635,  16769,  16885,
     16979,  17053,  17107,  17141,  17155,  17150,  17124,  17079,  17015,  16932,
     16832,  16714,  16577,  16425,  16255,  16070,  15868,  15652,  15422,  15177,
     14920,  14650,  14368,  14075,  13773,  13459,  13137,  12807,  12468,  12124,
     11773,  11418,  11058,  10694,  10328,   9959,   9589,   9218,   8849,   8479,
      8112,   7748,   7388,   7031,   6679,   6333,   5994,   5661,   5338,   5022,
      4715,   4418,   4132,   3857,   3594,   3341,   3104,   2878,   2666,   2468,
      2285,   2116,   1963,   1826,   1705,   1600,   1511,   1440,   1385,   1347,
      1327,   1323,   1338,   1370,   1418,   1484,   1568,   1668,   1786,   1921,
      2073,   2240,   2425,   2625,   2842,   3071,   3319,   3578,   3855,   4143,
      4446,   4761,   5090,   5429,   5780,   6141,   6515,   6897,   7289,   7688,
      8096,   8510,   8932,   9360,   9793,  10231,  10674,  11119,  11567,  12018,
     12469,  12922,  13375,  13827,  14278,  14728,  15173,  15618,  16058,  16494,
     16924,  17349,  17770,  18183,  18587,  18986,  19375,  19757,  20129,  20492,
     20845,  21188,  21519,  21840,  22150,  22448,  22733,  23007,  23268,  23516,
     23751,  23973,  24183,  24378,  24561,  24732,  24887,  25031,  25160,  25275,
     25378,  25467,  25544,  25607,  25658,  25697,  25722,  25735,  25737,  25727,
     25705,  25673,  25629,  25575,  25512,  25439,  25356,  25265,  25163,  25056,
     24940,  24817,  24688,  24551,  24409,  24262,  24109,  23952,  23790,  23626,
     23458,  23288,  23116,  22942,  22767,  22591,  22415,  22239,  22063,  21889,
     21716,  21546,  21375,  21210,  21047,  20888,  20732,  20581,  20434,  20291,
     20153,  20021,  19895,  19774,  19660,  19551,  19449,  19352,  19264,  19182,
     19107,  19039,  18978,  18924,  18878,  18838,  18805,  18780,  18763,  18752,
     18747,  18750,  18760,  18777,  18799,  18828,  18863,  18903,  18951,  19003,
     19061,  19124,  19192,  19265,  19341,  19420,  19505,  19591,  19682,  19775,
     19871,  19968,  20066,  20169,  20270,  20373,  20476,  20580,  20684,  20786,
     20888,  20989,  21089,  21186,  21281,  21376,  21466,  21554,  21639,  21720,
     21798,  21872,  21941,  22007,  22067,  22124,  22174,  22220,  22263,  22298,
     22330,  22355,  22375,  22388,  22396,  22400,  22396,  22388,  22375,  22355,
     22330,  22298,  22263,  22220,  22174,  22124,  22067,  22007,  21941,  21872,
     21798,  21720,  21639,  21554,  21466,  21376,  21281,  21186,  21089,  20989,
     20888,  20786,  20684,  20580,  20476,  20374,  20270,  20169,  20066,  19968,
     19871,  19775,  19682,  19591,  19505,  19420,  19341,  19265,  19192,  19124,
     19061,  19003,  18951,  18903,  18863,  18828,  18799,  18777,  18760,  18750,
     18747,  18752,  18763,  18780,  18805,  18838,  18878,  18924,  18978,  19039,
     19107,  19182,  19264,  19352,  19449,  19551,  19660,  19774,  19895,  20021,
     20153,  20291,  20434,  20581,  20732,  20888,  21047,  21210,  21375,  21546,
     21716,  21889,  22063,  22239,  22415,  22591,  22767,  22942,  23116,  23288,
     23458,  23626,  23790,  23952,  24109,  24262,  24409,  24551,  24688,  24817,
     24940,  25056,  25163,  25265,  25356,  25439,  25512,  25575,  25629,  25673,
     25705,  25727,  25737,  25735,  25722,  25697,  25658,  25607,  25544,  25467,
     25378,  25275,  25160,  25031,  24887,  24732,  24561,  24378,  24183,  23973,
     23751,  23516,  23268,  23007,  22733,  22448,  22150,  21840,  21519,  21188,
     20845,  20492,  20129,  19757,  19375,  18985,  18587,  18183,  17770,  17349,
     16924,  16494,  16058,  15618,  15173,  14728,  14278,  13827,  13375,  12922,
     12469,  12018,  11567,  11119,  10674,  10231,   9793,   9360,   8932,   8510,
      8096,   7688,   7289,   6897,   6515,   6141,   5780,   5429,   5090,   4761,
      4446,   4143,   3855,   3578,   3319,   3071,   2842,   2625,   2425,   2240,
      2073,   1921,   1786,   1668,   1568,   1484,   1418,   1370,   1338,   1323,
      1327,   1347,   1385,   1440,   1511,   1601,   1705,   1826,   1963,   2116,
      2285,   2468,   2666,   2878,   3104,   3341,   3594,   3857,   4132,   4418,
      4715,   5022,   5338,   5661,   5994,   6333,   6679,   7031,   7388,   7748,
      8112,   8479,   8849,   9218,   9589,   9959,  10328,  10694,  11058,  11418,
     11773,  12124,  12468,  12807,  13137,  13459,  13773,  14075,  14368,  14650,
     14920,  15177,  15422,  15652,  15868,  16070,  16255,  16425,  16577,  16714,
     16832,  16932,  17015,  17079,  17124,  17150,  17155,  17141,  17107,  17053,
     16979,  16885,  16769,  16635,  16478,  16303,  16105,  15889,  15652,  15395,
     15119,  14823,  14508,  14174,  13822,  13452,  13065,  12660,  12238,  11799,
     11346,  10877,  10393,   9896,   9386,   8863,   8327,   7780,   7224,   6656,
      6080,   5496,   4905,   4306,   3701,   3092,   2478,   1861,   1242,    621,
         0,   -621,  -1242,  -1861,  -2478,  -3092,  -3701,  -4306,  -4905,  -5496,
     -6080,  -6656,  -7224,  -7780,  -8327,  -8863,  -9386,  -9896, -10393, -10877,
    -11346, -11799, -12238, -12660, -13065, -13452, -13822, -14174, -14508, -14823,
    -15119, -15395, -15652, -15889, -16105, -16303, -16478, -16635, -16769, -16885,
    -16979, -17053, -17107, -17141, -17155, -17150, -17124, -17079, -17015, -16932,
    -16832, -16714, -16577, -16425, -16255, -16070, -15868, -15652, -15422, -15177,
    -14920, -14650, -14368, -14075, -13773, -13459, -13137, -12807, -12468, -12124,
    -11773, -11418, -11058, -10694, -10328,  -9958,  -9589,  -9218,  -8849,  -8479,
     -8112,  -7748,  -7388,  -7031,  -6679,  -6333,  -5994,  -5661,  -5338,  -5022,
     -4715,  -4418,  -4132,  -3857,  -3594,  -3341,  -3104,  -2878,  -2666,  -2468,
     -2285,  -2116,  -1963,  -1826,  -1705,  -1600,  -1511,  -1440,  -1385,  -1347,
     -1327,  -1323,  -1338,  -1370,  -1418,  -1484,  -1568,  -1668,  -1786,  -1921,
     -2073,  -2240,  -2425,  -2625,  -2842,  -3071,  -3319,  -3578,  -3855,  -4143,
     -4446,  -4761,  -5090,  -5429,  -5780,  -6141,  -6515,  -6897,  -7289,  -7688,
     -8096,  -8510,  -8932,  -9360,  -9793, -10231, -10674, -11119, -11567, -12018,
    -12469, -12922, -13375, -13827, -14278, -14728, -15173, -15618, -16058, -16494,
    -16924, -17349, -17770, -18183, -18587, -18985, -19375, -19757, -20129, -20492,
    -20846, -21188, -21519, -21840, -22150, -22448, -22733, -23007, -23268, -23516,
    -23751, -23973, -24183, -24378, -24561, -24732, -24887, -25031, -25160, -25275,
    -25378, -25467, -25544, -25607, -25658, -25697, -25722, -25735, -25737, -25727,
    -25705, -25673, -25629, -25575, -25512, -25439, -25356, -25265, -25163, -25056,
    -24940, -24817, -24688, -24551, -24409, -24262, -24109, -23952, -23790, -23626,
    -23458, -23288, -23116, -22942, -22767, -22591, -22415, -22239, -22063, -21889,
    -21716, -21546, -21375, -21210, -21047, -20888, -20732, -20581, -20434, -20291,
    -20153, -20021, -19895, -19774, -19660, -19551, -19449, -19352, -19264, -19182,
    -19107, -19039, -18978, -18924, -18878, -18837, -18805, -18780, -18763, -18752,
    -18747, -18750, -18760, -18777, -18799, -18828, -18863, -18903, -18951, -19003,
    -19061, -19124, -19192, -19265, -19341, -19420, -19505, -19591, -19682, -19775,
    -19871, -19968, -20066, -20169, -20270, -20373, -20476, -20580, -20684, -20786,
    -20888, -20989, -21089, -21186, -21281, -21376, -21466, -21554, -21639, -21720,
    -21798, -21872, -21941, -22007, -22067, -22124, -22174, -22220, -22263, -22298,
    -22330, -22355, -22375, -22388, -22396, -22400, -22396, -22388, -22375, -22355,
    -22330, -22298, -22263, -22220, -22174, -22124, -22067, -22007, -21941, -21872,
    -21798, -21720, -21639, -21554, -21466, -21376, -21281, -21186, -21089, -20989,
    -20888, -20786, -20684, -20580, -20476, -20373, -20270, -20169, -20066, -19968,
    -19871, -19775, -19682, -19591, -19505, -19420, -19341, -19265, -19192, -19124,
    -19061, -19003, -18951, -18903, -18863, -18828, -18799, -18777, -18760, -18750,
    -18747, -18752, -18763, -18780, -18805, -18838, -18878, -18924, -18978, -19039,
    -19107, -19182, -19264, -19352, -19449, -19551, -19660, -19774, -19895, -20021,
    -20153, -20291, -20434, -20581, -20732, -20888, -21047, -21210, -21375, -21546,
    -21716, -21889, -22063, -22239, -22415, -22591, -22767, -22942, -23116, -23288,
    -23458, -23626, -23790, -23952, -24109, -24262, -24409, -24551, -24688, -24817,
    -24940, -25056, -25163, -25265, -25356, -25439, -25512, -25575, -25629, -25673,
    -25705, -25727, -25737, -25735, -25722, -25696, -25658, -25607, -25544, -25467,
    -25378, -25275, -25160, -25031, -24887, -24732, -24561, -24378, -24183, -23973,
    -23751, -23516, -23268, -23007, -22733, -22448, -22150, -21840, -21519, -21188,
    -20845, -20492, -20129, -19757, -19375, -18985, -18587, -18183, -17770, -17349,
    -16924, -16494, -16058, -15618, -15173, -14728, -14278, -13827, -13375, -12922,
    -12469, -12018, -11567, -11119, -10674, -10231,  -9793,  -9360,  -8932,  -8510,
     -8096,  -7688,  -7289,  -6897,  -6515,  -6141,  -5780,  -5429,  -5090,  -4761,
     -4446,  -4143,  -3855,  -3578,  -3319,  -3071,  -2842,  -2625,  -2425,  -2240,
     -2073,  -1921,  -1786,  -1668,  -1568,  -1484,  -1418,  -1370,  -1338,  -1323,
     -1327,  -1347,  -1385,  -1440,  -1511,  -1599,  -1705,  -1826,  -1963,  -2116,
     -2285,  -2468,  -2666,  -2878,  -3104,  -3341,  -3594,  -3857,  -4132,  -4418,
     -4715,  -5022,  -5338,  -5661,  -5994,  -6333,  -6679,  -7031,  -7388,  -7748,
     -8112,  -8479,  -8849,  -9218,  -9589,  -9959, -10328, -10694, -11058, -11418,
    -11773, -12124, -12468, -12807, -13137, -13459, -13773, -14075, -14368, -14650,
    -14920, -15177, -15422, -15652, -15868, -16070, -16255, -16425, -16577, -16714,
    -16832, -16932, -17015, -17079, -17124, -17150, -17155, -17141, -17107, -17053,
    -16979, -16885, -16769, -16635, -16478, -16303, -16105, -15889, -15652, -15395,
    -15119, -14823, -14508, -14174, -13822, -13453, -13065, -12660, -12238, -11799,
    -11346, -10877, -10393,  -9896,  -9386,  -8862,  -8327,  -7780,  -7224,  -6656,
     -6080,  -5496,  -4905,  -4306,  -3701,  -3092,  -2478,  -1861,  -1242,   -621
};


/*
 * Waveform name: recorder_008271200, size: 1260 samples
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 0 | 0 | 8 | 2 | 7 | 1 | 2 | 0 | 0 |
 */
const  int16  recorder_008271200[] =
{
         0,    828,   1661,   2494,   3325,   4151,   4975,   5797,   6611,   7422,
      8229,   9027,   9819,  10607,  11383,  12152,  12913,  13661,  14403,  15132,
     15849,  16559,  17252,  17935,  18603,  19259,  19902,  20530,  21142,  21739,
     22322,  22888,  23439,  23974,  24489,  24990,  25475,  25940,  26388,  26818,
     27230,  27625,  28001,  28360,  28697,  29017,  29319,  29601,  29865,  30111,
     30337,  30545,  30734,  30904,  31056,  31189,  31306,  31403,  31483,  31543,
     31588,  31616,  31626,  31618,  31595,  31555,  31497,  31425,  31337,  31232,
     31114,  30979,  30834,  30670,  30497,  30307,  30105,  29893,  29667,  29430,
     29183,  28926,  28654,  28376,  28089,  27789,  27485,  27170,  26848,  26517,
     26180,  25837,  25489,  25136,  24776,  24415,  24045,  23675,  23300,  22922,
     22543,  22161,  21777,  21392,  21008,  20623,  20239,  19857,  19473,  19089,
     18707,  18331,  17953,  17581,  17212,  16844,  16483,  16125,  15771,  15424,
     15080,  14741,  14411,  14084,  13764,  13452,  13144,  12844,  12553,  12270,
     11993,  11725,  11465,  11215,  10975,  10740,  10517,  10299,  10093,   9898,
      9711,   9532,   9367,   9208,   9062,   8924,   8798,   8683,   8576,   8481,
      8396,   8320,   8259,   8204,   8162,   8131,   8110,   8097,   8097,   8108,
      8132,   8163,   8204,   8257,   8320,   8393,   8478,   8570,   8674,   8788,
      8913,   9047,   9188,   9343,   9504,   9677,   9857,  10044,  10242,  10449,
     10664,  10888,  11118,  11357,  11604,  11858,  12119,  12386,  12661,  12942,
     13233,  13525,  13824,  14130,  14439,  14753,  15073,  15394,  15723,  16054,
     16389,  16726,  17066,  17407,  17752,  18098,  18447,  18794,  19145,  19495,
     19841,  20189,  20537,  20884,  21231,  21574,  21915,  22252,  22586,  22919,
     23249,  23569,  23888,  24201,  24510,  24812,  25107,  25396,  25679,  25954,
     26218,  26479,  26729,  26968,  27201,  27423,  27635,  27837,  28028,  28205,
     28374,  28531,  28674,  28806,  28923,  29029,  29122,  29199,  29264,  29313,
     29348,  29369,  29374,  29365,  29340,  29299,  29241,  29171,  29083,  28977,
     28857,  28720,  28566,  28395,  28209,  28007,  27787,  27548,  27295,  27023,
     26735,  26430,  26110,  25773,  25420,  25048,  24660,  24260,  23840,  23405,
     22955,  22489,  22010,  21515,  21003,  20481,  19943,  19390,  18825,  18247,
     17654,  17053,  16438,  15811,  15172,  14522,  13864,  13195,  12515,  11830,
     11132,  10427,   9716,   8997,   8271,   7544,   6804,   6064,   5316,   4567,
      3814,   3057,   2298,   1539,    778,     16,   -742,  -1502,  -2262,  -3022,
     -3779,  -4531,  -5283,  -6030,  -6770,  -7510,  -8239,  -8965,  -9684, -10398,
    -11103, -11801, -12487, -13168, -13838, -14497, -15149, -15789, -16415, -17032,
    -17634, -18228, -18808, -19374, -19929, -20468, -20992, -21503, -22002, -22482,
    -22948, -23401, -23837, -24259, -24660, -25048, -25422, -25777, -26115, -26437,
    -26743, -27032, -27306, -27560, -27801, -28021, -28225, -28413, -28586, -28740,
    -28878, -29000, -29105, -29195, -29268, -29326, -29366, -29393, -29403, -29400,
    -29379, -29344, -29296, -29233, -29156, -29063, -28956, -28841, -28709, -28566,
    -28410, -28240, -28063, -27872, -27670, -27458, -27236, -27004, -26764, -26514,
    -26254, -25988, -25712, -25430, -25141, -24844, -24541, -24232, -23919, -23599,
    -23277, -22946, -22613, -22279, -21939, -21596, -21253, -20905, -20557, -20209,
    -19859, -19511, -19159, -18808, -18460, -18109, -17762, -17415, -17073, -16731,
    -16393, -16056, -15723, -15394, -15071, -14750, -14435, -14123, -13817, -13517,
    -13222, -12931, -12649, -12372, -12104, -11841, -11586, -11337, -11097, -10865,
    -10642, -10426, -10216, -10018,  -9830,  -9649,  -9475,  -9313,  -9159,  -9014,
     -8881,  -8756,  -8641,  -8537,  -8444,  -8360,  -8285,  -8222,  -8169,  -8127,
     -8096,  -8073,  -8063,  -8062,  -8073,  -8094,  -8127,  -8169,  -8224,  -8287,
     -8363,  -8447,  -8542,  -8650,  -8766,  -8892,  -9032,  -9179,  -9337,  -9504,
     -9684,  -9872, -10067, -10275, -10494, -10718, -10954, -11195, -11447, -11708,
    -11977, -12256, -12541, -12833, -13133, -13444, -13757, -14077, -14407, -14738,
    -15078, -15424, -15771, -16126, -16487, -16849, -17219, -17589, -17963, -18342,
    -18720, -19103, -19487, -19873, -20258, -20642, -21027, -21413, -21800, -22183,
    -22566, -22948, -23326, -23701, -24073, -24444, -24806, -25167, -25520, -25870,
    -26214, -26551, -26882, -27204, -27520, -27824, -28124, -28413, -28690, -28961,
    -29218, -29465, -29702, -29928, -30142, -30343, -30532, -30705, -30868, -31012,
    -31147, -31265, -31369, -31456, -31528, -31585, -31625, -31646, -31653, -31643,
    -31615, -31567, -31505, -31425, -31327, -31209, -31076, -30923, -30750, -30559,
    -30351, -30123, -29876, -29611, -29327, -29024, -28702, -28364, -28003, -27625,
    -27230, -26816, -26385, -25936, -25468, -24983, -24481, -23962, -23427, -22875,
    -22308, -21724, -21126, -20512, -19883, -19238, -18581, -17912, -17228, -16533,
    -15824, -15105, -14375, -13632, -12883, -12122, -11351, -10574,  -9787,  -8993,
     -8195,  -7388,  -6578,  -5762,  -4940,  -4116,  -3289,  -2457,  -1626,   -794,
        35,    865,   1697,   2529,   3360,   4186,   5009,   5830,   6645,   7455,
      8261,   9059,   9851,  10636,  11413,  12181,  12941,  13688,  14428,  15157,
     15873,  16581,  17275,  17956,  18623,  19277,  19919,  20546,  21156,  21752,
     22333,  22899,  23447,  23981,  24496,  24995,  25478,  25941,  26388,  26818,
     27229,  27621,  27996,  28353,  28688,  29007,  29308,  29588,  29851,  30097,
     30321,  30527,  30715,  30885,  31035,  31167,  31283,  31379,  31456,  31517,
     31562,  31588,  31597,  31587,  31564,  31524,  31465,  31392,  31303,  31198,
     31080,  30944,  30799,  30635,  30460,  30272,  30070,  29858,  29632,  29395,
     29147,  28889,  28619,  28341,  28053,  27756,  27451,  27136,  26815,  26485,
     26149,  25806,  25458,  25107,  24747,  24388,  24019,  23648,  23276,  22899,
     22520,  22140,  21758,  21373,  20989,  20607,  20225,  19843,  19460,  19078,
     18697,  18322,  17946,  17575,  17207,  16842,  16483,  16125,  15772,  15427,
     15084,  14748,  14418,  14092,  13775,  13463,  13157,  12858,  12569,  12286,
     12011,  11744,  11486,  11237,  10997,  10764,  10542,  10325,  10119,   9926,
      9740,   9562,   9396,   9240,   9094,   8957,   8832,   8716,   8610,   8514,
      8431,   8356,   8294,   8240,   8198,   8166,   8143,   8132,   8134,   8145,
      8167,   8198,   8239,   8291,   8354,   8427,   8511,   8603,   8707,   8820,
      8943,   9076,   9218,   9371,   9531,   9702,   9882,  10067,  10264,  10472,
     10685,  10907,  11136,  11374,  11619,  11872,  12132,  12397,  12673,  12951,
     13240,  13532,  13828,  14133,  14441,  14753,  15073,  15393,  15719,  16049,
     16382,  16717,  17056,  17396,  17740,  18084,  18433,  18779,  19127,  19475,
     19821,  20168,  20515,  20862,  21207,  21547,  21888,  22225,  22558,  22889,
     23218,  23538,  23857,  24169,  24476,  24778,  25073,  25363,  25643,  25919,
     26183,  26443,  26694,  26933,  27166,  27388,  27600,  27802,  27992,  28170,
     28338,  28496,  28640,  28772,  28889,  28996,  29090,  29168,  29233,  29282,
     29319,  29341,  29347,  29338,  29313,  29275,  29219,  29149,  29062,  28958,
     28837,  28702,  28551,  28381,  28195,  27994,  27775,  27538,  27287,  27016,
     26729,  26426,  26108,  25773,  25420,  25049,  24663,  24264,  23847,  23412,
     22964,  22500,  22022,  21527,  21017,  20496,  19960,  19408,  18845,  18268,
     17676,  17075,  16462,  15837,  15198,  14549,  13892,  13225,  12545,  11859,
     11164,  10459,   9749,   9031,   8305,   7578,   6837,   6099,   5352,   4602,
      3850,   3093,   2334,   1572,    813,     53,   -706,  -1467,  -2227,  -2987,
     -3745,  -4498,  -5249,  -5996,  -6738,  -7478,  -8207,  -8936,  -9655, -10368,
    -11074, -11774, -12462, -13143, -13814, -14474, -15126, -15768, -16396, -17014,
    -17617, -18213, -18794, -19362, -19918, -20457, -20984, -21496, -21995, -22478,
    -22946, -23399, -23837, -24259, -24662, -25052, -25427, -25784, -26124, -26447,
    -26754, -27045, -27320, -27574, -27816, -28039, -28244, -28433, -28607, -28763,
    -28900, -29024, -29132, -29222, -29295, -29354, -29396, -29424, -29434, -29431,
    -29411, -29378, -29330, -29267, -29190, -29098, -28992, -28876, -28746, -28601,
    -28445, -28275, -28098, -27907, -27705, -27494, -27271, -27039, -26799, -26548,
    -26288, -26021, -25746, -25462, -25172, -24875, -24572, -24262, -23947, -23625,
    -23304, -22972, -22637, -22301, -21961, -21617, -21273, -20925, -20575, -20224,
    -19873, -19525, -19172, -18820, -18470, -18117, -17769, -17421, -17077, -16733,
    -16393, -16056, -15722, -15392, -15067, -14743, -14428, -14115, -13806, -13505,
    -13209, -12917, -12633, -12355, -12086, -11822, -11565, -11315, -11074, -10841,
    -10617, -10400, -10190,  -9990,  -9801,  -9620,  -9445,  -9281,  -9127,  -8982,
     -8847,  -8722,  -8607,  -8503,  -8409,  -8325,  -8250,  -8186,  -8132,  -8092,
     -8062,  -8038,  -8027,  -8026,  -8038,  -8059,  -8092,  -8135,  -8190,  -8253,
     -8329,  -8415,  -8510,  -8618,  -8736,  -8863,  -9003,  -9150,  -9311,  -9479,
     -9659,  -9848, -10045, -10253, -10473, -10698, -10935, -11178, -11431, -11694,
    -11965, -12244, -12529, -12824, -13126, -13437, -13753, -14074, -14406, -14738,
    -15078, -15425, -15775, -16132, -16494, -16858, -17228, -17601, -17976, -18356,
    -18734, -19119, -19505, -19893, -20277, -20664, -21050, -21436, -21824, -22210,
    -22593, -22975, -23354, -23731, -24104, -24475, -24837, -25200, -25554, -25903,
    -26247, -26584, -26917, -27239, -27555, -27861, -28159, -28448, -28725, -28996,
    -29253, -29500, -29739, -29963, -30177, -30378, -30566, -30739, -30901, -31046,
    -31180, -31296, -31400, -31487, -31557, -31613, -31651, -31672, -31680, -31667,
    -31637, -31590, -31526, -31445, -31347, -31227, -31091, -30937, -30764, -30571,
    -30362, -30133, -29885, -29618, -29333, -29028, -28704, -28364, -28003, -27624,
    -27228, -26812, -26378, -25929, -25460, -24972, -24469, -23950, -23413, -22860,
    -22291, -21706, -21106, -20491, -19860, -19216, -18557, -17887, -17203, -16507,
    -15796, -15076, -14345, -13602, -12851, -12090, -11319, -10541,  -9753,  -8959,
     -8162,  -7353,  -6543,  -5727,  -4904,  -4079,  -3253,  -2423,  -1591,   -758
};

/*
 * Waveform name: hammond_rock_8888, size: 1260 samples
 * Osc. Freq. Divider:   1.000 OR 2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 8 | 8 | 8 | 8 | 0 | 0 | 0 | 0 | 0 |
 */
const  int16  hammond_rock_8888[] =
{
         0,    485,    975,   1463,   1952,   2439,   2927,   3415,   3899,   4384,
      4867,   5350,   5831,   6310,   6789,   7265,   7740,   8211,   8681,   9150,
      9617,  10080,  10542,  11000,  11456,  11910,  12359,  12808,  13251,  13690,
     14130,  14563,  14993,  15418,  15843,  16262,  16675,  17086,  17492,  17896,
     18293,  18687,  19076,  19460,  19839,  20215,  20583,  20950,  21309,  21664,
     22015,  22357,  22696,  23030,  23357,  23679,  23997,  24306,  24611,  24912,
     25204,  25492,  25773,  26050,  26317,  26580,  26836,  27088,  27332,  27569,
     27801,  28025,  28242,  28455,  28661,  28858,  29050,  29236,  29416,  29585,
     29751,  29909,  30062,  30207,  30346,  30476,  30601,  30717,  30829,  30932,
     31030,  31121,  31205,  31282,  31349,  31414,  31471,  31520,  31564,  31599,
     31629,  31651,  31667,  31678,  31680,  31678,  31666,  31650,  31624,  31596,
     31559,  31519,  31470,  31413,  31352,  31286,  31212,  31132,  31046,  30956,
     30857,  30753,  30645,  30530,  30411,  30284,  30153,  30014,  29873,  29725,
     29570,  29414,  29250,  29082,  28909,  28731,  28548,  28360,  28168,  27972,
     27771,  27565,  27355,  27140,  26923,  26701,  26477,  26247,  26013,  25775,
     25534,  25291,  25042,  24793,  24540,  24281,  24024,  23760,  23496,  23228,
     22957,  22684,  22408,  22130,  21850,  21568,  21286,  21001,  20713,  20423,
     20133,  19842,  19547,  19253,  18958,  18660,  18364,  18066,  17768,  17467,
     17167,  16866,  16565,  16266,  15964,  15662,  15362,  15061,  14760,  14461,
     14161,  13862,  13565,  13264,  12969,  12673,  12378,  12086,  11793,  11502,
     11213,  10924,  10638,  10354,  10072,   9788,   9511,   9232,   8957,   8684,
      8415,   8147,   7882,   7619,   7358,   7099,   6843,   6590,   6341,   6093,
      5849,   5609,   5371,   5135,   4904,   4675,   4450,   4228,   4011,   3795,
      3585,   3376,   3173,   2972,   2776,   2583,   2394,   2207,   2027,   1849,
      1674,   1504,   1338,   1178,   1020,    866,    715,    571,    429,    292,
       160,     31,    -93,   -213,   -328,   -440,   -549,   -654,   -752,   -847,
      -938,  -1024,  -1108,  -1185,  -1260,  -1330,  -1396,  -1455,  -1513,  -1567,
     -1614,  -1660,  -1701,  -1740,  -1771,  -1798,  -1824,  -1844,  -1861,  -1875,
     -1883,  -1888,  -1889,  -1886,  -1881,  -1870,  -1856,  -1840,  -1819,  -1795,
     -1767,  -1736,  -1701,  -1663,  -1622,  -1578,  -1531,  -1478,  -1427,  -1369,
     -1310,  -1247,  -1181,  -1112,  -1043,   -968,   -892,   -813,   -731,   -647,
      -562,   -472,   -381,   -290,   -196,    -98,      0,    101,    204,    308,
       414,    522,    630,    742,    852,    968,   1082,   1196,   1314,   1432,
      1551,   1671,   1792,   1913,   2034,   2157,   2279,   2405,   2526,   2654,
      2778,   2902,   3027,   3151,   3277,   3401,   3525,   3650,   3774,   3898,
      4021,   4143,   4266,   4389,   4509,   4628,   4748,   4866,   4983,   5098,
      5215,   5329,   5442,   5553,   5664,   5772,   5881,   5985,   6090,   6193,
      6293,   6394,   6492,   6588,   6682,   6774,   6864,   6952,   7038,   7124,
      7204,   7284,   7362,   7436,   7511,   7582,   7649,   7715,   7778,   7841,
      7898,   7955,   8010,   8060,   8109,   8156,   8198,   8238,   8278,   8312,
      8344,   8374,   8401,   8427,   8448,   8466,   8482,   8497,   8507,   8514,
      8519,   8523,   8520,   8517,   8512,   8503,   8490,   8478,   8459,   8439,
      8415,   8389,   8361,   8329,   8296,   8259,   8221,   8179,   8135,   8087,
      8037,   7985,   7930,   7873,   7814,   7752,   7687,   7620,   7550,   7479,
      7405,   7329,   7250,   7168,   7084,   7001,   6913,   6825,   6731,   6639,
      6545,   6448,   6349,   6247,   6145,   6042,   5936,   5828,   5718,   5610,
      5498,   5384,   5269,   5152,   5034,   4916,   4796,   4676,   4556,   4432,
      4308,   4184,   4059,   3935,   3806,   3678,   3549,   3421,   3293,   3162,
      3032,   2902,   2772,   2640,   2509,   2378,   2246,   2115,   1984,   1855,
      1722,   1592,   1461,   1332,   1203,   1072,    943,    817,    690,    563,
       436,    311,    187,     63,    -57,   -179,   -298,   -419,   -537,   -655,
      -769,   -884,   -997,  -1110,  -1219,  -1330,  -1435,  -1541,  -1646,  -1749,
     -1849,  -1949,  -2046,  -2141,  -2235,  -2326,  -2416,  -2505,  -2592,  -2675,
     -2758,  -2838,  -2914,  -2990,  -3064,  -3135,  -3205,  -3272,  -3335,  -3399,
     -3457,  -3516,  -3570,  -3623,  -3673,  -3723,  -3769,  -3812,  -3854,  -3892,
     -3927,  -3961,  -3992,  -4022,  -4046,  -4071,  -4092,  -4112,  -4127,  -4141,
     -4152,  -4161,  -4167,  -4170,  -4172,  -4170,  -4168,  -4161,  -4152,  -4141,
     -4127,  -4113,  -4094,  -4073,  -4051,  -4026,  -3999,  -3968,  -3936,  -3902,
     -3866,  -3827,  -3786,  -3743,  -3698,  -3651,  -3602,  -3549,  -3497,  -3442,
     -3384,  -3325,  -3265,  -3202,  -3137,  -3072,  -3005,  -2933,  -2862,  -2790,
     -2715,  -2639,  -2563,  -2483,  -2405,  -2324,  -2240,  -2156,  -2072,  -1984,
     -1897,  -1807,  -1719,  -1629,  -1538,  -1446,  -1353,  -1260,  -1165,  -1070,
      -975,   -879,   -782,   -685,   -589,   -490,   -393,   -295,   -197,    -98,
         0,     98,    197,    295,    393,    490,    589,    685,    782,    879,
       975,   1070,   1165,   1260,   1353,   1446,   1538,   1629,   1719,   1807,
      1897,   1984,   2072,   2156,   2240,   2324,   2405,   2483,   2563,   2639,
      2715,   2790,   2862,   2933,   3005,   3071,   3137,   3202,   3265,   3325,
      3384,   3442,   3497,   3549,   3602,   3651,   3698,   3743,   3786,   3827,
      3866,   3902,   3936,   3968,   3999,   4026,   4051,   4073,   4094,   4113,
      4127,   4141,   4152,   4161,   4168,   4170,   4172,   4170,   4167,   4161,
      4152,   4141,   4127,   4112,   4092,   4071,   4046,   4022,   3992,   3961,
      3927,   3892,   3854,   3812,   3769,   3723,   3673,   3623,   3570,   3516,
      3457,   3399,   3335,   3272,   3205,   3135,   3064,   2990,   2914,   2838,
      2758,   2675,   2592,   2505,   2416,   2326,   2235,   2141,   2046,   1949,
      1849,   1749,   1646,   1541,   1435,   1330,   1219,   1110,    997,    884,
       769,    655,    537,    419,    298,    179,     57,    -63,   -187,   -311,
      -436,   -563,   -690,   -817,   -943,  -1072,  -1203,  -1332,  -1461,  -1592,
     -1722,  -1855,  -1984,  -2115,  -2246,  -2378,  -2509,  -2640,  -2772,  -2902,
     -3032,  -3162,  -3293,  -3422,  -3549,  -3678,  -3806,  -3935,  -4059,  -4184,
     -4308,  -4432,  -4556,  -4676,  -4796,  -4916,  -5034,  -5152,  -5269,  -5384,
     -5498,  -5610,  -5718,  -5828,  -5936,  -6041,  -6145,  -6247,  -6349,  -6448,
     -6545,  -6639,  -6731,  -6825,  -6913,  -7001,  -7084,  -7168,  -7250,  -7329,
     -7405,  -7479,  -7550,  -7620,  -7687,  -7752,  -7814,  -7873,  -7930,  -7985,
     -8037,  -8087,  -8135,  -8179,  -8221,  -8259,  -8296,  -8329,  -8361,  -8389,
     -8415,  -8439,  -8459,  -8478,  -8490,  -8503,  -8512,  -8517,  -8520,  -8523,
     -8519,  -8514,  -8507,  -8497,  -8482,  -8466,  -8448,  -8427,  -8401,  -8374,
     -8344,  -8312,  -8278,  -8238,  -8198,  -8156,  -8109,  -8060,  -8010,  -7955,
     -7898,  -7841,  -7778,  -7715,  -7649,  -7581,  -7511,  -7436,  -7362,  -7284,
     -7204,  -7124,  -7038,  -6952,  -6864,  -6774,  -6682,  -6588,  -6492,  -6394,
     -6293,  -6193,  -6090,  -5985,  -5881,  -5772,  -5664,  -5553,  -5442,  -5329,
     -5215,  -5098,  -4983,  -4866,  -4748,  -4628,  -4509,  -4389,  -4266,  -4145,
     -4021,  -3898,  -3774,  -3650,  -3525,  -3401,  -3277,  -3151,  -3027,  -2902,
     -2778,  -2654,  -2526,  -2405,  -2279,  -2157,  -2034,  -1913,  -1792,  -1671,
     -1551,  -1432,  -1314,  -1196,  -1082,   -968,   -852,   -742,   -630,   -522,
      -414,   -308,   -204,   -101,      0,     98,    196,    290,    381,    472,
       562,    647,    731,    813,    892,    968,   1043,   1112,   1181,   1247,
      1310,   1369,   1427,   1478,   1531,   1578,   1622,   1663,   1701,   1736,
      1767,   1795,   1819,   1840,   1856,   1870,   1881,   1886,   1889,   1888,
      1883,   1873,   1861,   1844,   1824,   1798,   1771,   1740,   1701,   1660,
      1614,   1567,   1513,   1455,   1396,   1330,   1260,   1185,   1108,   1024,
       938,    847,    752,    654,    549,    440,    328,    213,     93,    -31,
      -160,   -292,   -429,   -571,   -715,   -867,  -1020,  -1178,  -1338,  -1504,
     -1674,  -1849,  -2027,  -2207,  -2394,  -2583,  -2776,  -2972,  -3173,  -3376,
     -3585,  -3795,  -4011,  -4228,  -4450,  -4675,  -4904,  -5135,  -5371,  -5609,
     -5849,  -6093,  -6341,  -6590,  -6843,  -7099,  -7358,  -7619,  -7882,  -8147,
     -8415,  -8684,  -8957,  -9232,  -9511,  -9788, -10072, -10354, -10638, -10924,
    -11213, -11502, -11793, -12086, -12378, -12673, -12969, -13264, -13565, -13862,
    -14161, -14461, -14760, -15061, -15362, -15662, -15964, -16266, -16565, -16866,
    -17167, -17467, -17768, -18066, -18364, -18661, -18958, -19253, -19547, -19842,
    -20133, -20423, -20713, -21001, -21286, -21568, -21850, -22130, -22408, -22684,
    -22957, -23228, -23496, -23760, -24024, -24281, -24540, -24792, -25042, -25291,
    -25534, -25775, -26013, -26247, -26477, -26701, -26923, -27140, -27355, -27565,
    -27771, -27972, -28168, -28360, -28548, -28731, -28909, -29082, -29250, -29414,
    -29570, -29725, -29873, -30014, -30153, -30284, -30411, -30530, -30645, -30753,
    -30857, -30956, -31046, -31132, -31212, -31286, -31352, -31413, -31470, -31519,
    -31559, -31596, -31624, -31650, -31666, -31677, -31680, -31678, -31667, -31651,
    -31629, -31599, -31564, -31520, -31471, -31414, -31349, -31282, -31205, -31121,
    -31030, -30932, -30829, -30717, -30601, -30476, -30346, -30207, -30062, -29909,
    -29751, -29585, -29416, -29236, -29050, -28858, -28661, -28455, -28242, -28025,
    -27801, -27569, -27332, -27088, -26836, -26580, -26317, -26050, -25773, -25492,
    -25204, -24912, -24611, -24306, -23997, -23679, -23357, -23030, -22696, -22357,
    -22015, -21664, -21309, -20950, -20583, -20215, -19839, -19460, -19076, -18687,
    -18293, -17896, -17492, -17086, -16675, -16261, -15843, -15418, -14993, -14563,
    -14130, -13690, -13251, -12808, -12359, -11910, -11456, -11000, -10542, -10080,
     -9617,  -9150,  -8681,  -8211,  -7740,  -7265,  -6789,  -6310,  -5831,  -5350,
     -4867,  -4384,  -3899,  -3415,  -2927,  -2439,  -1952,  -1463,   -975,   -485
};

/*
 * Waveform name: hammond_rock_8080, size: 1260 samples
 * Osc. Freq. Divider:   1.000 OR 2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 8 | 0 | 8 | 0 | 0 | 0 | 0 | 0 | 0 |
 */
const  int16  hammond_rock_8080[] =
{
         0,    267,    537,    806,   1076,   1345,   1614,   1885,   2153,   2422,
      2691,   2959,   3227,   3495,   3763,   4031,   4298,   4564,   4831,   5097,
      5364,   5629,   5893,   6159,   6422,   6686,   6948,   7212,   7474,   7735,
      7996,   8256,   8516,   8775,   9033,   9291,   9547,   9804,  10060,  10315,
     10568,  10822,  11074,  11326,  11577,  11827,  12076,  12324,  12572,  12817,
     13063,  13306,  13550,  13792,  14034,  14274,  14513,  14752,  14989,  15225,
     15460,  15694,  15927,  16158,  16388,  16616,  16845,  17072,  17297,  17521,
     17743,  17965,  18185,  18403,  18621,  18836,  19052,  19264,  19476,  19686,
     19895,  20103,  20308,  20513,  20716,  20918,  21118,  21317,  21513,  21709,
     21902,  22094,  22284,  22474,  22660,  22847,  23030,  23212,  23393,  23571,
     23748,  23924,  24097,  24269,  24439,  24608,  24773,  24940,  25101,  25263,
     25422,  25580,  25735,  25889,  26041,  26192,  26340,  26486,  26630,  26773,
     26913,  27052,  27190,  27324,  27457,  27587,  27716,  27843,  27968,  28093,
     28211,  28331,  28449,  28563,  28676,  28786,  28896,  29003,  29107,  29210,
     29311,  29410,  29506,  29600,  29694,  29783,  29872,  29958,  30043,  30124,
     30205,  30283,  30358,  30432,  30504,  30573,  30641,  30705,  30769,  30831,
     30888,  30945,  30999,  31052,  31103,  31152,  31197,  31242,  31284,  31324,
     31361,  31397,  31429,  31461,  31490,  31517,  31543,  31565,  31586,  31605,
     31621,  31635,  31648,  31659,  31667,  31673,  31677,  31680,  31680,  31676,
     31673,  31666,  31658,  31647,  31634,  31620,  31603,  31585,  31564,  31540,
     31517,  31490,  31460,  31430,  31398,  31362,  31327,  31287,  31247,  31204,
     31160,  31113,  31066,  31014,  30962,  30908,  30852,  30794,  30734,  30671,
     30609,  30544,  30476,  30407,  30336,  30263,  30189,  30112,  30034,  29954,
     29872,  29789,  29703,  29616,  29527,  29437,  29345,  29251,  29156,  29059,
     28959,  28860,  28757,  28654,  28549,  28442,  28333,  28224,  28112,  27999,
     27884,  27769,  27651,  27532,  27411,  27290,  27165,  27040,  26915,  26787,
     26657,  26527,  26395,  26263,  26128,  25993,  25856,  25718,  25578,  25437,
     25296,  25152,  25009,  24862,  24715,  24567,  24419,  24268,  24117,  23964,
     23811,  23657,  23501,  23345,  23187,  23029,  22869,  22709,  22547,  22384,
     22222,  22058,  21893,  21727,  21559,  21392,  21224,  21055,  20886,  20715,
     20544,  20372,  20199,  20026,  19851,  19678,  19502,  19326,  19150,  18972,
     18795,  18617,  18438,  18260,  18079,  17900,  17719,  17539,  17358,  17175,
     16994,  16811,  16628,  16445,  16260,  16077,  15893,  15709,  15525,  15341,
     15155,  14970,  14786,  14600,  14414,  14227,  14042,  13857,  13670,  13485,
     13298,  13113,  12928,  12741,  12556,  12370,  12184,  11999,  11814,  11628,
     11443,  11259,  11073,  10890,  10706,  10522,  10338,  10155,   9971,   9787,
      9605,   9423,   9241,   9061,   8880,   8698,   8519,   8340,   8160,   7980,
      7803,   7625,   7448,   7271,   7094,   6919,   6744,   6569,   6396,   6223,
      6050,   5878,   5706,   5536,   5367,   5198,   5030,   4861,   4695,   4529,
      4364,   4199,   4036,   3873,   3712,   3551,   3390,   3230,   3073,   2915,
      2759,   2603,   2448,   2296,   2142,   1991,   1839,   1691,   1541,   1394,
      1247,   1101,    958,    814,    672,    531,    391,    253,    115,    -20,
      -157,   -291,   -424,   -556,   -685,   -815,   -944,  -1071,  -1196,  -1321,
     -1445,  -1566,  -1687,  -1807,  -1924,  -2040,  -2157,  -2271,  -2384,  -2496,
     -2604,  -2714,  -2821,  -2928,  -3034,  -3136,  -3238,  -3339,  -3438,  -3537,
     -3633,  -3728,  -3821,  -3914,  -4005,  -4094,  -4182,  -4269,  -4354,  -4437,
     -4519,  -4599,  -4679,  -4757,  -4834,  -4909,  -4982,  -5053,  -5124,  -5195,
     -5262,  -5327,  -5391,  -5454,  -5517,  -5578,  -5635,  -5693,  -5747,  -5803,
     -5856,  -5907,  -5956,  -6005,  -6050,  -6096,  -6140,  -6182,  -6224,  -6261,
     -6300,  -6337,  -6372,  -6404,  -6437,  -6467,  -6496,  -6524,  -6550,  -6574,
     -6597,  -6618,  -6639,  -6658,  -6674,  -6690,  -6704,  -6718,  -6728,  -6739,
     -6747,  -6754,  -6761,  -6765,  -6767,  -6770,  -6769,  -6768,  -6765,  -6762,
     -6755,  -6750,  -6742,  -6731,  -6721,  -6708,  -6694,  -6681,  -6664,  -6647,
     -6628,  -6608,  -6586,  -6563,  -6539,  -6515,  -6489,  -6460,  -6431,  -6401,
     -6370,  -6337,  -6302,  -6268,  -6232,  -6195,  -6156,  -6116,  -6076,  -6033,
     -5990,  -5946,  -5901,  -5855,  -5807,  -5758,  -5709,  -5658,  -5607,  -5554,
     -5500,  -5444,  -5390,  -5332,  -5275,  -5216,  -5157,  -5096,  -5035,  -4972,
     -4910,  -4844,  -4780,  -4714,  -4648,  -4580,  -4512,  -4442,  -4372,  -4302,
     -4231,  -4158,  -4085,  -4011,  -3937,  -3862,  -3786,  -3710,  -3632,  -3554,
     -3476,  -3397,  -3317,  -3238,  -3157,  -3076,  -2994,  -2912,  -2829,  -2746,
     -2662,  -2577,  -2492,  -2407,  -2322,  -2236,  -2150,  -2063,  -1976,  -1888,
     -1800,  -1712,  -1623,  -1535,  -1446,  -1357,  -1267,  -1178,  -1089,   -997,
      -908,   -818,   -727,   -637,   -545,   -455,   -365,   -273,   -183,    -91,
         0,     91,    183,    273,    365,    455,    545,    637,    727,    818,
       908,    997,   1089,   1178,   1267,   1357,   1446,   1535,   1623,   1712,
      1800,   1888,   1976,   2063,   2150,   2236,   2322,   2407,   2492,   2577,
      2662,   2746,   2829,   2912,   2994,   3076,   3157,   3238,   3317,   3397,
      3476,   3554,   3632,   3710,   3786,   3862,   3937,   4011,   4085,   4158,
      4231,   4302,   4372,   4442,   4512,   4580,   4648,   4714,   4780,   4844,
      4910,   4972,   5035,   5096,   5157,   5216,   5275,   5332,   5390,   5444,
      5500,   5554,   5607,   5658,   5709,   5758,   5807,   5855,   5901,   5946,
      5990,   6033,   6076,   6116,   6156,   6195,   6232,   6268,   6302,   6337,
      6370,   6401,   6431,   6460,   6489,   6515,   6539,   6563,   6586,   6608,
      6628,   6647,   6664,   6681,   6694,   6708,   6721,   6731,   6742,   6750,
      6755,   6762,   6765,   6768,   6769,   6770,   6767,   6765,   6761,   6754,
      6747,   6739,   6728,   6718,   6704,   6690,   6674,   6658,   6639,   6618,
      6597,   6574,   6550,   6524,   6496,   6467,   6437,   6404,   6372,   6337,
      6300,   6261,   6224,   6182,   6140,   6096,   6050,   6005,   5956,   5907,
      5856,   5803,   5747,   5692,   5635,   5578,   5517,   5454,   5391,   5327,
      5262,   5195,   5124,   5053,   4982,   4909,   4834,   4757,   4679,   4599,
      4519,   4437,   4354,   4269,   4182,   4094,   4005,   3914,   3821,   3728,
      3633,   3537,   3438,   3339,   3238,   3136,   3034,   2928,   2821,   2714,
      2604,   2496,   2384,   2271,   2157,   2040,   1924,   1807,   1687,   1566,
      1445,   1321,   1196,   1071,    944,    815,    685,    556,    424,    291,
       157,     20,   -115,   -253,   -391,   -531,   -672,   -814,   -958,  -1101,
     -1247,  -1394,  -1541,  -1691,  -1839,  -1991,  -2142,  -2296,  -2448,  -2603,
     -2759,  -2915,  -3073,  -3230,  -3390,  -3551,  -3712,  -3873,  -4036,  -4199,
     -4364,  -4529,  -4695,  -4861,  -5030,  -5198,  -5367,  -5536,  -5706,  -5878,
     -6050,  -6223,  -6396,  -6569,  -6744,  -6919,  -7094,  -7271,  -7448,  -7625,
     -7803,  -7980,  -8160,  -8340,  -8519,  -8698,  -8880,  -9061,  -9241,  -9423,
     -9605,  -9787,  -9971, -10155, -10338, -10522, -10706, -10890, -11073, -11260,
    -11443, -11628, -11814, -11999, -12184, -12370, -12556, -12741, -12928, -13113,
    -13298, -13485, -13670, -13857, -14042, -14227, -14414, -14600, -14786, -14970,
    -15155, -15341, -15525, -15709, -15893, -16077, -16260, -16445, -16628, -16811,
    -16994, -17175, -17358, -17539, -17719, -17900, -18079, -18260, -18438, -18617,
    -18795, -18972, -19150, -19326, -19502, -19678, -19851, -20026, -20199, -20372,
    -20544, -20715, -20886, -21055, -21224, -21392, -21559, -21727, -21893, -22058,
    -22222, -22384, -22547, -22709, -22869, -23029, -23187, -23345, -23501, -23657,
    -23811, -23965, -24117, -24268, -24419, -24567, -24715, -24862, -25009, -25152,
    -25296, -25437, -25578, -25718, -25856, -25993, -26128, -26263, -26395, -26527,
    -26657, -26787, -26915, -27040, -27165, -27290, -27411, -27532, -27651, -27769,
    -27884, -27999, -28112, -28224, -28333, -28442, -28549, -28654, -28757, -28860,
    -28959, -29059, -29156, -29251, -29345, -29437, -29527, -29616, -29703, -29789,
    -29872, -29954, -30034, -30112, -30189, -30263, -30336, -30407, -30476, -30544,
    -30609, -30671, -30734, -30794, -30852, -30908, -30962, -31014, -31066, -31113,
    -31160, -31204, -31247, -31287, -31327, -31362, -31398, -31430, -31460, -31490,
    -31517, -31540, -31564, -31585, -31603, -31620, -31634, -31647, -31658, -31666,
    -31673, -31676, -31680, -31680, -31677, -31673, -31667, -31659, -31648, -31635,
    -31621, -31605, -31586, -31565, -31543, -31517, -31490, -31461, -31429, -31397,
    -31361, -31324, -31284, -31242, -31197, -31152, -31103, -31052, -30999, -30945,
    -30888, -30831, -30769, -30705, -30641, -30573, -30504, -30431, -30358, -30283,
    -30205, -30124, -30043, -29958, -29872, -29783, -29694, -29600, -29506, -29410,
    -29311, -29210, -29107, -29003, -28896, -28786, -28676, -28563, -28449, -28331,
    -28211, -28093, -27968, -27843, -27716, -27587, -27457, -27324, -27190, -27052,
    -26913, -26773, -26630, -26486, -26340, -26192, -26041, -25889, -25735, -25580,
    -25422, -25263, -25101, -24940, -24773, -24607, -24439, -24269, -24097, -23924,
    -23748, -23571, -23393, -23212, -23030, -22847, -22660, -22474, -22284, -22094,
    -21902, -21709, -21513, -21317, -21118, -20918, -20716, -20513, -20308, -20103,
    -19895, -19686, -19476, -19264, -19052, -18836, -18621, -18403, -18185, -17965,
    -17743, -17521, -17297, -17072, -16845, -16616, -16388, -16158, -15927, -15694,
    -15460, -15225, -14989, -14752, -14513, -14274, -14034, -13792, -13550, -13306,
    -13063, -12817, -12572, -12324, -12076, -11827, -11577, -11326, -11074, -10822,
    -10568, -10315, -10060,  -9804,  -9547,  -9291,  -9033,  -8775,  -8516,  -8256,
     -7996,  -7735,  -7474,  -7212,  -6948,  -6686,  -6422,  -6159,  -5893,  -5629,
     -5364,  -5097,  -4831,  -4564,  -4298,  -4031,  -3763,  -3495,  -3227,  -2959,
     -2691,  -2422,  -2153,  -1885,  -1614,  -1345,  -1076,   -806,   -537,   -267
};

/*
 * Waveform name: hammond_rock_0808, size: 1260 samples
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 0 | 8 | 0 | 8 | 0 | 0 | 0 | 0 | 0 |
 */
const  int16  hammond_rock_0808[] =
{
         0,    566,   1132,   1698,   2264,   2829,   3394,   3956,   4518,   5077,
      5637,   6194,   6748,   7301,   7851,   8399,   8944,   9486,  10024,  10560,
     11093,  11622,  12148,  12668,  13185,  13698,  14206,  14710,  15209,  15703,
     16193,  16677,  17155,  17627,  18095,  18557,  19013,  19461,  19905,  20341,
     20772,  21195,  21612,  22022,  22424,  22820,  23208,  23589,  23963,  24328,
     24685,  25036,  25377,  25712,  26036,  26353,  26663,  26963,  27254,  27537,
     27811,  28077,  28334,  28581,  28819,  29048,  29269,  29479,  29680,  29873,
     30055,  30228,  30392,  30545,  30690,  30824,  30948,  31063,  31169,  31263,
     31350,  31425,  31492,  31548,  31593,  31630,  31656,  31672,  31680,  31675,
     31662,  31640,  31607,  31565,  31512,  31450,  31379,  31297,  31206,  31105,
     30995,  30875,  30746,  30607,  30460,  30302,  30136,  29959,  29774,  29581,
     29379,  29166,  28946,  28717,  28479,  28233,  27977,  27714,  27443,  27164,
     26876,  26580,  26278,  25966,  25649,  25322,  24988,  24648,  24300,  23944,
     23582,  23214,  22839,  22458,  22070,  21676,  21276,  20869,  20457,  20040,
     19617,  19188,  18754,  18316,  17872,  17423,  16971,  16513,  16051,  15585,
     15115,  14641,  14164,  13684,  13200,  12712,  12222,  11729,  11234,  10737,
     10235,   9733,   9229,   8722,   8214,   7704,   7194,   6682,   6168,   5654,
      5140,   4626,   4110,   3594,   3080,   2564,   2050,   1536,   1024,    511,
         0,   -510,  -1019,  -1525,  -2030,  -2534,  -3036,  -3535,  -4032,  -4526,
     -5017,  -5508,  -5993,  -6476,  -6955,  -7431,  -7904,  -8372,  -8838,  -9298,
     -9755, -10208, -10656, -11099, -11538, -11972, -12400, -12825, -13243, -13656,
    -14063, -14465, -14861, -15251, -15635, -16015, -16387, -16752, -17113, -17466,
    -17812, -18153, -18486, -18813, -19132, -19444, -19750, -20048, -20338, -20621,
    -20899, -21168, -21428, -21682, -21927, -22166, -22396, -22619, -22833, -23039,
    -23239, -23430, -23612, -23786, -23953, -24111, -24261, -24402, -24536, -24662,
    -24779, -24887, -24988, -25081, -25164, -25240, -25308, -25366, -25418, -25461,
    -25494, -25522, -25539, -25549, -25550, -25544, -25530, -25508, -25477, -25437,
    -25392, -25337, -25275, -25205, -25127, -25041, -24948, -24848, -24739, -24625,
    -24501, -24371, -24233, -24089, -23937, -23778, -23612, -23439, -23260, -23074,
    -22882, -22683, -22478, -22267, -22048, -21824, -21595, -21358, -21118, -20870,
    -20617, -20360, -20096, -19827, -19553, -19275, -18990, -18702, -18409, -18111,
    -17810, -17504, -17192, -16878, -16561, -16239, -15913, -15583, -15251, -14915,
    -14576, -14234, -13890, -13542, -13193, -12840, -12485, -12127, -11769, -11408,
    -11044, -10680, -10315,  -9948,  -9580,  -9210,  -8839,  -8467,  -8096,  -7722,
     -7349,  -6976,  -6603,  -6229,  -5856,  -5482,  -5110,  -4737,  -4366,  -3994,
     -3625,  -3255,  -2887,  -2521,  -2156,  -1792,  -1430,  -1069,   -711,   -355,
         0,    352,    702,   1049,   1394,   1737,   2076,   2412,   2747,   3077,
      3405,   3728,   4049,   4367,   4682,   4991,   5298,   5600,   5898,   6194,
      6483,   6770,   7052,   7331,   7604,   7873,   8137,   8397,   8651,   8902,
      9147,   9388,   9624,   9855,  10080,  10301,  10517,  10727,  10932,  11132,
     11325,  11515,  11699,  11878,  12050,  12218,  12380,  12536,  12689,  12833,
     12973,  13108,  13236,  13358,  13476,  13589,  13694,  13796,  13890,  13980,
     14063,  14141,  14213,  14280,  14341,  14398,  14448,  14493,  14533,  14566,
     14595,  14618,  14635,  14648,  14656,  14658,  14655,  14646,  14632,  14614,
     14591,  14562,  14529,  14490,  14446,  14399,  14346,  14289,  14227,  14161,
     14091,  14016,  13936,  13852,  13764,  13673,  13577,  13476,  13373,  13265,
     13154,  13039,  12920,  12798,  12672,  12543,  12411,  12276,  12139,  11998,
     11853,  11707,  11557,  11407,  11251,  11094,  10935,  10773,  10610,  10443,
     10276,  10106,   9935,   9761,   9586,   9409,   9233,   9053,   8872,   8692,
      8509,   8325,   8142,   7957,   7771,   7584,   7398,   7211,   7024,   6836,
      6649,   6461,   6274,   6086,   5898,   5713,   5526,   5340,   5154,   4970,
      4786,   4603,   4422,   4240,   4060,   3882,   3704,   3528,   3353,   3179,
      3008,   2838,   2669,   2502,   2338,   2176,   2014,   1855,   1698,   1544,
      1391,   1241,   1094,    947,    804,    664,    525,    389,    257,    127,
         0,   -124,   -246,   -365,   -481,   -594,   -706,   -812,   -917,  -1019,
     -1118,  -1212,  -1305,  -1394,  -1479,  -1563,  -1642,  -1718,  -1792,  -1862,
     -1928,  -1992,  -2053,  -2110,  -2163,  -2214,  -2262,  -2305,  -2347,  -2385,
     -2419,  -2452,  -2479,  -2504,  -2527,  -2546,  -2562,  -2574,  -2585,  -2591,
     -2596,  -2596,  -2594,  -2590,  -2582,  -2571,  -2557,  -2541,  -2523,  -2501,
     -2476,  -2450,  -2421,  -2390,  -2355,  -2319,  -2280,  -2239,  -2195,  -2149,
     -2101,  -2052,  -2000,  -1946,  -1890,  -1834,  -1775,  -1713,  -1651,  -1586,
     -1520,  -1454,  -1385,  -1316,  -1245,  -1173,  -1100,  -1025,   -951,   -873,
      -797,   -719,   -641,   -562,   -483,   -403,   -323,   -242,   -162,    -81,
         0,     81,    162,    242,    323,    403,    483,    562,    641,    719,
       797,    873,    951,   1025,   1100,   1173,   1245,   1316,   1385,   1454,
      1520,   1586,   1651,   1713,   1775,   1834,   1890,   1946,   2000,   2052,
      2101,   2149,   2195,   2239,   2280,   2318,   2355,   2390,   2421,   2450,
      2476,   2501,   2523,   2541,   2557,   2571,   2582,   2590,   2594,   2596,
      2596,   2591,   2585,   2574,   2562,   2546,   2527,   2504,   2479,   2452,
      2419,   2385,   2347,   2305,   2262,   2214,   2163,   2110,   2053,   1992,
      1928,   1862,   1792,   1718,   1642,   1563,   1479,   1394,   1305,   1212,
      1118,   1019,    917,    812,    706,    594,    481,    365,    246,    124,
         0,   -127,   -257,   -389,   -525,   -664,   -804,   -947,  -1094,  -1241,
     -1391,  -1544,  -1698,  -1855,  -2014,  -2176,  -2338,  -2502,  -2669,  -2838,
     -3008,  -3179,  -3353,  -3528,  -3704,  -3882,  -4060,  -4240,  -4422,  -4603,
     -4786,  -4970,  -5154,  -5340,  -5526,  -5713,  -5898,  -6086,  -6274,  -6461,
     -6649,  -6836,  -7024,  -7211,  -7398,  -7584,  -7771,  -7957,  -8142,  -8325,
     -8509,  -8692,  -8872,  -9053,  -9233,  -9409,  -9586,  -9761,  -9935, -10106,
    -10276, -10443, -10610, -10773, -10935, -11094, -11251, -11407, -11557, -11707,
    -11853, -11998, -12139, -12276, -12411, -12543, -12672, -12798, -12920, -13039,
    -13154, -13265, -13373, -13476, -13577, -13672, -13764, -13852, -13936, -14016,
    -14091, -14161, -14227, -14289, -14346, -14399, -14446, -14490, -14529, -14562,
    -14591, -14614, -14632, -14646, -14655, -14658, -14656, -14648, -14635, -14618,
    -14595, -14566, -14533, -14493, -14448, -14398, -14341, -14280, -14213, -14141,
    -14063, -13980, -13890, -13796, -13694, -13589, -13476, -13358, -13236, -13108,
    -12973, -12833, -12689, -12536, -12380, -12218, -12050, -11878, -11699, -11515,
    -11325, -11132, -10932, -10727, -10517, -10301, -10080,  -9855,  -9624,  -9388,
     -9147,  -8902,  -8651,  -8397,  -8137,  -7872,  -7604,  -7331,  -7052,  -6770,
     -6483,  -6194,  -5898,  -5600,  -5298,  -4991,  -4682,  -4367,  -4049,  -3728,
     -3405,  -3077,  -2747,  -2412,  -2076,  -1737,  -1394,  -1049,   -702,   -352,
         0,    355,    711,   1069,   1430,   1792,   2156,   2521,   2887,   3255,
      3625,   3994,   4366,   4737,   5110,   5482,   5856,   6229,   6603,   6976,
      7349,   7722,   8096,   8467,   8839,   9210,   9580,   9948,  10315,  10680,
     11044,  11408,  11769,  12127,  12485,  12840,  13193,  13542,  13890,  14234,
     14576,  14915,  15251,  15583,  15913,  16239,  16561,  16878,  17192,  17504,
     17810,  18111,  18409,  18702,  18990,  19275,  19553,  19827,  20096,  20360,
     20617,  20870,  21118,  21358,  21595,  21824,  22048,  22267,  22478,  22683,
     22882,  23074,  23260,  23439,  23612,  23778,  23937,  24089,  24233,  24371,
     24501,  24625,  24739,  24848,  24948,  25041,  25127,  25205,  25275,  25337,
     25392,  25437,  25477,  25508,  25530,  25544,  25550,  25549,  25539,  25522,
     25494,  25461,  25418,  25366,  25308,  25240,  25164,  25081,  24988,  24887,
     24779,  24662,  24536,  24402,  24261,  24110,  23953,  23786,  23612,  23430,
     23239,  23039,  22833,  22619,  22396,  22166,  21927,  21682,  21428,  21168,
     20899,  20621,  20338,  20048,  19750,  19444,  19132,  18813,  18486,  18153,
     17812,  17466,  17113,  16752,  16387,  16015,  15635,  15251,  14861,  14465,
     14063,  13656,  13243,  12825,  12400,  11972,  11538,  11099,  10656,  10208,
      9755,   9298,   8838,   8372,   7904,   7431,   6955,   6476,   5993,   5508,
      5017,   4526,   4032,   3535,   3036,   2534,   2030,   1525,   1019,    510,
         0,   -511,  -1024,  -1536,  -2050,  -2565,  -3080,  -3594,  -4110,  -4626,
     -5140,  -5654,  -6168,  -6682,  -7194,  -7704,  -8214,  -8722,  -9229,  -9733,
    -10235, -10737, -11234, -11729, -12222, -12712, -13200, -13684, -14164, -14641,
    -15115, -15585, -16051, -16513, -16971, -17423, -17872, -18316, -18754, -19188,
    -19617, -20040, -20457, -20869, -21276, -21676, -22070, -22458, -22839, -23214,
    -23582, -23944, -24300, -24648, -24988, -25322, -25649, -25966, -26278, -26580,
    -26876, -27164, -27443, -27714, -27977, -28233, -28479, -28717, -28946, -29166,
    -29379, -29581, -29774, -29959, -30136, -30302, -30460, -30607, -30746, -30875,
    -30995, -31105, -31206, -31297, -31379, -31450, -31512, -31565, -31607, -31640,
    -31662, -31675, -31680, -31672, -31656, -31630, -31593, -31548, -31492, -31425,
    -31350, -31263, -31169, -31063, -30948, -30824, -30690, -30545, -30392, -30228,
    -30055, -29873, -29680, -29479, -29269, -29048, -28819, -28581, -28334, -28077,
    -27811, -27537, -27254, -26963, -26663, -26353, -26036, -25712, -25377, -25036,
    -24685, -24328, -23963, -23589, -23208, -22820, -22424, -22022, -21612, -21195,
    -20772, -20341, -19905, -19461, -19013, -18556, -18095, -17627, -17155, -16677,
    -16193, -15703, -15209, -14710, -14206, -13698, -13185, -12668, -12148, -11622,
    -11093, -10560, -10024,  -9486,  -8944,  -8399,  -7851,  -7301,  -6748,  -6194,
     -5637,  -5077,  -4518,  -3956,  -3394,  -2829,  -2264,  -1698,  -1132,   -566
};

/*
 * Waveform name: pink_floyd_organ_850005, size: 1260 samples
 * Osc. Freq. Divider:   1.000 OR 2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 8 | 5 | 0 | 0 | 0 | 5 | 0 | 0 | 0 |
 */
const  int16  pink_floyd_organ_850005[] =
{
         0,    584,   1171,   1755,   2339,   2921,   3498,   4073,   4645,   5212,
      5775,   6329,   6879,   7424,   7961,   8491,   9012,   9524,  10029,  10523,
     11010,  11483,  11946,  12400,  12842,  13271,  13690,  14096,  14489,  14869,
     15237,  15592,  15931,  16258,  16573,  16873,  17156,  17425,  17683,  17925,
     18150,  18364,  18562,  18746,  18917,  19069,  19211,  19337,  19450,  19547,
     19634,  19703,  19762,  19809,  19839,  19858,  19866,  19861,  19843,  19817,
     19779,  19728,  19668,  19599,  19520,  19432,  19335,  19230,  19118,  18999,
     18871,  18739,  18601,  18457,  18306,  18153,  17999,  17838,  17674,  17511,
     17345,  17178,  17009,  16841,  16671,  16504,  16339,  16173,  16013,  15853,
     15699,  15545,  15399,  15257,  15117,  14986,  14860,  14741,  14629,  14523,
     14425,  14334,  14254,  14181,  14117,  14064,  14017,  13981,  13954,  13938,
     13932,  13938,  13954,  13980,  14017,  14065,  14126,  14195,  14277,  14371,
     14474,  14589,  14715,  14850,  15001,  15158,  15328,  15506,  15697,  15897,
     16106,  16325,  16555,  16792,  17039,  17294,  17558,  17829,  18108,  18394,
     18687,  18986,  19289,  19601,  19917,  20237,  20563,  20890,  21221,  21555,
     21893,  22231,  22568,  22909,  23250,  23589,  23930,  24268,  24603,  24938,
     25269,  25598,  25922,  26241,  26555,  26866,  27170,  27467,  27758,  28041,
     28318,  28586,  28845,  29094,  29336,  29566,  29786,  29997,  30196,  30382,
     30559,  30724,  30875,  31016,  31142,  31258,  31358,  31446,  31518,  31578,
     31626,  31656,  31677,  31680,  31670,  31644,  31606,  31552,  31484,  31404,
     31309,  31201,  31075,  30939,  30786,  30623,  30447,  30257,  30053,  29838,
     29611,  29373,  29122,  28860,  28586,  28300,  28009,  27703,  27390,  27067,
     26737,  26400,  26052,  25700,  25338,  24974,  24602,  24224,  23842,  23458,
     23068,  22677,  22282,  21887,  21488,  21091,  20694,  20296,  19899,  19504,
     19111,  18718,  18331,  17948,  17568,  17191,  16822,  16459,  16099,  15749,
     15406,  15071,  14741,  14423,  14111,  13813,  13522,  13240,  12970,  12713,
     12465,  12230,  12007,  11796,  11598,  11412,  11238,  11079,  10933,  10800,
     10683,  10577,  10487,  10412,  10347,  10300,  10265,  10246,  10241,  10249,
     10271,  10309,  10358,  10424,  10501,  10594,  10696,  10815,  10947,  11089,
     11244,  11412,  11591,  11780,  11982,  12195,  12418,  12652,  12892,  13144,
     13404,  13671,  13947,  14230,  14521,  14819,  15120,  15428,  15741,  16057,
     16379,  16701,  17028,  17357,  17688,  18020,  18353,  18685,  19019,  19350,
     19681,  20008,  20336,  20657,  20977,  21293,  21602,  21909,  22209,  22504,
     22793,  23075,  23348,  23617,  23874,  24124,  24365,  24596,  24821,  25033,
     25235,  25428,  25611,  25781,  25941,  26090,  26226,  26352,  26464,  26566,
     26654,  26732,  26796,  26848,  26888,  26914,  26930,  26933,  26924,  26900,
     26867,  26820,  26762,  26692,  26610,  26519,  26416,  26301,  26175,  26040,
     25893,  25739,  25572,  25398,  25216,  25026,  24825,  24619,  24403,  24184,
     23956,  23722,  23482,  23240,  22990,  22738,  22481,  22222,  21958,  21694,
     21430,  21162,  20895,  20628,  20362,  20095,  19829,  19568,  19307,  19049,
     18794,  18544,  18297,  18056,  17821,  17591,  17365,  17150,  16938,  16737,
     16541,  16354,  16177,  16009,  15850,  15699,  15560,  15432,  15313,  15205,
     15106,  15020,  14946,  14884,  14834,  14794,  14767,  14754,  14752,  14764,
     14787,  14822,  14869,  14930,  15004,  15088,  15187,  15296,  15419,  15551,
     15699,  15853,  16021,  16201,  16392,  16593,  16803,  17024,  17254,  17495,
     17743,  18000,  18267,  18540,  18821,  19111,  19405,  19705,  20011,  20325,
     20639,  20959,  21284,  21609,  21940,  22272,  22604,  22938,  23273,  23607,
     23941,  24273,  24603,  24933,  25258,  25580,  25899,  26211,  26520,  26825,
     27122,  27412,  27695,  27972,  28241,  28498,  28750,  28990,  29219,  29442,
     29652,  29850,  30038,  30211,  30374,  30523,  30660,  30783,  30894,  30990,
     31072,  31142,  31194,  31231,  31255,  31264,  31258,  31233,  31198,  31145,
     31076,  30994,  30891,  30778,  30648,  30501,  30340,  30165,  29973,  29767,
     29545,  29310,  29061,  28799,  28522,  28232,  27926,  27609,  27279,  26936,
     26583,  26218,  25841,  25454,  25056,  24648,  24231,  23807,  23372,  22928,
     22480,  22021,  21559,  21087,  20613,  20132,  19647,  19160,  18668,  18174,
     17677,  17179,  16678,  16180,  15679,  15177,  14679,  14183,  13687,  13193,
     12704,  12218,  11735,  11257,  10785,  10319,   9858,   9403,   8955,   8515,
      8084,   7659,   7242,   6835,   6438,   6048,   5671,   5304,   4944,   4597,
      4262,   3935,   3621,   3317,   3026,   2746,   2480,   2224,   1979,   1749,
      1528,   1323,   1127,    942,    773,    614,    467,    331,    206,     95,
        -6,    -95,   -175,   -242,   -301,   -348,   -387,   -415,   -436,   -446,
      -446,   -441,   -426,   -406,   -376,   -342,   -299,   -254,   -202,   -145,
       -82,    -16,     50,    121,    195,    272,    348,    426,    506,    584,
       664,    744,    819,    893,    963,   1030,   1095,   1156,   1212,   1261,
      1306,   1349,   1381,   1409,   1427,   1439,   1443,   1440,   1427,   1406,
      1372,   1332,   1283,   1220,   1149,   1067,    974,    868,    755,    626,
       487,    335,    173,     -1,   -190,   -389,   -600,   -823,  -1060,  -1310,
     -1567,  -1843,  -2126,  -2423,  -2732,  -3049,  -3382,  -3724,  -4078,  -4441,
     -4816,  -5199,  -5594,  -5999,  -6411,  -6832,  -7265,  -7703,  -8149,  -8604,
     -9065,  -9532, -10005, -10486, -10970, -11460, -11952, -12449, -12950, -13453,
    -13958, -14464, -14973, -15481, -15987, -16495, -17002, -17506, -18007, -18508,
    -19003, -19497, -19985, -20468, -20946, -21418, -21884, -22341, -22794, -23236,
    -23671, -24095, -24513, -24919, -25313, -25699, -26072, -26435, -26787, -27125,
    -27450, -27762, -28063, -28349, -28622, -28881, -29124, -29354, -29567, -29767,
    -29951, -30122, -30277, -30417, -30538, -30648, -30741, -30818, -30879, -30927,
    -30957, -30972, -30972, -30956, -30928, -30883, -30824, -30750, -30663, -30562,
    -30445, -30317, -30176, -30021, -29856, -29676, -29488, -29285, -29073, -28850,
    -28617, -28375, -28122, -27862, -27595, -27319, -27037, -26747, -26450, -26149,
    -25844, -25533, -25217, -24900, -24578, -24254, -23930, -23603, -23274, -22947,
    -22620, -22295, -21971, -21646, -21326, -21009, -20695, -20385, -20080, -19780,
    -19484, -19197, -18914, -18638, -18371, -18109, -17856, -17614, -17380, -17153,
    -16938, -16733, -16536, -16351, -16176, -16013, -15861, -15720, -15590, -15473,
    -15369, -15273, -15194, -15124, -15068, -15021, -14991, -14969, -14962, -14968,
    -14986, -15016, -15056, -15110, -15173, -15251, -15340, -15439, -15548, -15670,
    -15801, -15945, -16097, -16258, -16428, -16606, -16796, -16990, -17194, -17405,
    -17624, -17849, -18079, -18317, -18557, -18806, -19056, -19311, -19568, -19831,
    -20092, -20357, -20624, -20891, -21155, -21423, -21690, -21954, -22218, -22480,
    -22738, -22993, -23244, -23493, -23736, -23972, -24205, -24432, -24650, -24863,
    -25068, -25267, -25454, -25636, -25806, -25971, -26123, -26265, -26398, -26523,
    -26633, -26735, -26825, -26903, -26970, -27025, -27067, -27099, -27118, -27123,
    -27119, -27099, -27070, -27026, -26970, -26902, -26821, -26729, -26624, -26506,
    -26376, -26237, -26083, -25921, -25745, -25559, -25361, -25154, -24938, -24710,
    -24473, -24228, -23974, -23710, -23439, -23160, -22874, -22582, -22281, -21977,
    -21665, -21349, -21029, -20705, -20378, -20048, -19714, -19379, -19044, -18706,
    -18369, -18030, -17693, -17357, -17023, -16692, -16362, -16037, -15716, -15399,
    -15087, -14779, -14478, -14183, -13895, -13615, -13341, -13076, -12820, -12574,
    -12337, -12110, -11892, -11687, -11491, -11308, -11136, -10975, -10829, -10694,
    -10570, -10462, -10367, -10284, -10216, -10163, -10120, -10094, -10081, -10083,
    -10098, -10130, -10174, -10234, -10305, -10393, -10494, -10610, -10739, -10881,
    -11038, -11207, -11390, -11586, -11792, -12014, -12248, -12491, -12747, -13014,
    -13292, -13581, -13877, -14185, -14503, -14830, -15162, -15506, -15853, -16212,
    -16573, -16941, -17314, -17695, -18077, -18464, -18854, -19246, -19639, -20036,
    -20434, -20829, -21228, -21624, -22020, -22414, -22805, -23195, -23581, -23963,
    -24339, -24712, -25078, -25439, -25793, -26141, -26479, -26813, -27134, -27450,
    -27754, -28048, -28336, -28611, -28876, -29126, -29370, -29600, -29817, -30023,
    -30213, -30392, -30559, -30714, -30853, -30979, -31090, -31191, -31273, -31347,
    -31402, -31444, -31472, -31485, -31487, -31472, -31444, -31402, -31347, -31276,
    -31195, -31098, -30987, -30865, -30731, -30585, -30423, -30254, -30070, -29878,
    -29672, -29456, -29232, -28996, -28751, -28500, -28238, -27966, -27690, -27407,
    -27114, -26817, -26513, -26204, -25892, -25574, -25253, -24929, -24602, -24272,
    -23941, -23608, -23274, -22942, -22610, -22277, -21947, -21616, -21291, -20968,
    -20647, -20330, -20017, -19710, -19408, -19110, -18820, -18534, -18254, -17986,
    -17722, -17468, -17221, -16982, -16753, -16532, -16321, -16119, -15928, -15745,
    -15575, -15417, -15266, -15125, -14998, -14880, -14775, -14678, -14596, -14522,
    -14462, -14411, -14370, -14341, -14325, -14317, -14321, -14336, -14360, -14395,
    -14438, -14492, -14556, -14631, -14712, -14802, -14901, -15008, -15121, -15242,
    -15370, -15504, -15645, -15792, -15942, -16098, -16258, -16424, -16591, -16760,
    -16934, -17108, -17284, -17459, -17637, -17812, -17989, -18164, -18335, -18506,
    -18673, -18837, -18997, -19156, -19307, -19452, -19593, -19728, -19855, -19974,
    -20086, -20190, -20285, -20371, -20448, -20515, -20571, -20616, -20649, -20673,
    -20686, -20684, -20669, -20645, -20606, -20553, -20489, -20411, -20316, -20210,
    -20091, -19954, -19806, -19640, -19463, -19267, -19063, -18839, -18602, -18352,
    -18083, -17806, -17510, -17200, -16878, -16541, -16193, -15827, -15451, -15061,
    -14657, -14243, -13816, -13378, -12928, -12468, -11995, -11513, -11019, -10518,
    -10009,  -9488,  -8961,  -8426,  -7885,  -7336,  -6782,  -6219,  -5654,  -5084,
     -4512,  -3935,  -3353,  -2770,  -2186,  -1600,  -1013,   -426,    158,    744
};

/*
 * Waveform name: bauer_organ_008008432, size: 1260 samples
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 0 | 0 | 8 | 0 | 0 | 8 | 4 | 3 | 2 |
 */
const  int16  bauer_organ_008008432[] =
{
         0,   1158,   2319,   3474,   4624,   5764,   6894,   8010,   9111,  10193,
     11259,  12300,  13318,  14313,  15281,  16218,  17127,  18005,  18849,  19658,
     20431,  21170,  21870,  22528,  23152,  23732,  24273,  24769,  25226,  25641,
     26014,  26345,  26633,  26877,  27081,  27242,  27364,  27443,  27481,  27483,
     27442,  27364,  27249,  27099,  26913,  26692,  26437,  26151,  25833,  25489,
     25114,  24712,  24286,  23837,  23365,  22871,  22355,  21824,  21273,  20707,
     20127,  19536,  18932,  18319,  17697,  17066,  16433,  15793,  15149,  14503,
     13857,  13212,  12569,  11929,  11291,  10659,  10032,   9412,   8799,   8198,
      7605,   7023,   6453,   5894,   5349,   4819,   4302,   3802,   3317,   2849,
      2399,   1967,   1553,   1158,    781,    428,     95,   -219,   -508,   -779,
     -1028,  -1252,  -1454,  -1630,  -1784,  -1914,  -2021,  -2103,  -2159,  -2191,
     -2197,  -2180,  -2136,  -2067,  -1972,  -1852,  -1708,  -1535,  -1341,  -1121,
      -877,   -605,   -311,      6,    345,    710,   1098,   1506,   1940,   2391,
      2865,   3356,   3871,   4402,   4950,   5514,   6098,   6693,   7304,   7927,
      8564,   9212,   9869,  10534,  11210,  11888,  12572,  13262,  13956,  14649,
     15345,  16038,  16729,  17417,  18102,  18779,  19450,  20112,  20765,  21409,
     22040,  22657,  23263,  23854,  24425,  24982,  25520,  26040,  26540,  27020,
     27478,  27915,  28327,  28719,  29086,  29428,  29747,  30040,  30308,  30552,
     30767,  30960,  31125,  31264,  31375,  31463,  31524,  31562,  31571,  31557,
     31517,  31454,  31367,  31256,  31121,  30961,  30781,  30580,  30357,  30112,
     29849,  29565,  29261,  28941,  28601,  28243,  27871,  27481,  27076,  26656,
     26222,  25773,  25312,  24837,  24352,  23855,  23346,  22828,  22297,  21759,
     21210,  20653,  20088,  19515,  18935,  18345,  17751,  17149,  16544,  15932,
     15315,  14693,  14067,  13437,  12802,  12164,  11526,  10886,  10241,   9596,
      8951,   8305,   7658,   7013,   6369,   5724,   5085,   4449,   3815,   3187,
      2560,   1942,   1330,    725,    127,   -461,  -1040,  -1611,  -2166,  -2711,
     -3245,  -3764,  -4268,  -4756,  -5228,  -5684,  -6121,  -6541,  -6940,  -7319,
     -7675,  -8012,  -8325,  -8614,  -8878,  -9120,  -9336,  -9526,  -9690,  -9828,
     -9940, -10022, -10079, -10106, -10108, -10081, -10028,  -9946,  -9837,  -9698,
     -9537,  -9347,  -9133,  -8891,  -8627,  -8338,  -8024,  -7690,  -7333,  -6955,
     -6560,  -6144,  -5712,  -5265,  -4802,  -4324,  -3835,  -3333,  -2825,  -2308,
     -1785,  -1256,   -724,   -188,    344,    880,   1413,   1940,   2465,   2982,
      3490,   3986,   4473,   4948,   5412,   5858,   6290,   6703,   7098,   7475,
      7831,   8165,   8477,   8768,   9035,   9277,   9495,   9687,   9855,   9994,
     10110,  10197,  10261,  10295,  10305,  10285,  10240,  10169,  10073,   9948,
      9801,   9628,   9429,   9207,   8959,   8690,   8398,   8084,   7749,   7393,
      7017,   6623,   6208,   5778,   5329,   4863,   4385,   3891,   3382,   2862,
      2328,   1782,   1224,    658,     82,   -503,  -1099,  -1700,  -2307,  -2922,
     -3541,  -4168,  -4797,  -5431,  -6068,  -6705,  -7348,  -7993,  -8637,  -9283,
     -9930, -10578, -11224, -11864, -12507, -13150, -13789, -14424, -15057, -15686,
    -16311, -16930, -17546, -18153, -18756, -19353, -19943, -20523, -21097, -21661,
    -22216, -22762, -23294, -23819, -24329, -24827, -25313, -25785, -26243, -26685,
    -27114, -27525, -27919, -28295, -28654, -28993, -29313, -29613, -29891, -30149,
    -30383, -30595, -30789, -30954, -31097, -31218, -31313, -31384, -31427, -31445,
    -31437, -31404, -31345, -31262, -31149, -31012, -30849, -30662, -30447, -30207,
    -29941, -29653, -29336, -28999, -28638, -28253, -27846, -27419, -26970, -26502,
    -26014, -25509, -24984, -24443, -23887, -23319, -22734, -22138, -21529, -20911,
    -20284, -19649, -19008, -18358, -17704, -17046, -16387, -15727, -15067, -14408,
    -13751, -13094, -12444, -11800, -11161, -10528,  -9909,  -9294,  -8690,  -8098,
     -7517,  -6950,  -6395,  -5855,  -5333,  -4823,  -4333,  -3856,  -3399,  -2958,
     -2538,  -2136,  -1756,  -1391,  -1051,   -730,   -431,   -153,    105,    340,
       556,    747,    915,   1061,   1186,   1287,   1367,   1424,   1458,   1468,
      1456,   1422,   1364,   1287,   1183,   1058,    913,    743,    554,    341,
       108,   -147,   -426,   -722,  -1039,  -1376,  -1734,  -2112,  -2509,  -2926,
     -3359,  -3811,  -4280,  -4766,  -5268,  -5786,  -6320,  -6869,  -7431,  -8003,
     -8586,  -9183,  -9790, -10407, -11031, -11662, -12299, -12942, -13587, -14235,
    -14883, -15534, -16183, -16827, -17470, -18106, -18736, -19354, -19965, -20565,
    -21149, -21721, -22276, -22815, -23332, -23829, -24304, -24754, -25178, -25577,
    -25948, -26290, -26599, -26877, -27120, -27330, -27502, -27637, -27735, -27794,
    -27812, -27793, -27730, -27624, -27478, -27286, -27054, -26776, -26458, -26096,
    -25689, -25239, -24749, -24215, -23641, -23024, -22369, -21671, -20938, -20167,
    -19360, -18519, -17644, -16736, -15801, -14834, -13843, -12827, -11786, -10724,
     -9644,  -8545,  -7434,  -6307,  -5171,  -4025,  -2873,  -1716,   -561,    595,
      1748,   2896,   4041,   5175,   6299,   7408,   8504,   9583,  10643,  11679,
     12694,  13684,  14649,  15584,  16491,  17366,  18210,  19019,  19796,  20536,
     21239,  21904,  22532,  23119,  23671,  24179,  24648,  25074,  25461,  25807,
     26114,  26378,  26601,  26784,  26929,  27032,  27096,  27124,  27112,  27062,
     26975,  26854,  26698,  26509,  26287,  26034,  25747,  25433,  25090,  24721,
     24324,  23903,  23461,  22996,  22509,  22003,  21477,  20935,  20376,  19802,
     19217,  18621,  18011,  17393,  16769,  16134,  15496,  14853,  14205,  13556,
     12906,  12258,  11610,  10963,  10321,   9683,   9050,   8428,   7809,   7199,
      6598,   6010,   5434,   4869,   4316,   3779,   3256,   2750,   2260,   1788,
      1335,    899,    483,     89,   -284,   -637,   -964,  -1271,  -1553,  -1812,
     -2048,  -2256,  -2438,  -2594,  -2724,  -2828,  -2907,  -2955,  -2976,  -2970,
     -2935,  -2871,  -2779,  -2660,  -2512,  -2335,  -2134,  -1900,  -1644,  -1358,
     -1044,   -704,   -338,     53,    468,    908,   1372,   1858,   2368,   2898,
      3450,   4019,   4610,   5216,   5841,   6477,   7131,   7795,   8473,   9162,
      9860,  10565,  11279,  11995,  12717,  13441,  14167,  14892,  15618,  16338,
     17056,  17766,  18472,  19170,  19857,  20533,  21199,  21853,  22492,  23118,
     23725,  24314,  24887,  25442,  25975,  26489,  26979,  27448,  27895,  28320,
     28718,  29094,  29445,  29769,  30070,  30344,  30594,  30817,  31014,  31187,
     31331,  31454,  31548,  31617,  31659,  31679,  31674,  31648,  31593,  31517,
     31419,  31298,  31155,  30991,  30806,  30596,  30368,  30125,  29860,  29576,
     29278,  28960,  28624,  28274,  27909,  27526,  27129,  26721,  26298,  25861,
     25412,  24948,  24476,  23990,  23494,  22989,  22472,  21947,  21409,  20865,
     20310,  19747,  19177,  18598,  18013,  17417,  16817,  16210,  15598,  14978,
     14353,  13725,  13089,  12451,  11812,  11166,  10516,   9865,   9213,   8559,
      7905,   7250,   6596,   5941,   5289,   4640,   3995,   3354,   2717,   2086,
      1460,    843,    233,   -364,   -955,  -1537,  -2103,  -2658,  -3196,  -3722,
     -4232,  -4726,  -5201,  -5659,  -6096,  -6514,  -6912,  -7286,  -7637,  -7966,
     -8271,  -8550,  -8805,  -9035,  -9235,  -9411,  -9559,  -9678,  -9771,  -9835,
     -9872,  -9877,  -9856,  -9805,  -9729,  -9623,  -9491,  -9329,  -9143,  -8929,
     -8690,  -8426,  -8139,  -7827,  -7494,  -7139,  -6763,  -6367,  -5954,  -5523,
     -5076,  -4616,  -4141,  -3655,  -3158,  -2650,  -2139,  -1617,  -1093,   -563,
       -35,    494,   1024,   1552,   2074,   2593,   3106,   3607,   4102,   4584,
      5055,   5510,   5953,   6380,   6791,   7183,   7559,   7912,   8246,   8559,
      8850,   9118,   9363,   9585,   9782,   9956,  10104,  10225,  10326,  10396,
     10443,  10463,  10462,  10432,  10379,  10299,  10196,  10067,   9915,   9739,
      9540,   9318,   9072,   8805,   8518,   8209,   7880,   7533,   7166,   6779,
      6375,   5957,   5518,   5066,   4599,   4116,   3621,   3112,   2590,   2057,
      1511,    954,    389,   -186,   -771,  -1364,  -1968,  -2578,  -3191,  -3812,
     -4440,  -5075,  -5712,  -6353,  -6999,  -7647,  -8299,  -8952,  -9607, -10266,
    -10921, -11576, -12233, -12888, -13543, -14196, -14846, -15492, -16135, -16774,
    -17409, -18035, -18659, -19274, -19881, -20482, -21074, -21656, -22227, -22788,
    -23337, -23875, -24398, -24909, -25403, -25883, -26346, -26794, -27225, -27637,
    -28033, -28406, -28761, -29094, -29404, -29693, -29963, -30206, -30426, -30623,
    -30797, -30941, -31066, -31162, -31230, -31278, -31298, -31292, -31256, -31195,
    -31109, -30996, -30857, -30695, -30502, -30288, -30047, -29784, -29496, -29183,
    -28846, -28490, -28110, -27711, -27290, -26851, -26392, -25915, -25424, -24916,
    -24391, -23854, -23303, -22741, -22167, -21584, -20991, -20392, -19783, -19170,
    -18555, -17933, -17310, -16683, -16057, -15431, -14808, -14187, -13570, -12955,
    -12347, -11745, -11151, -10562,  -9982,  -9414,  -8855,  -8305,  -7768,  -7244,
     -6730,  -6230,  -5744,  -5272,  -4818,  -4374,  -3951,  -3541,  -3148,  -2770,
     -2413,  -2070,  -1747,  -1440,  -1155,   -886,   -636,   -409,   -196,     -5,
       168,    321,    452,    563,    656,    727,    779,    810,    818,    807,
       775,    723,    648,    553,    437,    297,    139,    -42,   -242,   -464,
      -709,   -975,  -1261,  -1567,  -1895,  -2239,  -2607,  -2996,  -3402,  -3829,
     -4274,  -4737,  -5218,  -5714,  -6230,  -6760,  -7308,  -7868,  -8440,  -9026,
     -9625, -10236, -10856, -11486, -12122, -12766, -13414, -14067, -14723, -15380,
    -16035, -16690, -17343, -17992, -18634, -19266, -19894, -20506, -21108, -21697,
    -22265, -22820, -23355, -23870, -24361, -24829, -25271, -25687, -26071, -26427,
    -26752, -27044, -27302, -27524, -27710, -27859, -27969, -28039, -28067, -28055,
    -28002, -27906, -27768, -27586, -27360, -27089, -26777, -26419, -26020, -25577,
    -25091, -24562, -23991, -23382, -22732, -22042, -21314, -20547, -19749, -18914,
    -18046, -17148, -16220, -15261, -14279, -13272, -12243, -11192, -10123,  -9037,
     -7939,  -6823,  -5702,  -4569,  -3430,  -2287,  -1144,     -1,   1139,   2275
};

/*
 * Waveform name: mellow_reed_008042660, size: 1260 samples
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 0 | 0 | 8 | 0 | 4 | 2 | 6 | 6 | 0 |
 */
const  int16  mellow_reed_008042660[] =
{
         0,   1457,   2917,   4369,   5809,   7238,   8646,  10033,  11396,  12731,
     14034,  15304,  16535,  17729,  18879,  19981,  21036,  22041,  22992,  23892,
     24732,  25514,  26237,  26898,  27497,  28034,  28505,  28910,  29252,  29527,
     29740,  29885,  29967,  29984,  29937,  29826,  29657,  29426,  29139,  28792,
     28390,  27938,  27432,  26879,  26282,  25636,  24953,  24231,  23472,  22682,
     21862,  21016,  20146,  19260,  18356,  17436,  16508,  15574,  14635,  13695,
     12761,  11832,  10916,  10010,   9121,   8251,   7402,   6581,   5786,   5021,
      4290,   3594,   2935,   2316,   1741,   1208,    720,    279,   -111,   -452,
      -743,   -983,  -1173,  -1306,  -1388,  -1417,  -1392,  -1316,  -1185,  -1001,
      -768,   -480,   -149,    234,    664,   1141,   1660,   2221,   2824,   3464,
      4140,   4851,   5593,   6366,   7163,   7985,   8828,   9689,  10568,  11458,
     12362,  13268,  14181,  15098,  16012,  16921,  17825,  18719,  19603,  20468,
     21317,  22147,  22956,  23739,  24493,  25220,  25914,  26575,  27203,  27794,
     28345,  28858,  29330,  29759,  30147,  30489,  30787,  31039,  31247,  31408,
     31525,  31594,  31618,  31597,  31531,  31423,  31269,  31070,  30832,  30555,
     30239,  29883,  29491,  29066,  28609,  28120,  27601,  27055,  26485,  25894,
     25279,  24647,  23998,  23334,  22661,  21977,  21285,  20590,  19893,  19195,
     18501,  17809,  17125,  16450,  15785,  15137,  14499,  13881,  13280,  12702,
     12145,  11615,  11104,  10626,  10172,   9748,   9356,   8992,   8662,   8367,
      8103,   7872,   7675,   7513,   7384,   7290,   7228,   7202,   7208,   7247,
      7317,   7420,   7554,   7712,   7904,   8123,   8367,   8636,   8926,   9243,
      9575,   9925,  10299,  10682,  11081,  11497,  11918,  12349,  12784,  13228,
     13675,  14120,  14566,  15008,  15452,  15883,  16312,  16728,  17136,  17531,
     17913,  18279,  18630,  18960,  19276,  19568,  19842,  20092,  20319,  20523,
     20703,  20859,  20987,  21089,  21167,  21218,  21242,  21239,  21213,  21157,
     21078,  20971,  20837,  20681,  20501,  20296,  20067,  19821,  19550,  19258,
     18950,  18621,  18275,  17915,  17540,  17148,  16746,  16330,  15905,  15471,
     15027,  14582,  14126,  13668,  13206,  12742,  12279,  11817,  11355,  10895,
     10440,   9989,   9543,   9103,   8671,   8249,   7830,   7422,   7026,   6638,
      6262,   5894,   5538,   5197,   4862,   4541,   4232,   3931,   3645,   3369,
      3103,   2848,   2602,   2365,   2137,   1918,   1708,   1505,   1306,   1114,
       925,    743,    565,    386,    210,     36,   -136,   -312,   -491,   -670,
      -853,  -1043,  -1235,  -1434,  -1639,  -1851,  -2071,  -2299,  -2537,  -2786,
     -3043,  -3310,  -3588,  -3875,  -4179,  -4490,  -4813,  -5149,  -5494,  -5853,
     -6222,  -6601,  -6991,  -7391,  -7802,  -8221,  -8646,  -9082,  -9526,  -9974,
    -10427, -10887, -11348, -11814, -12279, -12744, -13211, -13676, -14138, -14595,
    -15044, -15491, -15927, -16356, -16774, -17178, -17573, -17951, -18314, -18662,
    -18993, -19304, -19597, -19871, -20120, -20351, -20557, -20739, -20897, -21033,
    -21141, -21222, -21278, -21307, -21311, -21287, -21238, -21161, -21059, -20931,
    -20776, -20596, -20393, -20164, -19914, -19642, -19349, -19033, -18702, -18352,
    -17985, -17602, -17205, -16797, -16379, -15948, -15517, -15072, -14628, -14181,
    -13733, -13284, -12839, -12402, -11968, -11544, -11128, -10725, -10339,  -9964,
     -9611,  -9276,  -8956,  -8665,  -8393,  -8145,  -7924,  -7730,  -7567,  -7431,
     -7326,  -7251,  -7209,  -7202,  -7225,  -7283,  -7373,  -7500,  -7660,  -7855,
     -8081,  -8342,  -8635,  -8964,  -9324,  -9713, -10134, -10585, -11063, -11570,
    -12098, -12653, -13229, -13828, -14443, -15079, -15726, -16389, -17063, -17745,
    -18435, -19129, -19825, -20521, -21215, -21907, -22590, -23262, -23925, -24574,
    -25205, -25821, -26413, -26981, -27528, -28047, -28535, -28994, -29420, -29813,
    -30169, -30486, -30764, -31003, -31202, -31358, -31469, -31537, -31558, -31537,
    -31469, -31355, -31197, -30990, -30740, -30444, -30105, -29719, -29292, -28824,
    -28313, -27765, -27176, -26550, -25893, -25202, -24479, -23726, -22946, -22140,
    -21314, -20468, -19604, -18723, -17834, -16933, -16025, -15115, -14201, -13290,
    -12387, -11486, -10598,  -9722,  -8864,  -8024,  -7203,  -6409,  -5639,  -4898,
     -4190,  -3517,  -2878,  -2277,  -1718,  -1202,   -726,   -298,     85,    415,
       700,    932,   1115,   1245,   1320,   1345,   1316,   1232,   1099,    909,
       671,    380,     37,   -353,   -794,  -1280,  -1813,  -2388,  -3005,  -3663,
     -4359,  -5088,  -5851,  -6645,  -7466,  -8313,  -9181, -10068, -10972, -11887,
    -12814, -13746, -14683, -15620, -16551, -17476, -18395, -19296, -20180, -21046,
    -21891, -22708, -23494, -24251, -24970, -25649, -26294, -26887, -27437, -27940,
    -28390, -28789, -29132, -29416, -29644, -29811, -29919, -29963, -29942, -29857,
    -29712, -29495, -29217, -28873, -28465, -27992, -27453, -26850, -26188, -25463,
    -24679, -23836, -22935, -21982, -20975, -19919, -18814, -17662, -16469, -15236,
    -13965, -12660, -11325,  -9963,  -8574,  -7164,  -5736,  -4296,  -2844,  -1385,
        73,   1531,   2991,   4443,   5881,   7309,   8717,  10104,  11465,  12798,
     14100,  15370,  16600,  17791,  18940,  20040,  21094,  22097,  23046,  23942,
     24781,  25561,  26282,  26939,  27538,  28071,  28540,  28942,  29281,  29555,
     29765,  29906,  29984,  29999,  29950,  29836,  29664,  29429,  29139,  28790,
     28385,  27930,  27421,  26866,  26265,  25616,  24931,  24205,  23443,  22652,
     21829,  20980,  20107,  19219,  18313,  17390,  16460,  15523,  14582,  13640,
     12705,  11775,  10855,   9948,   9057,   8187,   7337,   6513,   5717,   4952,
      4219,   3521,   2863,   2244,   1667,   1134,    647,    207,   -183,   -526,
      -817,  -1056,  -1245,  -1378,  -1460,  -1487,  -1461,  -1385,  -1252,  -1066,
      -833,   -543,   -211,    174,    606,   1085,   1605,   2168,   2773,   3416,
      4094,   4807,   5553,   6327,   7127,   7952,   8798,   9660,  10542,  11436,
     12341,  13251,  14168,  15086,  16003,  16917,  17824,  18719,  19606,  20475,
     21327,  22160,  22971,  23756,  24515,  25244,  25942,  26603,  27235,  27829,
     28382,  28899,  29371,  29804,  30195,  30538,  30838,  31093,  31303,  31466,
     31584,  31655,  31680,  31662,  31597,  31489,  31336,  31139,  30902,  30626,
     30310,  29955,  29565,  29139,  28682,  28194,  27673,  27128,  26559,  25968,
     25352,  24719,  24069,  23404,  22731,  22046,  21353,  20657,  19959,  19260,
     18563,  17870,  17184,  16508,  15842,  15190,  14550,  13930,  13327,  12746,
     12187,  11655,  11142,  10660,  10203,   9777,   9383,   9017,   8684,   8384,
      8117,   7885,   7685,   7521,   7386,   7290,   7226,   7198,   7199,   7235,
      7304,   7402,   7534,   7691,   7878,   8094,   8336,   8603,   8890,   9204,
      9534,   9882,  10252,  10634,  11031,  11443,  11863,  12292,  12726,  13167,
     13613,  14057,  14501,  14944,  15385,  15814,  16242,  16658,  17064,  17459,
     17841,  18206,  18556,  18886,  19204,  19496,  19769,  20018,  20246,  20451,
     20631,  20786,  20916,  21020,  21098,  21150,  21177,  21174,  21150,  21095,
     21017,  20913,  20781,  20626,  20448,  20246,  20020,  19774,  19506,  19218,
     18911,  18585,  18242,  17884,  17511,  17122,  16724,  16310,  15888,  15458,
     15016,  14573,  14122,  13666,  13206,  12745,  12287,  11827,  11368,  10910,
     10457,  10010,   9568,   9131,   8700,   8280,   7865,   7460,   7066,   6680,
      6307,   5942,   5587,   5247,   4915,   4597,   4290,   3990,   3706,   3431,
      3168,   2914,   2668,   2433,   2207,   1989,   1778,   1575,   1378,   1187,
       999,    817,    638,    458,    284,    109,    -63,   -239,   -419,   -599,
      -782,   -973,  -1166,  -1366,  -1572,  -1784,  -2006,  -2237,  -2476,  -2727,
     -2985,  -3253,  -3534,  -3824,  -4130,  -4443,  -4768,  -5107,  -5453,  -5815,
     -6187,  -6569,  -6963,  -7363,  -7777,  -8200,  -8629,  -9067,  -9513,  -9964,
    -10420, -10884, -11348, -11815, -12284, -12752, -13222, -13689, -14155, -14615,
    -15066, -15517, -15956, -16387, -16808, -17214, -17612, -17991, -18357, -18708,
    -19041, -19355, -19650, -19926, -20177, -20409, -20618, -20801, -20961, -21098,
    -21206, -21290, -21347, -21376, -21382, -21359, -21310, -21233, -21132, -21004,
    -20850, -20668, -20465, -20237, -19988, -19715, -19421, -19106, -18774, -18422,
    -18055, -17671, -17273, -16862, -16444, -16012, -15579, -15132, -14685, -14237,
    -13787, -13338, -12889, -12449, -12014, -11587, -11168, -10764, -10375,  -9997,
     -9641,  -9305,  -8982,  -8687,  -8413,  -8162,  -7937,  -7741,  -7575,  -7435,
     -7327,  -7251,  -7206,  -7195,  -7215,  -7270,  -7359,  -7483,  -7639,  -7830,
     -8054,  -8313,  -8603,  -8929,  -9287,  -9673, -10092, -10541, -11015, -11521,
    -12047, -12599, -13173, -13770, -14384, -15018, -15664, -16325, -16996, -17678,
    -18367, -19059, -19754, -20451, -21144, -21835, -22516, -23188, -23851, -24500,
    -25133, -25747, -26340, -26908, -27454, -27974, -28465, -28923, -29350, -29743,
    -30101, -30420, -30698, -30938, -31140, -31297, -31410, -31479, -31502, -31483,
    -31419, -31306, -31149, -30946, -30698, -30404, -30068, -29684, -29260, -28795,
    -28286, -27741, -27154, -26533, -25878, -25189, -24468, -23719, -22943, -22140,
    -21316, -20472, -19613, -18735, -17847, -16950, -16045, -15137, -14227, -13319,
    -12418, -11520, -10634,  -9761,  -8904,  -8067,  -7249,  -6457,  -5690,  -4952,
     -4245,  -3573,  -2936,  -2338,  -1780,  -1265,   -791,   -363,     17,    345,
       631,    862,   1043,   1173,   1248,   1271,   1242,   1159,   1027,    837,
       598,    307,    -36,   -425,   -866,  -1352,  -1884,  -2457,  -3075,  -3730,
     -4424,  -5153,  -5915,  -6707,  -7526,  -8371,  -9238, -10123, -11025, -11938,
    -12862, -13792, -14726, -15660, -16590, -17513, -18428, -19326, -20208, -21072,
    -21912, -22728, -23511, -24264, -24982, -25658, -26298, -26889, -27437, -27937,
    -28382, -28779, -29119, -29402, -29627, -29790, -29895, -29935, -29913, -29826,
    -29677, -29458, -29177, -28831, -28420, -27944, -27404, -26800, -26135, -25407,
    -24621, -23776, -22874, -21920, -20910, -19852, -18748, -17595, -16400, -15166,
    -13894, -12589, -11253,  -9889,  -8501,  -7091,  -5662,  -4224,  -2770,  -1311
};

/*
 * Waveform name: jazz_organ_40616004, size: 1260 samples
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 4 | 0 | 6 | 1 | 6 | 0 | 0 | 4 | 0 |
 */
const  int16  jazz_organ_406160040[] =
{
         0,    921,   1850,   2774,   3695,   4609,   5515,   6414,   7299,   8177,
      9040,   9889,  10721,  11538,  12336,  13117,  13875,  14612,  15329,  16022,
     16693,  17337,  17956,  18549,  19115,  19655,  20166,  20653,  21109,  21536,
     21937,  22307,  22649,  22963,  23250,  23508,  23738,  23941,  24116,  24266,
     24390,  24487,  24563,  24612,  24637,  24641,  24624,  24584,  24529,  24451,
     24356,  24245,  24116,  23976,  23820,  23651,  23470,  23280,  23081,  22874,
     22657,  22439,  22211,  21979,  21747,  21511,  21274,  21036,  20801,  20565,
     20331,  20100,  19874,  19651,  19435,  19222,  19015,  18817,  18621,  18435,
     18257,  18088,  17922,  17766,  17622,  17481,  17348,  17225,  17111,  17001,
     16898,  16803,  16716,  16634,  16556,  16486,  16421,  16359,  16300,  16245,
     16193,  16138,  16089,  16037,  15988,  15939,  15885,  15832,  15773,  15709,
     15644,  15576,  15498,  15414,  15325,  15228,  15124,  15010,  14886,  14755,
     14614,  14464,  14301,  14130,  13946,  13752,  13547,  13330,  13104,  12866,
     12617,  12357,  12085,  11806,  11517,  11215,  10907,  10590,  10265,   9933,
      9595,   9251,   8901,   8546,   8190,   7829,   7468,   7107,   6745,   6382,
      6026,   5671,   5321,   4976,   4637,   4307,   3986,   3674,   3376,   3087,
      2813,   2553,   2306,   2074,   1865,   1672,   1499,   1341,   1208,   1096,
      1007,    938,    896,    877,    883,    915,    972,   1054,   1162,   1299,
      1461,   1647,   1862,   2103,   2371,   2663,   2981,   3325,   3693,   4086,
      4501,   4941,   5403,   5886,   6389,   6910,   7453,   8012,   8586,   9177,
      9781,  10398,  11027,  11666,  12315,  12971,  13632,  14299,  14970,  15640,
     16311,  16978,  17649,  18312,  18973,  19625,  20269,  20901,  21525,  22136,
     22733,  23313,  23879,  24428,  24956,  25469,  25957,  26423,  26867,  27289,
     27686,  28057,  28405,  28724,  29016,  29282,  29520,  29729,  29911,  30063,
     30187,  30282,  30350,  30388,  30400,  30382,  30335,  30263,  30164,  30037,
     29883,  29708,  29507,  29280,  29032,  28762,  28471,  28158,  27825,  27475,
     27109,  26725,  26324,  25914,  25486,  25047,  24599,  24139,  23670,  23193,
     22712,  22224,  21732,  21236,  20740,  20238,  19739,  19239,  18741,  18245,
     17753,  17265,  16780,  16302,  15827,  15361,  14899,  14449,  14003,  13564,
     13136,  12718,  12308,  11907,  11514,  11132,  10755,  10393,  10035,   9688,
      9348,   9017,   8694,   8379,   8067,   7767,   7470,   7182,   6895,   6612,
      6338,   6061,   5789,   5521,   5251,   4983,   4717,   4447,   4180,   3904,
      3629,   3351,   3068,   2779,   2489,   2188,   1884,   1571,   1254,    927,
       592,    248,   -100,   -459,   -830,  -1210,  -1599,  -1996,  -2403,  -2819,
     -3243,  -3678,  -4121,  -4575,  -5035,  -5500,  -5975,  -6458,  -6944,  -7436,
     -7934,  -8436,  -8941,  -9446,  -9956, -10465, -10976, -11483, -11989, -12492,
    -12990, -13484, -13972, -14453, -14924, -15386, -15836, -16275, -16699, -17113,
    -17510, -17890, -18257, -18602, -18927, -19235, -19518, -19782, -20024, -20240,
    -20432, -20601, -20744, -20860, -20951, -21012, -21048, -21052, -21033, -20983,
    -20905, -20801, -20666, -20504, -20312, -20094, -19849, -19573, -19275, -18950,
    -18597, -18221, -17820, -17396, -16951, -16484, -15996, -15486, -14962, -14419,
    -13860, -13284, -12697, -12099, -11489, -10868, -10241,  -9604,  -8964,  -8320,
     -7676,  -7031,  -6384,  -5739,  -5097,  -4463,  -3834,  -3212,  -2599,  -1996,
     -1406,   -826,   -266,    281,    811,   1324,   1820,   2295,   2747,   3180,
      3591,   3978,   4341,   4681,   4993,   5282,   5544,   5783,   5992,   6176,
      6334,   6463,   6568,   6644,   6695,   6720,   6718,   6693,   6644,   6566,
      6465,   6344,   6199,   6032,   5842,   5635,   5407,   5162,   4898,   4617,
      4322,   4014,   3687,   3357,   3007,   2652,   2285,   1911,   1531,   1143,
       752,    359,    -38,   -437,   -834,  -1231,  -1630,  -2025,  -2416,  -2802,
     -3186,  -3564,  -3933,  -4297,  -4653,  -4998,  -5339,  -5667,  -5986,  -6296,
     -6596,  -6885,  -7163,  -7430,  -7685,  -7930,  -8168,  -8390,  -8605,  -8806,
     -8998,  -9180,  -9353,  -9517,  -9672,  -9819,  -9959, -10089, -10214, -10336,
    -10446, -10554, -10660, -10761, -10858, -10955, -11046, -11141, -11234, -11327,
    -11424, -11519, -11620, -11724, -11827, -11937, -12051, -12175, -12302, -12433,
    -12572, -12720, -12874, -13035, -13205, -13381, -13567, -13759, -13959, -14168,
    -14384, -14609, -14840, -15082, -15327, -15580, -15838, -16102, -16372, -16645,
    -16923, -17202, -17485, -17768, -18053, -18336, -18621, -18901, -19178, -19454,
    -19720, -19982, -20238, -20487, -20725, -20951, -21167, -21371, -21561, -21737,
    -21895, -22040, -22165, -22271, -22357, -22423, -22467, -22492, -22490, -22465,
    -22416, -22342, -22241, -22114, -21960, -21777, -21568, -21331, -21069, -20772,
    -20451, -20102, -19723, -19315, -18880, -18418, -17926, -17409, -16864, -16296,
    -15701, -15080, -14436, -13771, -13083, -12372, -11641, -10892, -10127,  -9344,
     -8546,  -7731,  -6904,  -6068,  -5219,  -4362,  -3499,  -2627,  -1753,   -875,
         0,    875,   1753,   2627,   3499,   4362,   5219,   6068,   6904,   7731,
      8546,   9344,  10127,  10892,  11641,  12372,  13083,  13771,  14436,  15080,
     15701,  16296,  16864,  17409,  17926,  18418,  18880,  19315,  19723,  20102,
     20451,  20772,  21069,  21331,  21568,  21777,  21960,  22114,  22241,  22342,
     22416,  22465,  22490,  22492,  22467,  22423,  22357,  22271,  22165,  22040,
     21895,  21737,  21561,  21371,  21167,  20951,  20725,  20487,  20238,  19982,
     19720,  19454,  19178,  18901,  18621,  18336,  18053,  17768,  17485,  17202,
     16923,  16645,  16372,  16102,  15838,  15580,  15327,  15082,  14840,  14609,
     14384,  14168,  13959,  13759,  13567,  13381,  13205,  13035,  12874,  12720,
     12572,  12433,  12302,  12175,  12051,  11937,  11827,  11724,  11620,  11519,
     11424,  11327,  11234,  11141,  11046,  10955,  10858,  10761,  10660,  10554,
     10446,  10336,  10214,  10089,   9959,   9819,   9672,   9517,   9353,   9180,
      8998,   8806,   8605,   8390,   8168,   7930,   7685,   7430,   7163,   6885,
      6596,   6296,   5986,   5667,   5339,   4998,   4653,   4297,   3933,   3564,
      3186,   2802,   2416,   2025,   1630,   1231,    834,    437,     38,   -359,
      -752,  -1143,  -1531,  -1913,  -2285,  -2652,  -3007,  -3357,  -3687,  -4014,
     -4322,  -4617,  -4898,  -5162,  -5407,  -5635,  -5842,  -6032,  -6199,  -6344,
     -6465,  -6566,  -6644,  -6693,  -6718,  -6720,  -6695,  -6644,  -6568,  -6463,
     -6334,  -6176,  -5992,  -5783,  -5544,  -5282,  -4993,  -4681,  -4341,  -3978,
     -3591,  -3180,  -2747,  -2295,  -1820,  -1324,   -811,   -281,    266,    826,
      1406,   1996,   2599,   3212,   3834,   4463,   5097,   5739,   6384,   7031,
      7676,   8320,   8964,   9604,  10241,  10868,  11489,  12099,  12697,  13284,
     13860,  14419,  14962,  15486,  15996,  16484,  16951,  17396,  17820,  18221,
     18597,  18950,  19275,  19573,  19849,  20094,  20312,  20504,  20666,  20801,
     20905,  20983,  21033,  21052,  21048,  21012,  20951,  20860,  20744,  20601,
     20432,  20240,  20024,  19782,  19518,  19235,  18927,  18602,  18257,  17890,
     17510,  17113,  16699,  16275,  15836,  15386,  14924,  14453,  13972,  13484,
     12990,  12492,  11989,  11483,  10976,  10465,   9956,   9446,   8941,   8436,
      7934,   7436,   6944,   6458,   5975,   5500,   5035,   4575,   4121,   3678,
      3243,   2819,   2403,   1996,   1599,   1210,    830,    459,    100,   -248,
      -592,   -927,  -1254,  -1571,  -1884,  -2188,  -2489,  -2779,  -3068,  -3351,
     -3629,  -3904,  -4180,  -4447,  -4717,  -4983,  -5251,  -5521,  -5789,  -6061,
     -6338,  -6612,  -6895,  -7182,  -7470,  -7767,  -8067,  -8379,  -8694,  -9017,
     -9348,  -9688, -10035, -10393, -10755, -11132, -11514, -11907, -12308, -12718,
    -13136, -13564, -14003, -14449, -14899, -15361, -15827, -16302, -16780, -17265,
    -17753, -18245, -18741, -19239, -19739, -20238, -20740, -21236, -21732, -22224,
    -22712, -23193, -23670, -24139, -24599, -25047, -25486, -25914, -26324, -26725,
    -27109, -27475, -27825, -28158, -28471, -28762, -29032, -29280, -29507, -29708,
    -29883, -30037, -30164, -30263, -30335, -30382, -30400, -30388, -30350, -30282,
    -30187, -30063, -29911, -29729, -29520, -29282, -29016, -28724, -28405, -28057,
    -27686, -27289, -26867, -26423, -25957, -25469, -24956, -24428, -23879, -23313,
    -22733, -22136, -21525, -20901, -20269, -19625, -18973, -18312, -17649, -16978,
    -16311, -15640, -14970, -14299, -13632, -12971, -12315, -11666, -11027, -10398,
     -9781,  -9177,  -8586,  -8012,  -7453,  -6910,  -6389,  -5886,  -5403,  -4941,
     -4501,  -4086,  -3693,  -3325,  -2981,  -2663,  -2371,  -2103,  -1862,  -1647,
     -1461,  -1299,  -1162,  -1054,   -972,   -915,   -883,   -877,   -896,   -938,
     -1007,  -1096,  -1208,  -1341,  -1499,  -1672,  -1865,  -2074,  -2306,  -2553,
     -2813,  -3087,  -3376,  -3674,  -3986,  -4307,  -4637,  -4976,  -5321,  -5671,
     -6026,  -6382,  -6745,  -7107,  -7468,  -7829,  -8190,  -8546,  -8901,  -9251,
     -9595,  -9933, -10265, -10590, -10907, -11215, -11517, -11806, -12085, -12357,
    -12617, -12866, -13104, -13330, -13547, -13752, -13946, -14130, -14301, -14464,
    -14614, -14755, -14886, -15010, -15124, -15228, -15325, -15414, -15498, -15576,
    -15644, -15709, -15773, -15832, -15885, -15939, -15988, -16037, -16089, -16138,
    -16193, -16245, -16300, -16359, -16421, -16486, -16556, -16634, -16716, -16803,
    -16898, -17001, -17111, -17225, -17348, -17481, -17622, -17766, -17922, -18088,
    -18257, -18435, -18621, -18817, -19015, -19222, -19435, -19651, -19874, -20100,
    -20331, -20565, -20801, -21036, -21274, -21511, -21747, -21979, -22211, -22439,
    -22657, -22874, -23081, -23280, -23470, -23651, -23820, -23976, -24116, -24245,
    -24356, -24451, -24529, -24584, -24624, -24641, -24637, -24612, -24563, -24487,
    -24390, -24266, -24116, -23941, -23738, -23508, -23250, -22963, -22649, -22307,
    -21937, -21536, -21109, -20653, -20166, -19655, -19115, -18549, -17956, -17337,
    -16693, -16022, -15329, -14612, -13875, -13117, -12336, -11538, -10721,  -9889,
     -9040,  -8177,  -7299,  -6414,  -5515,  -4609,  -3695,  -2774,  -1850,   -921
};

/*
 * Waveform name: jazz_organ_305060040, size: 1260 samples
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 3 | 0 | 5 | 0 | 6 | 0 | 0 | 4 | 0 |
 */
const  int16  jazz_organ_305060040[] =
{
         0,   1001,   2002,   3002,   3995,   4981,   5956,   6925,   7879,   8819,
      9748,  10657,  11546,  12418,  13265,  14094,  14897,  15675,  16425,  17149,
     17844,  18513,  19150,  19758,  20330,  20873,  21384,  21861,  22304,  22716,
     23094,  23436,  23748,  24023,  24268,  24477,  24654,  24802,  24916,  24998,
     25053,  25074,  25070,  25038,  24977,  24891,  24781,  24646,  24489,  24308,
     24111,  23892,  23655,  23404,  23136,  22853,  22558,  22252,  21939,  21612,
     21280,  20941,  20599,  20252,  19904,  19552,  19201,  18851,  18506,  18160,
     17822,  17483,  17153,  16830,  16512,  16205,  15904,  15616,  15334,  15061,
     14801,  14550,  14308,  14079,  13862,  13653,  13457,  13271,  13096,  12931,
     12775,  12627,  12490,  12363,  12241,  12129,  12025,  11924,  11829,  11740,
     11654,  11572,  11491,  11411,  11335,  11257,  11179,  11099,  11014,  10926,
     10835,  10738,  10636,  10526,  10410,  10284,  10153,  10007,   9855,   9691,
      9517,   9329,   9133,   8922,   8698,   8464,   8215,   7957,   7681,   7396,
      7096,   6784,   6461,   6125,   5779,   5422,   5054,   4674,   4288,   3893,
      3488,   3079,   2663,   2243,   1820,   1392,    963,    533,    106,   -319,
      -742,  -1162,  -1577,  -1983,  -2380,  -2770,  -3152,  -3516,  -3868,  -4204,
     -4527,  -4829,  -5116,  -5382,  -5625,  -5850,  -6049,  -6224,  -6374,  -6496,
     -6593,  -6661,  -6701,  -6710,  -6691,  -6640,  -6558,  -6446,  -6302,  -6125,
     -5916,  -5677,  -5403,  -5099,  -4763,  -4396,  -3995,  -3568,  -3106,  -2620,
     -2101,  -1556,   -982,   -383,    235,    883,   1554,   2243,   2954,   3686,
      4430,   5196,   5971,   6760,   7562,   8369,   9188,  10011,  10839,  11669,
     12500,  13328,  14155,  14977,  15794,  16602,  17398,  18186,  18962,  19720,
     20464,  21190,  21895,  22581,  23244,  23884,  24500,  25091,  25651,  26185,
     26691,  27170,  27612,  28026,  28408,  28758,  29073,  29356,  29605,  29820,
     30002,  30149,  30261,  30341,  30386,  30400,  30377,  30325,  30238,  30122,
     29976,  29797,  29590,  29356,  29096,  28807,  28494,  28158,  27798,  27417,
     27016,  26594,  26157,  25701,  25232,  24745,  24247,  23738,  23221,  22693,
     22157,  21616,  21072,  20521,  19970,  19419,  18867,  18316,  17766,  17221,
     16678,  16142,  15612,  15089,  14573,  14065,  13566,  13077,  12597,  12127,
     11667,  11219,  10784,  10356,   9946,   9541,   9152,   8772,   8401,   8046,
      7698,   7360,   7033,   6714,   6403,   6102,   5810,   5523,   5244,   4966,
      4698,   4432,   4166,   3908,   3648,   3391,   3135,   2874,   2612,   2348,
      2082,   1810,   1535,   1254,    965,    670,    368,     55,   -262,   -592,
      -932,  -1282,  -1643,  -2014,  -2397,  -2793,  -3199,  -3615,  -4045,  -4485,
     -4938,  -5399,  -5874,  -6357,  -6851,  -7356,  -7867,  -8392,  -8920,  -9454,
     -9997, -10545, -11099, -11652, -12211, -12769, -13328, -13887, -14443, -14996,
    -15543, -16087, -16623, -17149, -17666, -18171, -18665, -19144, -19608, -20054,
    -20485, -20896, -21287, -21656, -22002, -22325, -22623, -22896, -23138, -23354,
    -23544, -23700, -23829, -23928, -23991, -24023, -24023, -23989, -23922, -23820,
    -23687, -23518, -23316, -23079, -22811, -22507, -22171, -21802, -21401, -20972,
    -20508, -20018, -19495, -18948, -18374, -17772, -17145, -16499, -15828, -15137,
    -14426, -13699, -12956, -12198, -11424, -10645,  -9851,  -9051,  -8246,  -7434,
     -6623,  -5812,  -4998,  -4187,  -3382,  -2582,  -1791,  -1008,   -235,    518,
      1265,   1993,   2705,   3397,   4067,   4717,   5348,   5950,   6530,   7083,
      7607,   8107,   8576,   9015,   9424,   9804,  10149,  10465,  10748,  11001,
     11221,  11407,  11563,  11686,  11778,  11838,  11865,  11863,  11831,  11770,
     11679,  11561,  11415,  11242,  11044,  10822,  10577,  10309,  10020,   9709,
      9382,   9038,   8677,   8301,   7911,   7506,   7092,   6670,   6241,   5800,
      5358,   4907,   4457,   4001,   3549,   3093,   2641,   2192,   1746,   1305,
       868,    438,     19,   -393,   -798,  -1193,  -1577,  -1949,  -2310,  -2663,
     -3000,  -3326,  -3640,  -3940,  -4229,  -4504,  -4767,  -5017,  -5255,  -5481,
     -5696,  -5899,  -6091,  -6271,  -6444,  -6606,  -6758,  -6904,  -7043,  -7172,
     -7297,  -7417,  -7535,  -7647,  -7759,  -7866,  -7972,  -8080,  -8189,  -8299,
     -8411,  -8527,  -8645,  -8770,  -8899,  -9036,  -9178,  -9329,  -9488,  -9655,
     -9832, -10018, -10214, -10419, -10638, -10864, -11103, -11350, -11612, -11884,
    -12165, -12458, -12762, -13073, -13396, -13727, -14067, -14415, -14770, -15131,
    -15500, -15872, -16250, -16628, -17008, -17392, -17776, -18156, -18536, -18910,
    -19281, -19646, -20003, -20350, -20691, -21015, -21333, -21633, -21918, -22186,
    -22439, -22668, -22881, -23071, -23238, -23383, -23501, -23596, -23660, -23698,
    -23710, -23689, -23639, -23560, -23446, -23299, -23123, -22912, -22670, -22393,
    -22085, -21739, -21361, -20951, -20508, -20031, -19522, -18981, -18407, -17806,
    -17172, -16509, -15817, -15101, -14356, -13586, -12794, -11979, -11141, -10284,
     -9410,  -8517,  -7611,  -6689,  -5755,  -4812,  -3860,  -2901,  -1936,   -967,
         0,    967,   1936,   2901,   3860,   4812,   5755,   6689,   7611,   8517,
      9410,  10284,  11141,  11979,  12794,  13586,  14356,  15101,  15817,  16509,
     17172,  17806,  18407,  18981,  19522,  20031,  20508,  20951,  21361,  21739,
     22085,  22393,  22670,  22912,  23123,  23299,  23446,  23560,  23639,  23689,
     23710,  23698,  23660,  23596,  23501,  23383,  23238,  23071,  22881,  22668,
     22439,  22186,  21918,  21633,  21333,  21015,  20691,  20350,  20003,  19646,
     19281,  18910,  18536,  18156,  17776,  17392,  17008,  16628,  16250,  15872,
     15500,  15131,  14770,  14415,  14067,  13727,  13396,  13073,  12762,  12458,
     12165,  11884,  11612,  11350,  11103,  10864,  10638,  10419,  10214,  10018,
      9832,   9655,   9488,   9329,   9178,   9036,   8899,   8770,   8645,   8527,
      8411,   8299,   8189,   8080,   7972,   7866,   7759,   7647,   7535,   7417,
      7297,   7172,   7043,   6904,   6758,   6606,   6444,   6271,   6091,   5899,
      5696,   5481,   5255,   5017,   4767,   4504,   4229,   3940,   3640,   3326,
      3000,   2663,   2310,   1949,   1577,   1193,    798,    393,    -19,   -438,
      -868,  -1305,  -1746,  -2192,  -2641,  -3093,  -3549,  -4001,  -4457,  -4907,
     -5358,  -5800,  -6241,  -6670,  -7092,  -7506,  -7911,  -8301,  -8677,  -9038,
     -9382,  -9709, -10020, -10309, -10577, -10822, -11044, -11242, -11415, -11561,
    -11679, -11770, -11831, -11863, -11865, -11838, -11778, -11686, -11563, -11407,
    -11221, -11001, -10748, -10465, -10149,  -9804,  -9424,  -9015,  -8576,  -8107,
     -7607,  -7083,  -6530,  -5950,  -5348,  -4717,  -4067,  -3397,  -2705,  -1993,
     -1265,   -518,    235,   1008,   1791,   2582,   3382,   4187,   4998,   5812,
      6623,   7434,   8246,   9051,   9851,  10645,  11424,  12198,  12956,  13699,
     14426,  15137,  15828,  16499,  17145,  17772,  18374,  18948,  19495,  20018,
     20508,  20972,  21401,  21802,  22171,  22507,  22811,  23079,  23316,  23518,
     23687,  23820,  23922,  23989,  24023,  24023,  23991,  23928,  23829,  23700,
     23544,  23354,  23138,  22896,  22623,  22325,  22002,  21656,  21287,  20896,
     20485,  20054,  19608,  19144,  18665,  18171,  17666,  17149,  16623,  16087,
     15543,  14996,  14443,  13887,  13328,  12769,  12211,  11652,  11099,  10545,
      9997,   9454,   8920,   8392,   7867,   7356,   6851,   6357,   5874,   5399,
      4938,   4485,   4045,   3615,   3199,   2793,   2397,   2014,   1643,   1282,
       932,    592,    262,    -55,   -368,   -670,   -965,  -1254,  -1535,  -1810,
     -2082,  -2348,  -2612,  -2874,  -3135,  -3391,  -3648,  -3908,  -4166,  -4432,
     -4698,  -4966,  -5244,  -5523,  -5810,  -6102,  -6403,  -6714,  -7033,  -7360,
     -7698,  -8046,  -8401,  -8772,  -9152,  -9541,  -9946, -10356, -10784, -11219,
    -11667, -12127, -12597, -13077, -13566, -14065, -14573, -15089, -15612, -16142,
    -16678, -17221, -17766, -18316, -18867, -19419, -19970, -20521, -21072, -21616,
    -22157, -22693, -23221, -23738, -24247, -24745, -25232, -25701, -26157, -26594,
    -27016, -27417, -27798, -28158, -28494, -28807, -29096, -29356, -29590, -29797,
    -29976, -30122, -30238, -30325, -30377, -30400, -30386, -30341, -30261, -30149,
    -30002, -29820, -29605, -29356, -29073, -28758, -28408, -28026, -27612, -27170,
    -26691, -26185, -25651, -25091, -24500, -23884, -23244, -22581, -21895, -21190,
    -20464, -19720, -18962, -18186, -17398, -16602, -15794, -14977, -14155, -13328,
    -12500, -11669, -10839, -10011,  -9188,  -8369,  -7562,  -6760,  -5971,  -5196,
     -4430,  -3686,  -2954,  -2243,  -1554,   -883,   -235,    383,    982,   1556,
      2101,   2620,   3106,   3568,   3995,   4396,   4763,   5099,   5403,   5677,
      5916,   6125,   6302,   6446,   6558,   6640,   6691,   6710,   6701,   6661,
      6593,   6496,   6374,   6224,   6049,   5850,   5625,   5382,   5116,   4829,
      4527,   4204,   3868,   3516,   3152,   2770,   2380,   1983,   1577,   1162,
       742,    319,   -106,   -533,   -963,  -1392,  -1820,  -2243,  -2663,  -3079,
     -3488,  -3893,  -4288,  -4674,  -5054,  -5422,  -5779,  -6125,  -6461,  -6784,
     -7096,  -7396,  -7681,  -7957,  -8215,  -8464,  -8698,  -8922,  -9133,  -9329,
     -9517,  -9691,  -9855, -10007, -10153, -10284, -10410, -10526, -10636, -10738,
    -10835, -10926, -11014, -11099, -11179, -11257, -11335, -11411, -11491, -11572,
    -11654, -11740, -11829, -11924, -12025, -12129, -12241, -12363, -12490, -12627,
    -12775, -12931, -13096, -13271, -13457, -13653, -13862, -14079, -14308, -14550,
    -14801, -15061, -15334, -15616, -15904, -16205, -16512, -16830, -17153, -17483,
    -17822, -18160, -18506, -18851, -19201, -19552, -19904, -20252, -20599, -20941,
    -21280, -21612, -21939, -22252, -22558, -22853, -23136, -23404, -23655, -23892,
    -24111, -24308, -24489, -24646, -24781, -24891, -24977, -25038, -25070, -25074,
    -25053, -24998, -24916, -24802, -24654, -24477, -24268, -24023, -23748, -23436,
    -23094, -22716, -22304, -21861, -21384, -20873, -20330, -19758, -19150, -18513,
    -17844, -17149, -16425, -15675, -14897, -14094, -13265, -12418, -11546, -10657,
     -9748,  -8819,  -7879,  -6925,  -5956,  -4981,  -3995,  -3002,  -2002,  -1001
};

/*
 * Waveform name: glockenspiel_008360400, size: 1260 samples (Use percussive ENV)
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 0 | 0 | 8 | 3 | 6 | 0 | 4 | 0 | 0 |
 */
const  int16  glockenspiel_008360400[] =
{
         0,    963,   1930,   2897,   3859,   4818,   5771,   6717,   7658,   8589,
      9513,  10425,  11330,  12220,  13098,  13962,  14814,  15650,  16469,  17271,
     18059,  18826,  19575,  20304,  21016,  21705,  22373,  23021,  23646,  24249,
     24831,  25388,  25923,  26432,  26919,  27382,  27820,  28236,  28625,  28991,
     29333,  29651,  29947,  30217,  30461,  30684,  30883,  31057,  31213,  31342,
     31454,  31539,  31605,  31651,  31675,  31680,  31669,  31635,  31585,  31518,
     31434,  31332,  31217,  31086,  30943,  30784,  30614,  30429,  30235,  30030,
     29815,  29590,  29359,  29119,  28872,  28619,  28358,  28097,  27829,  27556,
     27283,  27009,  26730,  26452,  26175,  25896,  25620,  25344,  25069,  24798,
     24529,  24265,  24005,  23748,  23495,  23250,  23009,  22774,  22544,  22323,
     22106,  21894,  21694,  21498,  21309,  21127,  20956,  20789,  20630,  20478,
     20334,  20198,  20067,  19942,  19829,  19721,  19619,  19523,  19436,  19351,
     19274,  19204,  19139,  19081,  19024,  18974,  18927,  18882,  18846,  18809,
     18779,  18750,  18724,  18699,  18677,  18657,  18637,  18620,  18600,  18585,
     18567,  18549,  18530,  18513,  18494,  18474,  18451,  18428,  18402,  18375,
     18346,  18315,  18283,  18245,  18208,  18167,  18123,  18077,  18032,  17980,
     17926,  17870,  17809,  17749,  17687,  17620,  17554,  17484,  17415,  17344,
     17272,  17197,  17123,  17048,  16972,  16899,  16825,  16752,  16680,  16609,
     16540,  16475,  16409,  16348,  16292,  16235,  16183,  16138,  16095,  16060,
     16028,  16002,  15982,  15967,  15959,  15956,  15962,  15978,  15997,  16026,
     16064,  16109,  16160,  16225,  16295,  16372,  16461,  16558,  16665,  16781,
     16903,  17036,  17179,  17330,  17490,  17659,  17836,  18021,  18215,  18416,
     18626,  18841,  19067,  19296,  19532,  19775,  20022,  20275,  20531,  20792,
     21055,  21322,  21591,  21862,  22135,  22407,  22679,  22952,  23221,  23488,
     23755,  24017,  24273,  24525,  24772,  25011,  25244,  25469,  25684,  25892,
     26088,  26274,  26448,  26609,  26757,  26893,  27013,  27120,  27210,  27283,
     27340,  27381,  27402,  27405,  27388,  27355,  27298,  27224,  27126,  27010,
     26871,  26710,  26527,  26321,  26092,  25841,  25569,  25273,  24955,  24612,
     24247,  23860,  23450,  23016,  22561,  22083,  21583,  21063,  20520,  19954,
     19372,  18768,  18144,  17504,  16844,  16165,  15468,  14755,  14027,  13283,
     12525,  11754,  10970,  10174,   9364,   8547,   7720,   6883,   6040,   5189,
      4333,   3472,   2607,   1738,    869,      0,   -869,  -1738,  -2607,  -3472,
     -4333,  -5189,  -6040,  -6883,  -7720,  -8547,  -9364, -10174, -10970, -11754,
    -12525, -13283, -14027, -14755, -15468, -16165, -16844, -17504, -18144, -18768,
    -19372, -19954, -20520, -21063, -21583, -22083, -22561, -23016, -23450, -23860,
    -24247, -24613, -24955, -25273, -25569, -25841, -26092, -26321, -26527, -26710,
    -26871, -27010, -27126, -27224, -27298, -27355, -27388, -27405, -27402, -27381,
    -27340, -27283, -27210, -27120, -27013, -26893, -26757, -26609, -26448, -26274,
    -26088, -25892, -25684, -25469, -25244, -25011, -24772, -24525, -24273, -24017,
    -23755, -23488, -23221, -22952, -22679, -22407, -22135, -21862, -21591, -21322,
    -21057, -20792, -20531, -20275, -20022, -19775, -19532, -19296, -19067, -18841,
    -18626, -18416, -18215, -18021, -17836, -17659, -17490, -17330, -17179, -17036,
    -16903, -16781, -16665, -16558, -16461, -16372, -16295, -16225, -16160, -16109,
    -16064, -16026, -15997, -15978, -15962, -15956, -15959, -15967, -15982, -16002,
    -16028, -16060, -16095, -16138, -16183, -16235, -16292, -16348, -16409, -16475,
    -16540, -16609, -16680, -16752, -16825, -16899, -16972, -17048, -17123, -17197,
    -17272, -17344, -17415, -17484, -17554, -17620, -17687, -17749, -17809, -17870,
    -17926, -17980, -18032, -18077, -18123, -18167, -18208, -18245, -18283, -18315,
    -18346, -18375, -18402, -18428, -18451, -18474, -18494, -18513, -18530, -18549,
    -18567, -18585, -18600, -18620, -18637, -18657, -18677, -18699, -18724, -18750,
    -18779, -18809, -18846, -18882, -18927, -18974, -19024, -19081, -19139, -19204,
    -19274, -19351, -19436, -19523, -19619, -19721, -19829, -19942, -20067, -20198,
    -20334, -20478, -20630, -20789, -20956, -21127, -21309, -21498, -21694, -21894,
    -22106, -22323, -22544, -22774, -23009, -23250, -23495, -23748, -24005, -24265,
    -24529, -24798, -25069, -25344, -25620, -25896, -26175, -26452, -26730, -27009,
    -27283, -27556, -27829, -28097, -28358, -28619, -28872, -29119, -29359, -29590,
    -29815, -30030, -30235, -30429, -30614, -30784, -30943, -31086, -31217, -31332,
    -31434, -31518, -31585, -31635, -31669, -31680, -31675, -31651, -31605, -31539,
    -31454, -31342, -31213, -31057, -30883, -30684, -30461, -30217, -29947, -29651,
    -29333, -28991, -28625, -28236, -27820, -27382, -26919, -26432, -25923, -25388,
    -24831, -24249, -23646, -23021, -22373, -21705, -21016, -20304, -19575, -18826,
    -18059, -17271, -16469, -15650, -14814, -13962, -13098, -12220, -11330, -10425,
     -9513,  -8589,  -7658,  -6717,  -5771,  -4818,  -3859,  -2897,  -1930,   -963,
         0,    963,   1930,   2897,   3859,   4818,   5771,   6717,   7658,   8589,
      9513,  10425,  11330,  12220,  13098,  13962,  14814,  15650,  16469,  17271,
     18059,  18826,  19575,  20304,  21016,  21705,  22373,  23021,  23646,  24249,
     24831,  25388,  25923,  26432,  26919,  27382,  27820,  28236,  28625,  28991,
     29333,  29651,  29947,  30217,  30461,  30684,  30883,  31057,  31213,  31342,
     31454,  31539,  31605,  31651,  31675,  31680,  31669,  31635,  31585,  31518,
     31434,  31332,  31217,  31086,  30943,  30784,  30614,  30429,  30235,  30030,
     29815,  29590,  29359,  29119,  28872,  28619,  28358,  28097,  27829,  27556,
     27283,  27009,  26730,  26452,  26175,  25896,  25620,  25344,  25069,  24798,
     24529,  24265,  24005,  23748,  23495,  23250,  23009,  22774,  22544,  22323,
     22106,  21894,  21694,  21498,  21309,  21127,  20956,  20789,  20630,  20478,
     20334,  20198,  20067,  19942,  19829,  19721,  19619,  19523,  19436,  19351,
     19274,  19204,  19139,  19081,  19024,  18974,  18927,  18882,  18846,  18809,
     18779,  18750,  18724,  18699,  18677,  18657,  18637,  18620,  18600,  18585,
     18567,  18549,  18530,  18513,  18494,  18474,  18451,  18428,  18402,  18375,
     18346,  18315,  18283,  18245,  18208,  18167,  18123,  18077,  18032,  17980,
     17926,  17870,  17809,  17749,  17687,  17620,  17554,  17484,  17415,  17344,
     17272,  17197,  17123,  17048,  16972,  16899,  16825,  16752,  16680,  16609,
     16540,  16475,  16409,  16348,  16292,  16235,  16183,  16138,  16095,  16060,
     16028,  16002,  15982,  15967,  15959,  15956,  15962,  15978,  15997,  16026,
     16064,  16109,  16160,  16225,  16295,  16372,  16461,  16558,  16665,  16781,
     16903,  17036,  17179,  17330,  17490,  17659,  17836,  18021,  18215,  18416,
     18626,  18841,  19067,  19296,  19532,  19775,  20022,  20275,  20531,  20792,
     21055,  21322,  21591,  21862,  22135,  22407,  22679,  22952,  23221,  23488,
     23755,  24017,  24273,  24525,  24772,  25011,  25244,  25469,  25684,  25892,
     26088,  26274,  26448,  26609,  26757,  26893,  27013,  27120,  27210,  27283,
     27340,  27381,  27402,  27405,  27388,  27355,  27298,  27224,  27126,  27010,
     26871,  26710,  26527,  26321,  26092,  25841,  25569,  25273,  24955,  24612,
     24247,  23860,  23450,  23016,  22561,  22083,  21583,  21063,  20520,  19954,
     19372,  18768,  18144,  17504,  16844,  16165,  15468,  14755,  14027,  13283,
     12525,  11754,  10970,  10174,   9364,   8547,   7720,   6883,   6040,   5189,
      4333,   3472,   2607,   1738,    869,      0,   -869,  -1738,  -2607,  -3472,
     -4333,  -5189,  -6040,  -6883,  -7720,  -8547,  -9364, -10174, -10970, -11754,
    -12525, -13283, -14027, -14755, -15468, -16165, -16844, -17504, -18144, -18768,
    -19372, -19954, -20520, -21063, -21583, -22083, -22561, -23016, -23450, -23860,
    -24247, -24613, -24955, -25273, -25569, -25841, -26092, -26321, -26527, -26710,
    -26871, -27010, -27126, -27224, -27298, -27355, -27388, -27405, -27402, -27381,
    -27340, -27283, -27210, -27120, -27013, -26893, -26757, -26609, -26448, -26274,
    -26088, -25892, -25684, -25469, -25244, -25011, -24772, -24525, -24273, -24017,
    -23755, -23488, -23221, -22952, -22679, -22407, -22135, -21862, -21591, -21322,
    -21057, -20792, -20531, -20275, -20022, -19775, -19532, -19296, -19067, -18841,
    -18626, -18416, -18215, -18021, -17836, -17659, -17490, -17330, -17179, -17036,
    -16903, -16781, -16665, -16558, -16461, -16372, -16295, -16225, -16160, -16109,
    -16064, -16026, -15997, -15978, -15962, -15956, -15959, -15967, -15982, -16002,
    -16028, -16060, -16095, -16138, -16183, -16235, -16292, -16348, -16409, -16475,
    -16540, -16609, -16680, -16752, -16825, -16899, -16972, -17048, -17123, -17197,
    -17272, -17344, -17415, -17484, -17554, -17620, -17687, -17749, -17809, -17870,
    -17926, -17980, -18032, -18077, -18123, -18167, -18208, -18245, -18283, -18315,
    -18346, -18375, -18402, -18428, -18451, -18474, -18494, -18513, -18530, -18549,
    -18567, -18585, -18600, -18620, -18637, -18657, -18677, -18699, -18724, -18750,
    -18779, -18809, -18846, -18882, -18927, -18974, -19024, -19081, -19139, -19204,
    -19274, -19351, -19436, -19523, -19619, -19721, -19829, -19942, -20067, -20198,
    -20334, -20478, -20630, -20789, -20956, -21127, -21309, -21498, -21694, -21894,
    -22106, -22323, -22544, -22774, -23009, -23250, -23495, -23748, -24005, -24265,
    -24529, -24798, -25069, -25344, -25620, -25896, -26175, -26452, -26730, -27009,
    -27283, -27556, -27829, -28097, -28358, -28619, -28872, -29119, -29359, -29590,
    -29815, -30030, -30235, -30429, -30614, -30784, -30943, -31086, -31217, -31332,
    -31434, -31518, -31585, -31635, -31669, -31680, -31675, -31651, -31605, -31539,
    -31454, -31342, -31213, -31057, -30883, -30684, -30461, -30217, -29947, -29651,
    -29333, -28991, -28625, -28236, -27820, -27382, -26919, -26432, -25923, -25388,
    -24831, -24249, -23646, -23021, -22373, -21705, -21016, -20304, -19575, -18826,
    -18059, -17271, -16469, -15650, -14814, -13962, -13098, -12220, -11330, -10425,
     -9513,  -8589,  -7658,  -6717,  -5771,  -4818,  -3859,  -2897,  -1930,   -963
};

/*
 * Waveform name: theatre_organ_878656463, size: 1260 samples
 * Osc. Freq. Divider:   2.000
 * Hammond registration:
 * Drawbar | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 * Setting | 8 | 7 | 8 | 6 | 5 | 6 | 4 | 6 | 3 |
 */
const  int16  theatre_organ_878656463[] =
{
         0,   1292,   2592,   3890,   5176,   6450,   7713,   8961,  10190,  11397,
     12582,  13741,  14873,  15979,  17052,  18089,  19094,  20061,  20988,  21882,
     22731,  23542,  24309,  25032,  25713,  26343,  26937,  27478,  27980,  28435,
     28848,  29215,  29540,  29818,  30057,  30254,  30409,  30532,  30608,  30652,
     30663,  30639,  30582,  30497,  30382,  30233,  30066,  29879,  29664,  29432,
     29184,  28917,  28639,  28353,  28053,  27743,  27430,  27109,  26788,  26467,
     26145,  25824,  25511,  25201,  24899,  24602,  24317,  24040,  23775,  23521,
     23278,  23054,  22846,  22646,  22468,  22303,  22153,  22018,  21904,  21802,
     21723,  21658,  21610,  21574,  21558,  21556,  21569,  21600,  21641,  21697,
     21767,  21847,  21942,  22042,  22157,  22281,  22411,  22550,  22696,  22850,
     23008,  23169,  23338,  23501,  23677,  23851,  24024,  24198,  24369,  24539,
     24712,  24880,  25040,  25199,  25359,  25507,  25652,  25791,  25926,  26056,
     26171,  26288,  26393,  26484,  26575,  26655,  26725,  26788,  26844,  26890,
     26925,  26950,  26970,  26979,  26977,  26968,  26951,  26922,  26885,  26840,
     26786,  26720,  26645,  26566,  26477,  26378,  26273,  26158,  26035,  25904,
     25768,  25622,  25472,  25310,  25151,  24977,  24799,  24613,  24432,  24239,
     24044,  23840,  23636,  23429,  23215,  23006,  22787,  22572,  22351,  22131,
     21912,  21693,  21471,  21255,  21040,  20827,  20616,  20410,  20206,  20009,
     19815,  19631,  19446,  19270,  19099,  18938,  18784,  18636,  18498,  18369,
     18248,  18137,  18033,  17940,  17859,  17781,  17718,  17664,  17618,  17582,
     17558,  17540,  17527,  17529,  17538,  17549,  17573,  17601,  17634,  17675,
     17716,  17766,  17816,  17868,  17925,  17977,  18029,  18079,  18129,  18172,
     18215,  18248,  18276,  18298,  18309,  18311,  18298,  18278,  18244,  18196,
     18131,  18055,  17961,  17846,  17716,  17569,  17403,  17219,  17008,  16783,
     16539,  16275,  15984,  15674,  15350,  14996,  14631,  14247,  13839,  13411,
     12967,  12511,  12029,  11538,  11035,  10520,   9992,   9452,   8903,   8349,
      7785,   7223,   6652,   6087,   5517,   4950,   4390,   3832,   3283,   2740,
      2213,   1696,   1194,    708,    241,   -205,   -634,  -1045,  -1423,  -1785,
     -2119,  -2423,  -2701,  -2948,  -3166,  -3352,  -3511,  -3635,  -3730,  -3788,
     -3821,  -3813,  -3775,  -3706,  -3606,  -3472,  -3311,  -3120,  -2901,  -2653,
     -2375,  -2076,  -1748,  -1399,  -1030,   -639,   -235,    192,    632,   1080,
      1548,   2021,   2501,   2981,   3469,   3962,   4449,   4939,   5419,   5896,
      6363,   6823,   7264,   7694,   8111,   8512,   8892,   9252,   9589,   9910,
     10203,  10470,  10718,  10933,  11123,  11284,  11423,  11527,  11606,  11657,
     11679,  11670,  11638,  11573,  11484,  11365,  11225,  11054,  10863,  10650,
     10411,  10157,   9875,   9578,   9261,   8933,   8586,   8230,   7859,   7479,
      7093,   6699,   6296,   5896,   5486,   5082,   4676,   4273,   3875,   3480,
      3090,   2712,   2339,   1976,   1627,   1290,    966,    660,    365,     83,
      -179,   -420,   -650,   -860,  -1049,  -1218,  -1375,  -1507,  -1622,  -1718,
     -1796,  -1854,  -1891,  -1913,  -1915,  -1902,  -1874,  -1824,  -1763,  -1685,
     -1590,  -1485,  -1368,  -1238,  -1092,   -940,   -778,   -606,   -424,   -235,
       -42,    155,    359,    567,    778,    993,   1208,   1425,   1644,   1859,
      2072,   2282,   2495,   2705,   2905,   3111,   3304,   3498,   3684,   3865,
      4040,   4210,   4370,   4527,   4674,   4813,   4948,   5074,   5191,   5299,
      5402,   5497,   5584,   5664,   5733,   5796,   5849,   5896,   5936,   5966,
      5990,   6003,   6016,   6016,   6013,   6000,   5981,   5953,   5922,   5881,
      5838,   5788,   5733,   5669,   5603,   5530,   5456,   5377,   5291,   5202,
      5108,   5013,   4915,   4818,   4718,   4611,   4505,   4399,   4288,   4182,
      4071,   3964,   3856,   3752,   3648,   3546,   3445,   3348,   3254,   3165,
      3079,   2998,   2923,   2855,   2788,   2731,   2675,   2629,   2592,   2562,
      2534,   2517,   2510,   2506,   2514,   2523,   2545,   2577,   2614,   2660,
      2712,   2773,   2838,   2909,   2988,   3068,   3153,   3250,   3348,   3441,
      3545,   3648,   3752,   3852,   3956,   4058,   4155,   4247,   4333,   4412,
      4492,   4555,   4614,   4659,   4698,   4718,   4728,   4724,   4702,   4668,
      4611,   4540,   4449,   4336,   4207,   4051,   3875,   3680,   3459,   3222,
      2953,   2668,   2354,   2022,   1661,   1279,    877,    454,      9,   -457,
      -943,  -1449,  -1974,  -2510,  -3070,  -3639,  -4220,  -4811,  -5414,  -6025,
     -6641,  -7262,  -7887,  -8512,  -9135,  -9756, -10368, -10974, -11569, -12155,
    -12723, -13281, -13813, -14334, -14825, -15293, -15736, -16149, -16535, -16887,
    -17206, -17493, -17740, -17953, -18120, -18252, -18343, -18393, -18398, -18359,
    -18276, -18148, -17977, -17760, -17505, -17199, -16854, -16462, -16032, -15556,
    -15042, -14488, -13898, -13270, -12611, -11916, -11193, -10437,  -9654,  -8844,
     -8017,  -7162,  -6296,  -5410,  -4509,  -3602,  -2682,  -1759,   -828,    100,
      1023,   1945,   2860,   3771,   4665,   5543,   6406,   7253,   8078,   8875,
      9654,  10401,  11123,  11810,  12469,  13090,  13679,  14228,  14746,  15220,
     15660,  16055,  16416,  16729,  17006,  17239,  17434,  17581,  17692,  17762,
     17794,  17785,  17736,  17651,  17527,  17367,  17173,  16952,  16691,  16401,
     16081,  15736,  15361,  14962,  14543,  14100,  13639,  13162,  12663,  12155,
     11629,  11098,  10555,  10006,   9448,   8890,   8325,   7759,   7195,   6632,
      6074,   5521,   4972,   4429,   3899,   3376,   2864,   2360,   1872,   1394,
       932,    483,     50,   -368,   -767,  -1149,  -1518,  -1870,  -2199,  -2516,
     -2812,  -3096,  -3356,  -3602,  -3826,  -4034,  -4231,  -4405,  -4566,  -4707,
     -4833,  -4950,  -5043,  -5126,  -5193,  -5247,  -5289,  -5315,  -5334,  -5336,
     -5332,  -5310,  -5282,  -5249,  -5200,  -5148,  -5085,  -5011,  -4939,  -4856,
     -4767,  -4670,  -4577,  -4474,  -4366,  -4258,  -4151,  -4038,  -3927,  -3812,
     -3697,  -3582,  -3465,  -3356,  -3244,  -3135,  -3031,  -2927,  -2831,  -2731,
     -2638,  -2555,  -2469,  -2393,  -2321,  -2260,  -2200,  -2148,  -2102,  -2063,
     -2034,  -2013,  -1998,  -1995,  -1995,  -2006,  -2026,  -2054,  -2085,  -2132,
     -2186,  -2249,  -2315,  -2391,  -2477,  -2567,  -2669,  -2775,  -2881,  -2998,
     -3122,  -3252,  -3387,  -3522,  -3663,  -3806,  -3951,  -4097,  -4247,  -4396,
     -4542,  -4687,  -4831,  -4972,  -5110,  -5239,  -5369,  -5488,  -5605,  -5707,
     -5807,  -5896,  -5974,  -6042,  -6102,  -6146,  -6179,  -6203,  -6209,  -6202,
     -6181,  -6146,  -6100,  -6038,  -5961,  -5866,  -5762,  -5642,  -5504,  -5358,
     -5195,  -5021,  -4833,  -4635,  -4418,  -4199,  -3966,  -3726,  -3476,  -3218,
     -2959,  -2695,  -2423,  -2148,  -1872,  -1596,  -1320,  -1047,   -776,   -513,
      -257,     -7,    237,    472,    693,    899,   1093,   1277,   1436,   1581,
      1707,   1820,   1909,   1978,   2030,   2054,   2056,   2037,   1991,   1926,
      1837,   1724,   1589,   1425,   1245,   1038,    810,    561,    291,     -1,
      -305,   -635,   -980,  -1340,  -1711,  -2098,  -2495,  -2903,  -3320,  -3743,
     -4169,  -4601,  -5037,  -5467,  -5896,  -6326,  -6743,  -7160,  -7563,  -7959,
     -8343,  -8708,  -9061,  -9396,  -9712, -10010, -10283, -10537, -10765, -10971,
    -11147, -11299, -11417, -11510, -11581, -11614, -11621, -11599, -11549, -11464,
    -11356, -11215, -11047, -10850, -10627, -10375, -10101,  -9804,  -9485,  -9137,
     -8773,  -8388,  -7983,  -7568,  -7136,  -6691,  -6237,  -5771,  -5299,  -4824,
     -4338,  -3856,  -3372,  -2894,  -2417,  -1945,  -1479,  -1027,   -587,   -159,
       255,    654,   1030,   1394,   1735,   2048,   2345,   2614,   2859,   3079,
      3268,   3435,   3571,   3674,   3752,   3797,   3819,   3808,   3767,   3700,
      3602,   3470,   3318,   3131,   2922,   2684,   2425,   2137,   1828,   1498,
      1144,    769,    374,    -31,   -463,   -902,  -1357,  -1826,  -2306,  -2796,
     -3292,  -3793,  -4307,  -4820,  -5336,  -5853,  -6372,  -6890,  -7401,  -7915,
     -8419,  -8924,  -9417,  -9906, -10385, -10854, -11312, -11760, -12196, -12626,
    -13036, -13435, -13822, -14195, -14549, -14892, -15222, -15532, -15832, -16118,
    -16381, -16631, -16867, -17095, -17304, -17501, -17681, -17848, -18005, -18146,
    -18274, -18391, -18498, -18593, -18674, -18752, -18815, -18871, -18916, -18953,
    -18984, -19006, -19025, -19034, -19040, -19040, -19034, -19023, -19010, -18993,
    -18971, -18953, -18929, -18901, -18875, -18847, -18825, -18795, -18767, -18745,
    -18721, -18697, -18678, -18660, -18645, -18634, -18630, -18626, -18624, -18630,
    -18639, -18652, -18671, -18695, -18728, -18765, -18806, -18860, -18916, -18982,
    -19049, -19127, -19210, -19305, -19405, -19518, -19631, -19754, -19883, -20026,
    -20171, -20325, -20488, -20660, -20833, -21014, -21200, -21393, -21593, -21797,
    -22010, -22223, -22440, -22655, -22882, -23106, -23340, -23564, -23798, -24024,
    -24254, -24480, -24704, -24925, -25142, -25355, -25561, -25761, -25952, -26139,
    -26319, -26486, -26644, -26790, -26927, -27052, -27163, -27263, -27348, -27419,
    -27480, -27522, -27548, -27561, -27561, -27545, -27511, -27463, -27406, -27326,
    -27231, -27128, -27003, -26870, -26727, -26569, -26401, -26217, -26028, -25832,
    -25624, -25407, -25190, -24969, -24739, -24511, -24280, -24046, -23823, -23595,
    -23375, -23160, -22948, -22748, -22557, -22375, -22207, -22049, -21908, -21780,
    -21673, -21578, -21504, -21446, -21409, -21393, -21396, -21420, -21469, -21534,
    -21624, -21736, -21873, -22025, -22205, -22405, -22620, -22854, -23113, -23384,
    -23671, -23979, -24300, -24634, -24977, -25331, -25692, -26060, -26432, -26807,
    -27183, -27560, -27929, -28294, -28657, -29002, -29341, -29666, -29966, -30254,
    -30521, -30765, -30988, -31183, -31344, -31477, -31583, -31648, -31680, -31674,
    -31628, -31542, -31418, -31253, -31038, -30782, -30485, -30137, -29747, -29310,
    -28826, -28296, -27721, -27098, -26438, -25724, -24975, -24179, -23340, -22463,
    -21545, -20594, -19602, -18580, -17527, -16440, -15328, -14187, -13025, -11840,
    -10639,  -9417,  -8182,  -6934,  -5673,  -4411,  -3144,  -1872,   -602,    667
};


// ================================================================================================
//
// Array of descriptors used to access pre-defined wave-tables stored in flash PM
// The patch parameter 'WaveTableNumber' is an index into this array.
//
// typedef struct Flash_Wave_Table_Descriptor
// {
//   uint16  Size;          // Table size, samples
//   float   FreqDiv;       // Osc Freq Divider
//   int16  *Address;       // Address of wave-table data
// 
// } FlashWaveTable_t;

const  FlashWaveTable_t  g_FlashWaveTableDef[] =
{
    {   // ID# 0:  <!> Reserved for RAM-based "user" wave-table
        0,
        1.00,
        (int16 *) NULL  
    },
    
    {   // ID# 1: Pure sinewave at fundamental freq.
        1260,
        1.00,
        (int16 *) g_sinewave
    },
  
    {   // ID# 2: Square wave, lightly anti-alias filtered -- classic wind pipe tone
        1260,
        1.00,
        (int16 *) square_wave 
    },
    
    {   // ID# 3: Sawtooth wave, lightly anti-alias filtered -- buzzy tone (violin/cello?)
        1260,
        1.00,
        (int16 *) sawtooth_wave 
    },

    {   // ID# 4: reserved  (formerly "rounded_square")
        1260,
        1.00,
        (int16 *) square_wave
    },
    
    {   // ID# 5: Blunt sawtooth wave -- dull, mellow sound  -- replace ??? ********************
        1260,
        1.00,
        (int16 *) blunt_sawtooth
    },
    
    {   // ID# 6: Clean bright flute -- flinty, metallic, modulated tone
        1260,
        1.00,
        (int16 *) clean_bright_flute  
    },
    
    {   // ID# 7: reserved
        1260,
        3.00,
        (int16 *) g_sinewave
    },
    
    {   // ID# 8: reserved
        1260,
        4.00,
        (int16 *) g_sinewave
    },
    
    {   // ID# 9: Alto saxophone  -- reedy, boxy sound in low register (used in patch?)
        1260,
        2.00,  // take it down an octave!
        (int16 *) alto_saxophone
    },
    
    {   // ID# 10: Psychedelic oboe -- very complex inter-modulated harmonics (nice)
        1260,
        2.00,  // take it down an octave!
        (int16 *) psychedelic_oboe
    },
    
    {   // ID# 11: Electric clarinet -- thin squeaky or boxy, depending on pitch (nice)
        1260,
        2.00,  // take it down an octave!
        (int16 *) electric_clarinet
    },
    
    {   // ID# 12: Mellow pipe #1 -- muted mellow woodwind (good - keep)
        1260,
        1.00,
        (int16 *) mellow_pipe_v1
    },
    
    {   // ID# 13: Recorder (drawbars: 00 8271 200) -- classic mostly-odd harmonic spectrum
        1260,
        2.0,
        (int16 *) recorder_008271200
    },
    
    {   // ID# 14: Rock organ 8888 (drawbars: 88 8800 000) -- simple electric organ
        1260,
        1.0,      // pitch offset = +1 octave (2x fo)
        (int16 *) hammond_rock_8888   
    },
    
    {   // ID# 15: Rock organ 8080 (drawbars: 80 8000 000) -- very mellow organ
        1260,
        2.0,
        (int16 *) hammond_rock_8080   
    },
    
    {   // ID# 16: Rock organ 0808 (drawbars: 08 0800 000) -- ring modulator effect
        1260,
        2.0,
        (int16 *) hammond_rock_0808  
    },

    {   // ID# 17: Jazz organ #1  (drawbars: 40 6160 040) 
        1260,
        2.0,  
        (int16 *) jazz_organ_406160040
    },
    
    {   // ID# 18: Jazz organ #2  (drawbars: 30 5060 040) 
        1260,
        2.0,  
        (int16 *) jazz_organ_305060040
    },
    
    {   // ID# 19: Glockenspiel (drawbars: 00 8360 400) -- timbre similar to recorder!
        1260,
        2.0, 
        (int16 *) glockenspiel_008360400
    },
    
    {   // ID# 20: Pink Floyd organ (drawbars: 85 0005 000) -- rich complex, flutey sound
        1260,
        1.00,     // pitch offset = + 1 octave (2x fo)
        (int16 *) pink_floyd_organ_850005  
    },
    
    {   // ID# 21: Theatre Organ (drawbars: 87 8656 463) -- very full organ (good)
        1260,
        2.0, 
        (int16 *) theatre_organ_878656463  
    },
    
    {   // ID# 22: BAUER organ (drawbars: 00 8008 432) -- rich, bright organ sound (keep)
        1260,
        2.00,  
        (int16 *) bauer_organ_008008432
    },
    
    {   // ID# 23: Mellow reed (drawbars: 00 8042 660) -- pleasant, rounded, oboe-ish (keep)
        1260,
        2.00,
        (int16 *) mellow_reed_008042660 
    },
/*    
    {   // ID# 24: reserved
        1260,
        2.00,  
        (int16 *) g_sinewave
    }
*/
};


// Function returns the ID number of the highest wave-table defined by the descriptor
// array g_FlashWaveTableDef[], above.  This number is an index into the array.
// Note:  Special case:  ID == 0 references the "user" wave-table buffer in RAM.
//
int  GetHighestWaveTableID()
{
    return  sizeof(g_FlashWaveTableDef) / sizeof(g_FlashWaveTableDef[0]) - 1;
}

// *** end of file ***
