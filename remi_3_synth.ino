/**
   ================================================================================================

   Module:       remi_teensy_synth

   Overview:     REMI (v3) Teensy3.2 built-in sound synthesizer module.

   Author:       M.J.Bauer, Copyright 2020++  All rights reserved

   Reference:    www.mjbauer.biz/Build_the_REMI_by_MJB.htm

   ================================================================================================
*/
#include "remi_3_synth.h"

fixed_t  ReverbDelayLine[REVERB_DELAY_MAX_SIZE];  // fixed-point samples

IntervalTimer  sampleTimer;

PatchParamTable_t  g_Patch;        // active (working) patch parameters

int32  g_debugValue;  // (Temp. for debug)

// -----------  Synth process variables  -----------------------------------------------
//
static uint16   m_Osc1WaveTableSize;      // Number of samples in OSC1 wave-table
static uint16   m_Osc2WaveTableSize;      // Number of samples in OSC2 wave-table
static int16   *m_WaveTable1;             // Pointer to OSC1 wave-table
static int16   *m_WaveTable2;             // Pointer to OSC2 wave-table
static float    m_Osc1FreqDiv;            // OSC1 frequency divider
static float    m_Osc2FreqDiv;            // OSC2 frequency divider
static fixed_t  m_Osc1StepInit;           // Initial value of v_Osc1Step at Note-On
static fixed_t  m_Osc2StepInit;           // Initial value of v_Osc2Step at Note-On
static fixed_t  m_OscFreqMultiplier;      // Pitch-bend factor (range: 0.5 ~ 2.0)
static int32    m_LFO_Step;               // LFO "phase step" (fixed-point 24:8 bit format)
static fixed_t  m_LFO_output;             // LFO output signal, normalized, bipolar (+/-1.0)

static fixed_t  m_PressureLevel;          // Expression/Pressure level, norm.
static fixed_t  m_ModulationLevel;        // Modulation level, normalized
static uint16   m_PitchBendRange;         // Pitch-Bend range, cents (0..1200) -- todo
static fixed_t  m_PitchBendFactor;        // Pitch-Bend factor, normalized
static uint8    m_PitchBendControl;       // Pitch-Bend control mode (Off, PBmsg, CC01, CC02)
static uint8    m_VibratoControl;         // 0:None, 1:CC1(Mod.Lvr), 3:Auto, 4:Asymm.
static fixed_t  m_RampOutput;             // Vibrato Ramp output level, normalized (0..1)
static fixed_t  m_AmpldEnvOutput;         // Amplitude envelope output (0 ~ 0.9995)
static short    m_ContourEnvSegment;      // Mixer transient/contour phase (state)
static fixed_t  m_ContourEnvOutput;       // Mixer contour output, normalized (0..1)

static fixed_t  m_AttackVelocity;         // Attack Velocity, normalized (0 ~ 0.999)
static BOOL     m_TriggerAttack;          // Signal to put ampld envelope into attack
static BOOL     m_TriggerRelease;         // Signal to put ampld envelope into release
static BOOL     m_ContourEnvTrigger;      // Signal to start mixer transient/contour
static BOOL     m_ContourEnvFinish;       // Signal to end mixer transient/contour
static bool     m_LegatoNoteChange;       // Signal Legato note change to Vibrato func.
static bool     m_Note_ON;                // TRUE if Note ON, ie. "gated", else FALSE

static uint8    m_FilterAtten_pc;         // Filter input atten/gain (%)
static uint8    m_FilterGain_x10;         // Filter output gain x10 (1..250)
static uint8    m_NoiseGain_x10;          // Noise filter gain x10 (1..250)
static fixed_t  m_FiltCoeff_c[110];       // Bi-quad filter coeff. c  (a1 = -c)
static fixed_t  m_FiltCoeff_a2;           // Bi-quad filter coeff. a2
static fixed_t  m_FiltCoeff_b0;           // Bi-quad filter coeff. b0  (b2 = -b0)
static int      m_FilterIndex;            // Index into LUT: m_FiltCoeff_c[]

static int      m_RvbDelayLen;            // Reverb. delay line length (samples)
static fixed_t  m_RvbDecay;               // Reverb. decay factor
static uint16   m_RvbAtten;               // Reverb. attenuation factor (0..127)
static uint16   m_RvbMix;                 // Reverb. wet/dry mix ratio (0..127)

// Audio Sampling Routine variables
//
volatile uint8    v_SynthEnable;      // Signal to enable synth sampling routine
volatile int32    v_Osc1Angle;        // sample pos'n in wave-table, OSC1 [16:16]
volatile int32    v_Osc2Angle;        // sample pos'n in wave-table, OSC2 [16:16]
volatile int32    v_Osc1Step;         // sample pos'n increment, OSC1 [16:16 fixed-pt]
volatile int32    v_Osc2Step;         // sample pos'n increment, OSC2 [16:16 fixed-pt]
volatile uint16   v_Mix2Level;        // Mixer input_2 level (0..1000)
volatile fixed_t  v_NoiseLevel;       // Noise level control (normalized)
volatile fixed_t  v_OutputLevel;      // Audio output level control (normalized)
volatile fixed_t  v_coeff_b0;         // Bi-quad filter coeff b0 (active)
volatile fixed_t  v_coeff_b2;         // Bi-quad filter coeff b2 (active)
volatile fixed_t  v_coeff_a1;         // Bi-quad filter coeff a1 (active)
volatile fixed_t  v_coeff_a2;         // Bi-quad filter coeff a2 (active)


// Look-up table giving frequencies of notes on the chromatic scale.
// The array covers a 9-octave range beginning with C0 (MIDI note number 12),
// up to C9 (120).  Subtract 12 from MIDI note number to get table index.
// Table index range:  [0]..[108]
//
const  float  m_NoteFrequency[] =
{
  // C0      C#0       D0      Eb0       E0       F0      F#0       G0
  16.3516, 17.3239, 18.3540, 19.4455, 20.6017, 21.8268, 23.1247, 24.4997,
  // Ab0      A0      Bb0       B1       C1      C#1       D1      Eb1
  25.9566, 27.5000, 29.1353, 30.8677, 32.7032, 34.6478, 36.7081, 38.8909,
  // E1       F1      F#1       G1      Ab1       A1      Bb1       B1
  41.2034, 43.6535, 46.2493, 48.9994, 51.9131, 55.0000, 58.2705, 61.7354,
  // C2      C#2       D2      Eb2       E2       F2      F#2       G2
  65.4064, 69.2957, 73.4162, 77.7817, 82.4069, 87.3071, 92.4986, 97.9989,
  // Ab2      A2      Bb2       B2       C3      C#3       D3      Eb3
  103.826, 110.000, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563,
  // E3       F3      F#3       G3      Ab3       A3      Bb3       B3
  164.814, 174.614, 184.997, 195.998, 207.652, 220.000, 233.082, 246.942,
  // C4      C#4       D4      Eb4       E4       F4      F#4       G4
  261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995,
  // Ab4      A4      Bb4       B4       C5      C#5       D5      Eb5
  415.305, 440.000, 466.164, 493.883, 523.251, 554.365, 587.330, 622.254,
  // E5       F5      F#5       G5      Ab5       A5      Bb5       B5
  659.255, 698.456, 739.989, 783.991, 830.609, 880.000, 932.328, 987.767,
  // C6      C#6       D6      Eb6       E6       F6      F#6       G6
  1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98,
  // Ab6      A6      Bb6       B6       C7      C#7       D7      Eb7
  1661.22, 1760.00, 1864.66, 1975.53, 2093.00, 2217.46, 2349.32, 2489.02,
  // E7       F7      F#7       G7      Ab7       A7      Bb7       B7
  2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 3951.07,
  // C8      C#8       D8      Eb8       E8       F8      F#8       G8
  4186.01, 4434.92, 4698.64, 4978.04, 5274.04, 5587.66, 5919.92, 6271.92,
  // Ab8      A8      Bb8       B8       C9
  6644.88, 7040.00, 7458.62, 7902.14, 8372.02
};


/*`````````````````````````````````````````````````````````````````````````````````````````````````
   Function:  Initialize synth audio variables and Timer ISR for audio DAC operation.
*/
void  SynthAudioInit(void)
{
  GLOBAL_INT_DISABLE();
  v_SynthEnable = 0;
  m_Note_ON = 0;
  analogWriteRes(12);        // set DAC resolution to 12 bits
  
  sampleTimer.begin(AudioSamplingRoutine, 25);   // 25us period -> 40kHz sample rate
  sampleTimer.priority(1);

  // Calculate reverb constants
  m_RvbDelayLen = (int) (REVERB_LOOP_TIME_SEC * SAMPLE_RATE_HZ);
//  float rvbDecayFactor = (float) REVERB_LOOP_TIME_SEC / REVERB_DECAY_TIME_SEC;
//  m_RvbDecay = FloatToFixed( powf(0.001f, rvbDecayFactor) );
  m_RvbDecay = FloatToFixed( 0.87 );
  m_RvbAtten = 102;  // default setting, approx 80%
  m_RvbMix = 19;  // approx 15%
  
  GLOBAL_INT_ENABLE();  // Let 'er rip, Boris!
}


/*`````````````````````````````````````````````````````````````````````````````````````````````````
   Function:     Prepare REMI synth tone generator to play a note.

   Overview:     This function must be called following any change in the synth patch
                 configuration or other synth parameter, before playing a note.

   Note:         On entry, and exit, the signal v_SynthEnable is set False.
*/
void  SynthPrepare()
{
  float   res, res_sq, freq_rat;
  float   pi_2 = 2.0f * 3.14159265f;
  int     idx;
  int32   oscFreqLFO;  // 24:8 bit fixed-point

  v_SynthEnable = 0;    // Disable the synth tone-generator
  m_Note_ON = FALSE;    // no note playing

  oscFreqLFO = (((int) g_Patch.LFO_Freq_x10) << 8) / 10;  // Fixed-point value (24:8 bits)
  m_LFO_Step = (oscFreqLFO * SINE_WAVE_TABLE_SIZE) / 1000;  // LFO sample rate is 1000Hz.

  m_FilterAtten_pc = (uint8) (FILTER_INPUT_ATTEN * 100);
  m_FilterGain_x10 = (uint8) (FILTER_OUTPUT_GAIN * 10);
  m_NoiseGain_x10 = (uint8) (NOISE_FILTER_GAIN * 10);

  WaveTableSelect(1, g_Patch.Osc1WaveTable);
  WaveTableSelect(2, g_Patch.Osc2WaveTable);

  m_OscFreqMultiplier = IntToFixedPt(1);
  m_LFO_output = 0;
  m_ContourEnvOutput = IntToFixedPt(g_Patch.ContourStartLevel) / 100;

  // Find coefficients for bi-quad filter according to patch param (FilterResonance)
  res = (float) g_Patch.FilterResonance / 10000;   // range 0 ~ 0.9999
  res_sq = res * res;
  m_FiltCoeff_a2 = FloatToFixed(res_sq);
  m_FiltCoeff_b0 = FloatToFixed(0.5f - (res_sq / 2.0f));

  // Coeff a1 (a1 = -c) is both resonance and frequency dependent...
  for (idx = 0 ; idx <= 108 ; idx++)    // populate LUT
  {
    freq_rat = m_NoteFrequency[idx] / SAMPLE_RATE_HZ;   // Fr = Fc / Fs
    m_FiltCoeff_c[idx] = FloatToFixed(2.0 * res * cosf(pi_2 * freq_rat));
  }

  // Initial values for real-time control variables, in case modulation disabled.
  v_NoiseLevel = 0;
  v_OutputLevel = IntToFixedPt( 1 ) / 2;
}


/*`````````````````````````````````````````````````````````````````````````````````````````````````
   Function:     Select (activate) a wave-table for a given synth oscillator.
                 This then becomes the "active" wave-table, over-riding the table
                 selected by any prior call to SynthPatchSelect().

   Entry args:   osc_num = oscillator assigned to wave-table, 1 -> OSC1, 2 -> OSC2
                 wave_id = ID number of wave-table, range 1..250
*/
void  WaveTableSelect(uint8 osc_num, uint8 wave_id)
{
  if (wave_id <= GetHighestWaveTableID())  // Flash-based wave-table
  {
    if (osc_num == 1)
    {
      m_Osc1WaveTableSize = g_FlashWaveTableDef[wave_id].Size;
      m_Osc1FreqDiv = g_FlashWaveTableDef[wave_id].FreqDiv;
      m_WaveTable1 = (int16 *) g_FlashWaveTableDef[wave_id].Address;
    }
    else if (osc_num == 2)
    {
      m_Osc2WaveTableSize = g_FlashWaveTableDef[wave_id].Size;
      m_Osc2FreqDiv = g_FlashWaveTableDef[wave_id].FreqDiv;
      m_WaveTable2 = (int16 *) g_FlashWaveTableDef[wave_id].Address;
    }
  }
}


/*`````````````````````````````````````````````````````````````````````````````````````````````````
   Function:     Copies patch parameters from a given pre-defined patch table in flash
                 program memory to the "active" patch parameter table in data memory.
                 If the given patch ID number cannot be found, the function will copy
                 parameters from a "default" patch (idx == 0) and return ERROR (-1).

   Entry args:   patchNum = ID number of patch parameter table to be set up.
                 <!> This is *not* an index into the patch definitions array, g_PatchProgram[].

   Return val:   ERROR (-1) if the given patch ID cannot be found, else OK (0).
*/
short  SynthPatchSelect(int patchNum)
{
  short  status = 0;
  int    i;
  int    patchCount = GetNumberOfPatchesDefined();

  if (patchNum != 0)
  {
    for (i = 0;  i < patchCount;  i++)
    {
      if (g_PatchProgram[i].PatchNumber == patchNum)  break;
    }

    if (i >= patchCount)   // patchNum not found -- load default patch
    {
      i = 0;
      status = ERROR;
    }

    memcpy(&g_Patch, &g_PatchProgram[i], sizeof(PatchParamTable_t));
  }

  // Ensure minimum values are assigned to envelope transition times...
  // (except for peak-hold time, which may be zero)
  if (g_Patch.AmpldEnvAttack_ms < 5) g_Patch.AmpldEnvAttack_ms = 5;
  if (g_Patch.AmpldEnvDecay_ms < 5) g_Patch.AmpldEnvDecay_ms = 5;
  if (g_Patch.AmpldEnvRelease_ms < 5) g_Patch.AmpldEnvRelease_ms = 5;
  if (g_Patch.ContourDelay_ms < 5) g_Patch.ContourDelay_ms = 5;
  if (g_Patch.ContourRamp_ms < 5) g_Patch.ContourRamp_ms = 5;
  if (g_Patch.VibratoRamp_ms < 5) g_Patch.VibratoRamp_ms = 5;

  SynthPrepare();

  return  status;
}


/*
   Function:     If a note is already playing, perform a Legato note change;
                 otherwise initiate a new note.

   Entry args:   noteNum  = MIDI standard note number, range: 12 ~ 120 (C0..C9),
                            e.g. note #60 = C4 = middle-C.
                 velocity = attack velocity (usage dependent on synth settings)

   When a new note is initiated, the function prepares the synth wave-table oscillators
   to play the given note, sets filter characteristics according to patch parameters,
   then triggers the envelope shapers to enter the 'Attack' phase.
*/
void  SynthNoteOn(uint8 noteNum, uint8 velocity)
{
  if (!m_Note_ON)    // Note OFF -- Initiate a new note...
  {
    SynthNoteChange(noteNum);  // Set OSC1 and OSC2 frequencies, etc

    m_AmpldEnvOutput = 0;   // Zero the ampld envelope output signal

    // A square-law curve is applied to velocity
    m_AttackVelocity = IntToFixedPt((int) velocity) / 128;  // normalized
    m_AttackVelocity = MultiplyFixed(m_AttackVelocity, m_AttackVelocity);  // squared

    GLOBAL_INT_DISABLE();
    v_Osc1Angle = 0;
    v_Osc2Angle = 0;
    // Initialize wave mixer input levels (range 0..1024)
    v_Mix2Level = (1000 * (int) g_Patch.MixerOsc2Level) / 100;
    GLOBAL_INT_ENABLE();

    m_LegatoNoteChange = 0;    // Not a Legato event
    m_TriggerAttack = 1;       // Let 'er rip, Boris
    m_ContourEnvTrigger = 1;
	  v_SynthEnable = 1;         // in case not already enabled
    m_Note_ON = TRUE;
  }
  else  // Note already playing -- Legato note change
  {
    SynthNoteChange(noteNum);  // Adjust OSC1 and OSC2 frequencies
    m_LegatoNoteChange = 1;        // Signal Note-Change event (for vibrato fn)
  }
}


/*
   Function:     Set the pitch of a note to be initiated, or change pitch of the note
                 in progress, without affecting the amplitude envelope (i.e. no re-attack).
                 This function may be used where a "legato" effect is required.
                 (See also: SynthNoteOn() function.)

   Entry args:   noteNum = MIDI standard note number. (Note #60 = C4 = middle-C.)
                 The REMI synth supports note numbers in the range: 12 (C0) to 108 (C8).

   The actual perceived pitch depends on the Frequency Divider values and the dominant
   partial(s) in the waveform(s). Normally, the Osc.Freq.Div parameter value is chosen to
   match the wave-table, so that the perceived pitch corresponds to the MIDI note number.
*/
void  SynthNoteChange(uint8 noteNum)
{
  float   osc1Freq, osc2Freq;
  fixed_t osc1Step, osc2Step;
  float   osc2detune;      // ratio:  osc2Freq / osc1Freq;
  fixed_t detuneNorm;
  int     filterCorner;    // unit = MIDI note number (semitone)
  int     cents;

  // Ensure note number is within synth range (12 ~ 108)
  while (noteNum > 108)  {
    noteNum -= 12;  // too high
  }

  while (noteNum < 12)  {
    noteNum += 12;   // too low
  }

  // Convert MIDI note number to frequency (Hz);  apply OSC1 freq.divider param.
  osc1Freq = m_NoteFrequency[noteNum - 12] / m_Osc1FreqDiv;

  // Calculate detune factor as a fraction of an octave
  cents = g_Patch.Osc2Detune % 1200;     // signed
  detuneNorm = (IntToFixedPt(1) * cents) / 1200;  // range +/-1.000
  osc2detune = FixedToFloat(Base2Exp(detuneNorm));
  osc2Freq = osc1Freq * osc2detune;      // Apply OSC2 detune factor
  osc2Freq = osc2Freq / m_Osc2FreqDiv;   // Apply OSC2 Freq.Divider parameter

  // Initialize oscillator variables for use in audio ISR
  osc1Step = (int32)((osc1Freq * m_Osc1WaveTableSize * 65536) / SAMPLE_RATE_HZ);
  osc2Step = (int32)((osc2Freq * m_Osc2WaveTableSize * 65536) / SAMPLE_RATE_HZ);
  
  m_Osc1StepInit = osc1Step;   // Needed for Osc FM (vibrato, pitch-bend, etc)
  m_Osc2StepInit = osc2Step;

  // Calculate filter corner freq (pitch offset) for new note...
  if (g_Patch.FilterNoteTrack)  // case 1: Note Tracking enabled
  {
    filterCorner = noteNum + g_Patch.FilterFrequency;  // MIDI note, variable
    if (filterCorner > 120)  filterCorner = 120;       // Max at C9 (~8 kHz)
    m_FilterIndex = filterCorner - 12;
  }
  else  // case 2: Note Tracking disabled
  {
    filterCorner = g_Patch.FilterFrequency;     // MIDI note, constant
    if (filterCorner < 12)  filterCorner = 12;  // Min at C0 (~16 Hz)
    m_FilterIndex = filterCorner - 12;
  }
  
  // Use Fc = 16 Hz (minimum) for pitched noise option
  if (g_Patch.NoiseMode & NOISE_PITCHED)  m_FilterIndex = 0;  
  
  GLOBAL_INT_DISABLE(); 
  v_Osc1Step = osc1Step;
  v_Osc2Step = osc2Step;
  // Set filter coefficient values to be applied in the audio ISR
  v_coeff_b0 = m_FiltCoeff_b0;
  v_coeff_b2 = 0 - m_FiltCoeff_b0;      // b2 = -b0
  v_coeff_a1 = 0 - m_FiltCoeff_c[m_FilterIndex];  // a1 = -c
  v_coeff_a2 = m_FiltCoeff_a2;
  GLOBAL_INT_ENABLE();
}


/*
   Function:     Set the "Pressure Level" according to a given data value.
                 Equivalent to MIDI Control Change message (CC# = 02, 07 or 11).

   Entry args:   data14 = MIDI expression/pressure value (14 bits, unsigned).

   Output:       (fixed_t) m_PressureLevel = normalized pressure level (0..+1.0)
*/
void   SynthExpression(unsigned data14)
{

  // Apply square law transfer function
  uint32  ulval = ((uint32) data14 * data14) / 16384;  
  fixed_t level = ulval << 6;  // convert to fixed-point fraction (20 bits)
  if (level > FIXED_MAX_LEVEL) level = FIXED_MAX_LEVEL;  // clip at 0.99999

  m_PressureLevel = level;  // process variable
}


/*
   Function:     End the note playing, if any.

   The function puts envelope shapers into the 'Release' phase. The note will be
   terminated by the synth process (B/G task) when the release time expires, or if
   a new note is initiated prior.
*/
void  SynthNoteOff()
{
  m_TriggerRelease = 1;
  m_ContourEnvFinish = 1;
  m_Note_ON = FALSE;
}


/*
   Function:    Modify pitch of note in progress according to Pitch-Bend data value.

   Entry arg:   data14 = signed integer representing Pitch Bend lever position,
                         in the range +/-8000 (14 LS bits).  Centre pos'n is 0.

   Output:      m_PitchBendFactor, which is processed by the real-time synth function
                OscFreqModulation() while a note is in progress.
*/
void   SynthPitchBend(int data14)
{
  // Scale lever pos'n (arg) value according to operational variable m_PitchBendRange.
  // PitchBendRange may be up to 1200 cents (i.e. 1 octave maximum).
  int  posnScaled = (data14 * m_PitchBendRange) / 1200;

  // Convert to 20-bit *signed* fixed-point fraction  (13 + 7 = 20 bits)
  m_PitchBendFactor = (fixed_t) (posnScaled << 7);
}


/*
   Function:     Control synth effect(s) according to MIDI Modulation data (CC#1);
                 e.g. vibrato depth, noise level, filter freq., etc.
                 The effect to be controlled is a function of the synth patch^.

   Entry args:   data14 = unsigned integer representing Modulation Lever position;
                          range 0..16383 (= 2^14 - 1).

   Output:       m_ModulationLevel, normalized fixed-pt number in the range 0..+1.0.

*/
void   SynthModulation(unsigned data14)
{
  if (data14 < 16384) m_ModulationLevel = (fixed_t) ((uint32) data14 << 6);
  else   m_ModulationLevel = 0;
}


/*
   Function:     Set Synth Vibrato control mode.

   Entry arg:    mode =  0:Disable, 1:Effect Switch, 2:CC01 (Modulation), 3:Automatic
                         4:Auto-Asymmetric (modulate OSC1 only)

   Note 1:       Vibrato mode is not a patch parameter;  it is set by calling this function.

   Note 2:       Pitch Bend and Vibrato are mutually exclusive in the REMI synth...
                 if vibrato is enabled (mode != 0), then Pitch Bend is inhibited, i.e.
                 Pitch Bend messages will have no effect.
*/
void  SynthVibratoModeSet(unsigned mode)
{
  m_VibratoControl = mode;
}


/*
   Function:     Set Synth Pitch Bend control mode.

   Entry arg:    mode =  0:Disable, 1:Pitch-Bend message, 2:CC01 (Modulation), 3:CC02 (Breath)

   Note 1:       Pitch Bend mode is not a patch parameter;  it is set by calling this function.

   Note 2:       Pitch Bend and Vibrato are mutually exclusive in the REMI synth...
                 if vibrato is enabled (mode != 0), then Pitch Bend is inhibited, i.e.
                 Pitch Bend messages will have no effect.
*/
void  SynthPitchBendModeSet(unsigned mode)
{
  m_PitchBendControl = mode;
}


/*
   Function:     Set Synth Reverb Level.

   Entry arg:    level_pc =  Reverb wet/dry mix (percent wet)
   
   Output:       m_RvbMix, range 0..128
*/
void  SynthReverbLevelSet(unsigned level_pc)
{
  if (level_pc <= 100)  m_RvbMix = (level_pc * 128) / 100;  // 0..128
}

/*
   Function:     Set Synth Reverb Attenuation Factor.

   Entry arg:    atten_pc =  Reverb Attenuation Factor (percent)
   
   Output:       m_RvbAtten, range 0..128
*/
void  SynthReverbAttenSet(unsigned atten_pc)
{
  if (atten_pc <= 100)  m_RvbAtten = (atten_pc * 128) / 100;  // 0..128
}


/*`````````````````````````````````````````````````````````````````````````````````````````````````
   Function:  SynthProcess()

   Overview:  Periodic background task called at 1ms intervals which performs most of the
              real-time sound synthesis computations, except those which need to be executed
              at the PCM audio sampling rate; these are done by the Timer ISR.

   This task implements the envelope shapers, oscillator pitch bend and vibrato (LFO), mixer
   input ratio control, DSP filter frequency control, audio output amplitude control, etc.

   Some processing is done at 1ms intervals (1000Hz), while other parts are done at longer
   intervals, e.g. 5ms/200Hz, where timing resolution is not so critical and/or more intensive
   computation, e.g. floating point arithmetic, is needed. Speed-critical computations use
   32-bit fixed-point arithmetic.
*/
void   SynthProcess()
{
  static  int   count5ms;

  AmpldEnvelopeShaper();
  ContourEnvelopeShaper();
  LowFrequencyOscillator();
  AudioLevelController();

  if (++count5ms == 5)  // 5ms process interval (200Hz)
  {
    count5ms = 0;
	  VibratoRampGenerator();
    OscFreqModulation();       // Process pitch-bend or vibrato
    OscMixRatioModulation();   // Wave-table morphing routine
    NoiseLevelControl();       // Noise level control routine
    FilterFrequencyControl();  // Bi-quad filter freq. control
  }
}


/*
   Function:  AmpldEnvelopeShaper()

   Overview:  Audio amplitude envelope shaper.
              Routine called by the Synth Process at 1ms intervals.

   Output:    (fixed_t) m_AmpldEnvOutput = Envelope output level, norm. (0 ~ 0.9995)

*/
void   AmpldEnvelopeShaper()
{
  static  short    envSegment;     // Envelope shaper segment, aka "phase"
  static  uint32   envPhaseTimer;  // Time elapsed in envelope phase (ms)
  static  fixed_t  sustainLevel;   // Ampld Env. sustain level (0 ~ 0.9995)
  static  fixed_t  timeConstant;   // 20% of decay or release time (ms)
  static  fixed_t  ampldDelta;     // Step change in Env Ampld in 1ms
  static  fixed_t  ampldMaximum;   // Peak value of Envelope Ampld
  
  if (m_TriggerAttack)
  {
    m_TriggerAttack = 0;
    m_TriggerRelease = 0;
    envPhaseTimer = 0;
    sustainLevel = IntToFixedPt((int) g_Patch.AmpldEnvSustain) / 100;    // normalized
    sustainLevel = MultiplyFixed(sustainLevel, sustainLevel);  // squared
    ampldMaximum = FIXED_MAX_LEVEL;  // for Peak-Hold phase
    if (g_Patch.AmpldEnvPeak_ms == 0)
      ampldMaximum = sustainLevel;  // No Peak-Hold phase
    ampldDelta = ampldMaximum / g_Patch.AmpldEnvAttack_ms;  // step change in 1ms
    envSegment = ENV_ATTACK;
  }

  if (m_TriggerRelease)
  {
    m_TriggerRelease = 0;
    timeConstant = g_Patch.AmpldEnvRelease_ms / 5;
    envPhaseTimer = 0;
    envSegment = ENV_RELEASE;
  }

  switch (envSegment)
  {
    case ENV_IDLE:  // Idle - Sound off - zero output level
      {
        m_AmpldEnvOutput = 0;
        break;
      }
    case ENV_ATTACK:  // Attack - linear ramp up to peak - or to the sustain level
      {
        if (m_AmpldEnvOutput < ampldMaximum) m_AmpldEnvOutput += ampldDelta;
        if (++envPhaseTimer >= g_Patch.AmpldEnvAttack_ms)  // attack time ended
        {
          m_AmpldEnvOutput = ampldMaximum;
          envPhaseTimer = 0;
          if (g_Patch.AmpldEnvPeak_ms == 0)  envSegment = ENV_SUSTAIN;  // skip peak and decay phases
          else  envSegment = ENV_PEAK_HOLD;  // run all phases
        }
        break;
      }
    case ENV_PEAK_HOLD:  // Peak - constant output level (0.999)
      {
        if (++envPhaseTimer >= g_Patch.AmpldEnvPeak_ms)  // Peak time ended
        {
          timeConstant = g_Patch.AmpldEnvDecay_ms / 5;  // for Decay phase
          envPhaseTimer = 0;
          envSegment = ENV_DECAY;
        }
        break;
      }
    case ENV_DECAY:  // Decay - exponential ramp down to sustain level
      {
        ampldDelta = (m_AmpldEnvOutput - sustainLevel) / timeConstant;  // step in 1ms
        if (ampldDelta == 0)  ampldDelta = FIXED_MIN_LEVEL;
        if (m_AmpldEnvOutput >= (sustainLevel + ampldDelta))  m_AmpldEnvOutput -= ampldDelta;
        // Allow 10 x time-constant for decay phase to complete
        if (++envPhaseTimer >= (g_Patch.AmpldEnvDecay_ms * 2))  envSegment = ENV_SUSTAIN;
        break;
      }
    case ENV_SUSTAIN:       // Sustain constant level - waiting for m_TriggerRelease
      {
        break;
      }
    case ENV_RELEASE:       // Release - exponential ramp down to zero level
      {
        // timeConstant and envPhaseTimer are set by the trigger condition, above.
        ampldDelta = m_AmpldEnvOutput / timeConstant;
        if (ampldDelta == 0)  ampldDelta = FIXED_MIN_LEVEL;
        if (m_AmpldEnvOutput >= ampldDelta)  m_AmpldEnvOutput -= ampldDelta;
        // Allow 10 x time-constant for release phase to complete
        if (++envPhaseTimer >= (g_Patch.AmpldEnvRelease_ms * 2))
        {
          envPhaseTimer = 0;
          envSegment = ENV_IDLE;
        }
        break;
      }
  };  // end switch
}


/*
   Function:  AudioLevelController()

   Overview:  This routine is called by the Synth Process at 1ms intervals.
              The output level is controlled (modulated) by one of a variety of options
              as determined by the patch parameter: g_Patch.OutputAmpldCtrl.

   Output:    (fixed_t) v_OutputLevel : normalized output level (0..+1.0)
              The output variable is used by the audio ISR to control the audio ampld,
              except for the reverberated signal which may continue to sound.
*/
void   AudioLevelController()
{
  static  fixed_t  smoothExprnLevel;
  fixed_t  exprnLevel;
  fixed_t  outputAmpld;  // Audio output level, normalized

  if (g_Patch.OutputAmpldCtrl == AMPLD_CTRL_FIXED_L2)        // mode 1
  {
    if (m_Note_ON)  outputAmpld = FIXED_MAX_LEVEL / 2;
    else  outputAmpld = 0;
  }
  else if (g_Patch.OutputAmpldCtrl == AMPLD_CTRL_EXPRESS)    // mode 2
  {
    // After Note-Off, MIDI Pressure/Expression Level is assumed to be zero
    if (m_Note_ON)  exprnLevel = m_PressureLevel;
    else  exprnLevel = 0;
	
	// Apply IIR smoothing filter to eliminate abrupt changes (K = 1/16)
    smoothExprnLevel -= smoothExprnLevel >> 4;
    smoothExprnLevel += exprnLevel >> 4;
    outputAmpld = smoothExprnLevel;
  }
  else if (g_Patch.OutputAmpldCtrl == AMPLD_CTRL_AMPLD_ENV)  // mode 3
  {
    outputAmpld = m_AmpldEnvOutput;
  }
  else if (g_Patch.OutputAmpldCtrl == AMPLD_CTRL_ENV_VELO)   // mode 4
  {
    outputAmpld = MultiplyFixed(m_AmpldEnvOutput, m_AttackVelocity);
  }
  else    // default  ...................................... // mode 0
  {
    if (m_Note_ON)  outputAmpld = FIXED_MAX_LEVEL;
    else  outputAmpld = 0;
  }

  if (outputAmpld > FIXED_MAX_LEVEL)  outputAmpld = FIXED_MAX_LEVEL;

  v_OutputLevel = outputAmpld;  // accessed by audio ISR
}


/*
   Function:  ContourEnvelopeShaper()

   Overview:  Routine called by the Synth Process at 1ms intervals.
              All segments of the Contour Envelope are linear time-varying.
              The contour output may be used to control the oscillator mix ratio,
              noise level, filter corner frequency (Fc), or whatever.

   Output:    (fixed_t) m_ContourEnvOutput = output signal, normalized (0..+0.99999)
*/
void   ContourEnvelopeShaper()
{
  static  uint32   contourSegmentTimer;   // Time elapsed in active phase (ms)
  static  fixed_t  outputDelta;           // Step change in output level in 1ms

  fixed_t  startLevel = IntToFixedPt(g_Patch.ContourStartLevel) / 100;
  fixed_t  holdLevel = IntToFixedPt(g_Patch.ContourHoldLevel) / 100;

  if (m_ContourEnvTrigger)  // Note-On event
  {
    m_ContourEnvTrigger = 0;
    m_ContourEnvFinish = 0;
    m_ContourEnvOutput = startLevel;
    contourSegmentTimer = 0;
    m_ContourEnvSegment = CONTOUR_ENV_DELAY;
  }

  switch (m_ContourEnvSegment)
  {
    case CONTOUR_ENV_IDLE:         // Waiting for trigger signal
      {
        break;
      }
    case CONTOUR_ENV_DELAY:        // Delay before ramp up/down segment
      {
        if (contourSegmentTimer >= g_Patch.ContourDelay_ms)  // Delay segment ended
        {
          // Prepare for ramp up/down phase (next state) to Hold level
          outputDelta = (holdLevel - m_ContourEnvOutput) / g_Patch.ContourRamp_ms;
          contourSegmentTimer = 0;
          m_ContourEnvSegment = CONTOUR_ENV_RAMP;
        }
        break;
      }
    case CONTOUR_ENV_RAMP:         // Linear ramp up/down from Start to Hold level
      {
        if (contourSegmentTimer >= g_Patch.ContourRamp_ms)  // Ramp segment ended
          m_ContourEnvSegment = CONTOUR_ENV_HOLD;
        else
          m_ContourEnvOutput += outputDelta;
        break;
      }
    case CONTOUR_ENV_HOLD:         // Hold constant level - waiting for Note-Off event
      {
        m_ContourEnvOutput = holdLevel;
        break;
      }
  };  // end switch

  contourSegmentTimer++;
}


/*
   Function:     Synth LFO implementation.

   Called by SynthProcess() at 1ms intervals, this function generates a sinusoidal
   waveform in real time.  LFO frequency is a patch parameter, g_Patch.VibratoFreq,
   unsigned 8-bit value representing LFO freq * 10 Hz; range 1..250 => 0.1 to 25 Hz.
   
   Input variable, m_LFO_Step, is initialised externally, dependent on synth patch.
   The output of the LFO is m_LFO_output, a normalized fixed-point variable.
*/
void   LowFrequencyOscillator()
{
  static  int32  oscAngleLFO;  // 24:8 bit fixed-point
  fixed_t  sample;
  int  waveIdx;

  waveIdx = oscAngleLFO >> 8;  // integer part of oscAngleLFO
  sample = (fixed_t) g_sinewave[waveIdx] << 5;  // normalized
  oscAngleLFO += m_LFO_Step;
  if (oscAngleLFO >= SINE_WAVE_TABLE_SIZE << 8)
      oscAngleLFO -= SINE_WAVE_TABLE_SIZE << 8;

  m_LFO_output = (fixed_t) sample;
}


/*
 * Function:     Vibrato Ramp Generator implementation.
 *
 * Called by the SynthProcess() at 5ms intervals, this function generates a linear ramp.
 *
 * The vibrato (LFO) delayed ramp is triggered by a Note-On event. 
 * If a Legato note change occurs, vibrato is stopped (fast ramp down) and the ramp delay
 * is re-started, so that vibrato will ramp up again after the delay.
 *
 * The delay and ramp-up times are both set by the patch parameter, g_Patch.LFO_RampTime,
 * so the delay time value is the same as the ramp-up time.  This works well enough.
 */
PRIVATE  void   VibratoRampGenerator()
{
    static  short   rampState = 0;
    static  uint32  delayTimer_ms;
    static  fixed_t rampStep;  // Step chnage in output per 5 ms

    if (rampState == 0)  // Idle - waiting for Note-On
    {
		  rampStep = IntToFixedPt(5) / (int) g_Patch.VibratoRamp_ms;
      if (m_Note_ON)  
        { m_RampOutput = 0;  delayTimer_ms = 0;  rampState = 1; }
    }
    else if (rampState == 1)  // Delaying before ramp-up begins
    {
      if (delayTimer_ms >= g_Patch.VibratoRamp_ms)  rampState = 2;
      else  delayTimer_ms += 5;
    }
    else if (rampState == 2)  // Ramping up - hold at max. level (1.00)
    {
      if (m_RampOutput < FIXED_MAX_LEVEL)  m_RampOutput += rampStep;
      if (m_RampOutput > FIXED_MAX_LEVEL)  m_RampOutput = FIXED_MAX_LEVEL;
    }
    else  rampState = 0;  // Undefined state... reset
	
	// Check for Note-Off or Note-Change event while ramp is progressing
    if ((rampState != 0) && (!m_Note_ON || m_LegatoNoteChange))
    {
      if (m_LegatoNoteChange)  
		    { m_LegatoNoteChange = 0;  m_RampOutput = 0;  delayTimer_ms = 0;  rampState = 1; }
      else  rampState = 0;
    }
}


/*
   Function:     Oscillator Frequency Modulation  (Pitch-bend, vibrato, etc)

   Called by SynthProcess() at 5ms intervals, this function modulates the pitch of
   the wave-table oscillators according to a multiplier variable, freqMult,
   which may be modified while a note is in progress.

   The linear m_PitchBendFactor is transformed into a multiplier in the range 0.5 ~ 2.0.
   Centre (zero) m_PitchBendFactor value should give a multplier value of 1.00.

   Note 1:  This function is used for low frequency modulation, up to about 25Hz.
          
   Note 2:  Pitch Bend and Vibrato are mutually exclusive in the REMI synth...
            If vibrato is enabled (m_VibratoControl != 0), then Pitch Bend is inhibited.      
*/
void   OscFreqModulation()
{
  static  fixed_t  smoothFreqMult = IntToFixedPt(1);

  fixed_t  LFO_scaled, modnLevel = 0;  // normalized quantities (range 0..+/-1.0)
  fixed_t  freqMult = 0;

  if (m_VibratoControl == VIBRATO_BY_MODN_CC)  // Use Mod Lever position
    modnLevel = (m_ModulationLevel * g_Patch.LFO_FM_Depth) / 1200;
	  
  if (m_VibratoControl == VIBRATO_AUTOMATIC)   //  Use Ramp Gen.
     modnLevel = (m_RampOutput * g_Patch.LFO_FM_Depth) / 1200;
 
  if (m_VibratoControl && !m_PitchBendControl)
  {
    LFO_scaled = MultiplyFixed(m_LFO_output, modnLevel);
    freqMult = Base2Exp(LFO_scaled);   // range 0.5 ~ 2.0.
  }
  else if (m_PitchBendControl == PITCH_BEND_BY_SENSOR)
  {
    freqMult = Base2Exp(m_PitchBendFactor);
  }
  else if (m_PitchBendControl == PITCH_BEND_BY_EXPRN)
  {
    modnLevel = (m_PressureLevel * m_PitchBendRange) / 1200;
    freqMult = Base2Exp(modnLevel);
  }
  else  freqMult = IntToFixedPt( 1 );  // No pitch modulation

  if (m_VibratoControl || m_PitchBendControl)
  {
    smoothFreqMult -= smoothFreqMult >> 3;  // Tc = 8 * 5ms = 40ms (approx)
    smoothFreqMult += freqMult >> 3; 
    // Update real-time oscillator variables (accessed by audio ISR)
    v_Osc1Step = MultiplyFixed(m_Osc1StepInit, smoothFreqMult);
    v_Osc2Step = MultiplyFixed(m_Osc2StepInit, smoothFreqMult);
  }
}


/*
   Oscillator Mix Ratio Modulation

   Called by the SynthProcess() routine at 5ms intervals, this function controls the ratio
   of the 2 oscillator signals input to the wave mixer, according to a variable, mixRatio_pK,
   which is the fraction (x1024) of the output of OSC2 relative to OSC1 fed into the mixer.

   The instantaneous value of the time-varying quantity mixRatio_pK is determined by the
   patch mixer control mode parameter, g_Patch.MixerControl.
   The actual mixing operation is performed by the audio ISR, using the output variables.

   Output variable:   v_Mix2Level  (range 0..1000)
*/
void  OscMixRatioModulation()
{
  fixed_t  LFO_scaled;
  fixed_t  modnLevel;
  fixed_t  mixRatioLFO;   // normalized
  int      mixRatio_pK;   // fraction of OSC2 in the mix x1000

  if (g_Patch.MixerControl == MIXER_CTRL_CONTOUR)
  {
    mixRatio_pK = IntegerPart(m_ContourEnvOutput * 1000);
  }
  else if (g_Patch.MixerControl == MIXER_CTRL_LFO)
  {
    // Use vibrato depth param (0..1200) to set contour LFO modulation depth.
    modnLevel = (m_RampOutput * g_Patch.LFO_FM_Depth) / 1200;
    LFO_scaled = MultiplyFixed(m_LFO_output, modnLevel);  // range -1.0 ~ +1.0
    mixRatioLFO = (IntToFixedPt( 1 ) + LFO_scaled) / 2;   // range  0.0 ~ +1.0
    mixRatio_pK = IntegerPart(mixRatioLFO * 1000);        // convert to 'per K' units
  }
  else if (g_Patch.MixerControl == MIXER_CTRL_EXPRESS)
  {
    mixRatio_pK = IntegerPart(m_PressureLevel * 1000);
  }
  else if (g_Patch.MixerControl == MIXER_CTRL_MODULN)
  {
    mixRatio_pK = IntegerPart(m_ModulationLevel * 1000);
  }
  else  // assume (g_Patch.MixerControl == MIXER_CTRL_FIXED) -- default
  {
    mixRatio_pK = (1000 * (int) g_Patch.MixerOsc2Level) / 100;  // fixed %
  }

  v_Mix2Level = mixRatio_pK;
}


/*
   Noise Generator Output level Control

   Called by the SynthProcess() routine at 5ms intervals, this function sets the noise
   modulator output level in real-time according to the selected control mode (patch param).
   The actual level control operation is performed by the audio ISR.

   Output variable:  v_NoiseLevel  (normalized fixed-point)
*/
void   NoiseLevelControl()
{
  if (g_Patch.NoiseLevelCtrl == NOISE_LVL_FIXED)           // mode 1 (Fixed max.)
    v_NoiseLevel = FIXED_MAX_LEVEL;
  else if (g_Patch.NoiseLevelCtrl == NOISE_LVL_AMPLD_ENV)  // mode 2
    v_NoiseLevel = m_AmpldEnvOutput;
  else if (g_Patch.NoiseLevelCtrl == NOISE_LVL_EXPRESS)    // mode 3
    v_NoiseLevel = (m_PressureLevel / 2);
  else if (g_Patch.NoiseLevelCtrl == NOISE_LVL_MODULN)     // mode 4
    v_NoiseLevel = (m_ModulationLevel * 75) / 100;
  else  v_NoiseLevel = 0;  // ...........................  // mode 0 (Noise OFF)
}


/*
 * Bi-quad resonant filter centre frequency control (modulation)
 *
 * Called by the SynthProcess() routine at 5ms intervals, this function updates the
 * bi-quad IIR filter coefficient a1 in real-time according to the note pitch and the
 * filter frequency control (modulation) parameter(s).
 * The filter resonance cannot be changed while a note is in progress, hence other
 * filter coeff's do not need to be updated here.
 * The actual DSP filter algorithm is incorporated in the audio ISR.
 * 
 * Input variable:  m_FilterIndex = index into filter coeff LUT, varies with fc,
 *                                  determined at Note_ON and legato note change.
 *     
 * Output variables:  v_coeff_a1  = real-time filter coeff (fixed-point value)
 */
PRIVATE  void   FilterFrequencyControl()
{
    fixed_t  devn;   // deviation from quiescent value (+/-0.5 max)
    int  fc_idx;     // index into filter coeff (c) look-up table
    
    if (g_Patch.NoiseMode != NOISE_DISABLED)  
        return;  // wave filter is bypassed while noise is enabled
    
    if (g_Patch.FilterControl == FILTER_CTRL_CONTOUR)  // mode 1
    {
        fc_idx = m_FilterIndex + IntegerPart(m_ContourEnvOutput * 108) - 50;
    }
    else if (g_Patch.FilterControl == FILTER_CTRL_LFO)  // mode 4
    {
        devn = (m_LFO_output * g_Patch.LFO_FM_Depth) / 200;  // deviation (+/-0.5 max)
        fc_idx = m_FilterIndex + IntegerPart(devn * 108);
    }
    else if (g_Patch.FilterControl == FILTER_CTRL_MODULN)  // mode 5
    {
        devn = (m_ModulationLevel * 50) / 100;  // deviation (0.5 max)
        fc_idx = m_FilterIndex - IntegerPart(devn * 108);  // Fc decreases with mod'n level
    }
    else  fc_idx = m_FilterIndex;  // filter Fc is constant or note tracking (offset)

    if (fc_idx > 108)  fc_idx = 108;   // max. (~8 kHz)
    if (fc_idx < 0)  fc_idx = 0;       // min. (~16 Hz)

    v_coeff_a1 = 0 - m_FiltCoeff_c[fc_idx];  // a1 = -c
}


/*`````````````````````````````````````````````````````````````````````````````````````````````````
   Function:   Audio Sampling Routine (ASR) -- called by timer interrupt handler

   The ASR performs DSP synthesis computations which need to be executed at the PCM audio
   sampling rate, as defined by SAMPLE_RATE_HZ (typ. 40 kHz).

   Signal (sample) computations use 32-bit [12:20] fixed-point arithmetic, except
   that wave-table samples are stored as 16-bit signed integers. Wave-table samples are
   converted to normalized fixed-point (20-bit fraction) by shifting left 5 bit places.

   The Wave-table Oscillator algorithm uses lower precision fixed-point (16:16 bits) to
   avoid arithmetic overflow, which could occur with 12:20 bit precision.
*/
void  AudioSamplingRoutine(void)
{
  static  fixed_t  filter_in_1;         // bi-quad filter input delayed 1 sample
  static  fixed_t  filter_in_2;         // bi-quad filter input delayed 2 samples
  static  fixed_t  filter_out_1;        // bi-quad filter output delayed 1 sample
  static  fixed_t  filter_out_2;        // bi-quad filter output delayed 2 samples
  static  uint32   rand_last = 1;       // random number (NB: seed must be odd!)
  static  int      rvbIndex;            // index into ReverbDelayLine[]
  static  fixed_t  reverbPrev;          // previous sample from reverb delay line

  int      idx;                         // index into wave-tables
  fixed_t  osc1Sample, osc2Sample;      // outputs from OSC1 and OSC2
  fixed_t  noiseSample;                 // output from white noise algorithm
  fixed_t  noiseGenOut;                 // output from noise generator
  fixed_t  waveRatio;                   // wave to noise ratio (0 ~ 1.0))
  fixed_t  mixerIn1, mixerIn2;          // inputs to wave-osc mixer
  fixed_t  waveMixerOut;                // output from wave-osc mixer
  fixed_t  totalMixOut = 0;             // output from wave + noise mixers
  fixed_t  filterIn;                    // input to IIR bi-quad filter
  fixed_t  filterOut;                   // output from IIR bi-quad filter
  fixed_t  attenOut = 0;                // output from variable-gain attenuator
  fixed_t  reverbOut;                   // output from reverb delay line
  fixed_t  reverbLPF;                   // output from reverb loop filter
  fixed_t  finalOutput = 0;             // output sample (to DAC)

  TESTPOINT_SET_HIGH();  // for 'scope probe -- to measure ASR execution time

  if (v_SynthEnable)
  {
    // OSC1 Wave-table oscillator
    idx = v_Osc1Angle >> 16;  // integer part of v_Osc1Angle
    osc1Sample = (fixed_t) m_WaveTable1[idx] << 5;  // normalize
    v_Osc1Angle += v_Osc1Step;
    if (v_Osc1Angle >= (m_Osc1WaveTableSize << 16))
      v_Osc1Angle -= (m_Osc1WaveTableSize << 16);

    // OSC2 Wave-table oscillator
    idx = v_Osc2Angle >> 16;  // integer part of v_Osc2Angle
    osc2Sample = (fixed_t) m_WaveTable2[idx] << 5;  // normalize
    v_Osc2Angle += v_Osc2Step;
    if (v_Osc2Angle >= (m_Osc2WaveTableSize << 16))
      v_Osc2Angle -= (m_Osc2WaveTableSize << 16);

    // Wave Mixer -- add OSC1 and OSC2 samples, scaled according to mix ratio
    mixerIn1 = (osc1Sample * (1000 - v_Mix2Level)) >> 10;
    mixerIn2 = (osc2Sample * v_Mix2Level) >> 10;
    waveMixerOut = mixerIn1 + mixerIn2;

    // White noise generator -- Pseudo-random number algorithm...
    rand_last = (rand_last * 1103515245 + 12345) & 0x7FFFFFFF;  // unsigned
    noiseSample = (int32) (rand_last << 1);    // signed 32-bit value
    noiseSample = noiseSample >> 11;           // normalized fixed-pt (+/-1.0)

    if (g_Patch.NoiseMode)  // Noise enabled in patch
    {
      // Adjust noiseSample to a level which avoids overdriving the filter
      filterIn = (noiseSample * m_FilterAtten_pc) / 100;
      // Apply filter algorithm
      filterOut =  MultiplyFixed(v_coeff_b0, filterIn);
      filterOut += MultiplyFixed(v_coeff_b2, filter_in_2);
      filterOut -= MultiplyFixed(v_coeff_a1, filter_out_1);
      filterOut -= MultiplyFixed(v_coeff_a2, filter_out_2);
      filter_in_2 = filter_in_1;  // update delayed samples
      filter_in_1 = filterIn;
      filter_out_2 = filter_out_1;
      filter_out_1 = filterOut;
      // Adjust noise filter output level to compensate for spectral loss
      filterOut = (filterOut * m_NoiseGain_x10) / 10;

      // If enabled, Ring Modulate OSC2 output with filtered noise...
      if (g_Patch.NoiseMode & NOISE_PITCHED)
        noiseGenOut = MultiplyFixed(filterOut, osc2Sample);  // Ring Mod.
      else  noiseGenOut = filterOut;   // unmodulated filtered noise

      // Add or mix noise with wave mixer output according to patch mode
      if ((g_Patch.NoiseMode & 3) == NOISE_WAVE_ADDED)  // Add noise to total mix
      {
        noiseGenOut = MultiplyFixed(noiseGenOut, v_NoiseLevel);
        totalMixOut = (waveMixerOut + noiseGenOut) / 2;  // avoid clipping
      }
      else if ((g_Patch.NoiseMode & 3) == NOISE_WAVE_MIXED)  // Ratiometric mix
      {
        waveRatio = IntToFixedPt(1) - v_NoiseLevel;  // wave:noise ratio (0 ~ 1.0)
        totalMixOut = MultiplyFixed(waveMixerOut, waveRatio);
        totalMixOut += MultiplyFixed(noiseGenOut, v_NoiseLevel);
      }
      else  totalMixOut = MultiplyFixed(noiseGenOut, v_NoiseLevel);  // Noise only
    }
    else if (g_Patch.FilterResonance)  // Filter enabled (FilterResonance != 0)
    {
      // Adjust waveMixerOut to a level which avoids overdriving the filter
      filterIn = (waveMixerOut * m_FilterAtten_pc) / 100;
      // Apply filter algorithm
      filterOut =  MultiplyFixed(v_coeff_b0, filterIn);
      filterOut += MultiplyFixed(v_coeff_b2, filter_in_2);
      filterOut -= MultiplyFixed(v_coeff_a1, filter_out_1);
      filterOut -= MultiplyFixed(v_coeff_a2, filter_out_2);
      filter_in_2 = filter_in_1;  // update delayed samples
      filter_in_1 = filterIn;
      filter_out_2 = filter_out_1;
      filter_out_1 = filterOut;
      // Adjust filter output level
      totalMixOut = (filterOut * m_FilterGain_x10) / 100;
    }
    else  totalMixOut = waveMixerOut;   // No noise and no filter in patch

    // Apply ampld limiter...  (crude clipping for the time being)
    if (finalOutput > FIXED_MAX_LEVEL)  finalOutput = FIXED_MAX_LEVEL;
    if (finalOutput < -FIXED_MAX_LEVEL)  finalOutput = -FIXED_MAX_LEVEL;

    // Variable-gain output attenuator -- Apply expression, envelope, etc.
    attenOut = MultiplyFixed(totalMixOut, v_OutputLevel);

    // Reverberation effect processor (Courtesy of Dan Mitchell, ref. "BasicSynth")
	  if (m_RvbMix != 0)
	  {
      reverbOut = MultiplyFixed(ReverbDelayLine[rvbIndex], m_RvbDecay);
      reverbLPF = (reverbOut + reverbPrev) >> 1;  // simple low-pass filter
	    reverbPrev = reverbOut;
      ReverbDelayLine[rvbIndex] = ((attenOut * m_RvbAtten) >> 7) + reverbLPF;
      if (++rvbIndex >= m_RvbDelayLen)  rvbIndex = 0;  // wrap
      // Add reverb output to dry signal according to reverb mix setting...
      finalOutput = (attenOut * (128 - m_RvbMix)) >> 7;  // Dry portion
      finalOutput += (reverbOut * m_RvbMix) >> 7;   // Wet portion
	  }
	  else  finalOutput = attenOut;
  }
  
  // Audio DAC output (12 bits) -- update DAC register with sample value (1..3999).
  // The DAC output is unipolar (0 to +3.3V), so a 50% bias (2000) is added to the sample.
  analogWrite(A14, 2000 + (int)(finalOutput >> 9));

  TESTPOINT_SET_LOW();
}


//=================================================================================================
//                                    Sundry functions
/*
   Function:     Get ID number of active patch.
*/
int  GetActivePatchID()
{
  return  g_Patch.PatchNumber;
}

/*
   Function:     Get patch (program) table index for a given patch ID number. 
   Return val:   Table index, or ERROR (-1) if patchNumber not found (undefined).           
*/
int  GetPatchTableIndex(unsigned patchNumber)
{
  int  i, patchIndex = -1;
  int  patchCount = GetNumberOfPatchesDefined();
	
  for (i = 0;  i < patchCount;  i++) 
  {
    if (g_PatchProgram[i].PatchNumber == patchNumber)  { patchIndex = i;  break; }
  }
  
  return  patchIndex;
}

/*
   Function:     Set OSC1 Frequency Divider value.
                 The given value over-rides the value selected by a prior call to
                 SynthPatchSetup() or WaveTableSelect().
                 Intended primarily for test and debug purposes.

   Entry arg:    (float) freqDiv = Frequency Divider value
*/
void  Osc1FreqDividerSet(float freqDiv)
{
  m_Osc1FreqDiv = freqDiv;
}

/*
   Function:  Return TRUE if the Remi synth is enabled, i.e. audio sampling active.
              Intended primarily for test and debug purposes.
*/
BOOL  isSynthActive(void)
{
  return  (v_SynthEnable != 0);
}

/*
   Function:     Get Expression/pressure level (fixed-pt value).
                 Intended primarily for test and debug purposes.
*/
fixed_t  GetExpressionLevel(void)
{
  return  m_PressureLevel;
}

/*
   Function:     Get Expression/pressure level (fixed-pt value).
                 Intended primarily for test and debug purposes.
*/
fixed_t  GetModulationLevel(void)
{
  return  m_ModulationLevel;
}


/*
   Function:    Base2Exp()

   Overview:    Base-2 exponential transfer function using look-up table with interpolation.
                Resolution (precision) is better than +/-0.0001

   Entry arg:   (fixed_t) xval = fixed-point real number, range -1.0 to +1.0

   Returned:    (fixed_t) yval = 2 ** xval;  range 0.5000 to 2.0000

   Note 1:      If entry arg (xval) is out of range, returned value is 1.000.

   Note 2: <!>  LUT g_base2exp[] values are 18:14 bit fixed-point.
                Shift left 6 bit places to convert to 12:20 fixed-pt.

   Results from unit test function:

     x = -1.00000,  y =  0.50000
     x = -0.99900,  y =  0.50031
     x = -0.50000,  y =  0.70709
     x = -0.00100,  y =  0.99908
     x =  0.00000,  y =  1.00000
     x =  0.00010,  y =  1.00000
     x =  0.00050,  y =  1.00031
     x =  0.00100,  y =  1.00067
     x =  0.00150,  y =  1.00098
     x =  0.00200,  y =  1.00134
     x =  0.50000,  y =  1.41418
     x =  0.99950,  y =  1.99896
     x =  1.00000,  y =  2.00000
*/
fixed_t  Base2Exp(fixed_t xval)
{
  int   ixval;        // 13-bit integer representing x-axis coordinate
  int   idx;          // 10 MS bits of ixval = array index into LUT, g_base2exp[]
  int   irem3;        // 3 LS bits of ixval for interpolation
  int32 ydelta;       // change in y value between 2 adjacent points in LUT
  int32 yval;         // y value (from LUT) with interpolation

  if (xval < IntToFixedPt(-1) || xval > IntToFixedPt(1))  xval = 0;

  // Convert real xval (x-coord) to positive 13-bit integer in the range 0 ~ 8K
  ixval = FractionPart((xval + IntToFixedPt(1)) / 2, 13);
  idx = ixval >> 3;  // 10-bit int
  irem3 = ixval & 7;

  if (xval == IntToFixedPt(1))
    yval = 2 << 14;  // maximum value in 18:14 bit format
  else
  {
    yval = (int32) g_base2exp[idx];
    ydelta = (((int32) g_base2exp[idx + 1] - yval) * irem3) / 8;
    yval = yval + ydelta;
  }

  return  (fixed_t)(yval << 6);   // convert to 12:20 fixed-pt format
}

/*
   Function:    ScurveTransform()

   Overview:    Apply "S-curve" transform to a linear input value (point).
                The curve is based on the middle half cycle of the sine function, inverted:
                y = (1 - sin(x)) / 2,  where pi/2 < x < 3*pi/2

   Entry arg:   (unsigned) point = x-axis value, range 0 to 16K (14 bits)

   Returned:    (fixed_t) y-axis value, normalized, range: 0.0 to 0.99999  
   
   Note:        Number of points in g_sinewave[] LUT = 1260;  peak value = 31680
   
   To do:       Add LUT interpolation to improve precision.   <<<<<<<<<<<<<<<<<<<<<<< todo ???
                (based on "virtual LUT" with 8 x number of points, i.e. 8 x 1260)
*/
fixed_t  ScurveTransform(unsigned point)
{
  unsigned idx = (630 * point) / (16 * 1024) + 315;  // range: 1260/4 .. 3*1260/4
  int  yval = (31680 - g_sinewave[idx]) / 2;  // 15 bits (positive value)
  
  // Scale to and convert 15-bit integer to fixed-pt (20-bit fraction)
  return  (fixed_t) ((32767 * yval) / 31680) << 5;  
}

// end-of-file
