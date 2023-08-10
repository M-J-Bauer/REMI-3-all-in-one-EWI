/**
     File:    remi_teensy_synth.h

     Data declarations for REMI mk3 (Teensy 3.2) sound synthesizer.
*/
#ifndef REMI_TEENSY_SYNTH_H
#define REMI_TEENSY_SYNTH_H

#include "remi_system_def.h"
#include "remi_3.h"

#define GLOBAL_INT_ENABLE()         interrupts()
#define GLOBAL_INT_DISABLE()        noInterrupts()

#define SAMPLE_RATE_HZ        (40000)    // For wave-table Oscillators
#define FILTER_INPUT_ATTEN      0.20f    // Set to avoid overloading filter input
#define FILTER_OUTPUT_GAIN       4.0f    // Set to avoid output mixer clipping
#define NOISE_FILTER_GAIN        4.0f    // Noise generator post-filter gain

#define REVERB_DELAY_MAX_SIZE    2000    // samples 
#define REVERB_LOOP_TIME_SEC     0.04    // seconds (max. 0.05 sec.)
#define REVERB_DECAY_TIME_SEC     0.5    // seconds
#define SINE_WAVE_TABLE_SIZE     1260    // samples (for g_sinewave[] LUT)

#define FIXED_MIN_LEVEL  (1)                     // Minimum normalized signal level (0.000001)
#define FIXED_MAX_LEVEL  (IntToFixedPt(1) - 1)   // Full-scale normalized signal level (0.999999)
#define FIXED_PT_HALF    (IntToFixedPt(1) / 2)   // Constant 0.5 in fixed_t format
#define AUDIO_FLOOR_LEVEL  (20)                  // Audio "floor" level (approx. 0.00002)

// Possible values for configuration parameter: g_Config.AudioAmpldControlMode
#define AMPLD_CTRL_FIXED_FS         0    // Output ampld is fixed (full-scale)
#define AMPLD_CTRL_ENV_VELO         1    // Output ampld control by Env * Velocity
#define AMPLD_CTRL_EXPRESS          2    // Output ampld control by Expression (CC2/7/11)

// Possible values for m_VibratoMode
#define VIBRATO_DISABLED            0    // Vibrato off
#define VIBRATO_BY_MODN_CC          1    // Vibrato controlled by Modulation (CC1)
#define VIBRATO_AUTOMATIC           2    // Vibrato automatic, delay + ramp, OSC1, OSC2

// Possible values for m_PitchBendMode  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  *** TODO ***
#define PITCH_BEND_DISABLED         0    // Pitch Bend disabled
#define PITCH_BEND_BY_SENSOR        1    // Pitch Bend controlled by PB sensor
#define PITCH_BEND_BY_MODN          2    // Pitch Bend controlled by Modulation lever (N/A)
#define PITCH_BEND_BY_EXPRN         3    // Pitch Bend controlled by Breath pressure (todo)

// Possible values for patch parameter: m_Patch.MixerControl
#define MIXER_CTRL_FIXED            0    // Osc. mix is constant (MixerOsc2Level %)
#define MIXER_CTRL_CONTOUR          1    // Osc. mix is modulated by Contour Envelope
#define MIXER_CTRL_LFO              2    // Osc. mix is modulated by LFO * Env
#define MIXER_CTRL_EXPRESS          3    // Osc. mix is modulated by Expression (CC2/CC11)
#define MIXER_CTRL_MODULN           4    // Osc. mix is modulated by Modulation Lvr (CC1)

// Possible values for patch parameter: m_Patch.NoiseMode (3 LS bits)
#define NOISE_DISABLED              0    // Noise off
#define NOISE_ONLY_NO_WAVE          1    // Noise, no wave signal added
#define NOISE_WAVE_ADDED            2    // Noise, wave signal added
#define NOISE_WAVE_MIXED            3    // Noise, wave signal mixed (ratiometric)
// Add 4 (set bit2) in the above values to enable Ring Modulator for "pitched noise"
#define NOISE_PITCHED               4    // Pitched noise 

// Possible values for patch parameter: m_Patch.NoiseLevelCtrl
#define NOISE_LVL_FIXED             0    // Noise level is fixed (constant)
#define NOISE_LVL_AMPLD_ENV         1    // Noise level control by Ampld Envelope
#define NOISE_LVL_LFO               2    // Noise level control by LFO 
#define NOISE_LVL_EXPRESS           3    // Noise level control by Expression (CC2/CC11)
#define NOISE_LVL_MODULN            4    // Noise level control by Modulation (CC1)

// Possible values for patch parameter: m_Patch.FilterControl
#define FILTER_CTRL_FIXED           0    // Filter Fc is fixed (FilterCornerFreq)
#define FILTER_CTRL_CONTOUR         1    // Filter Fc control by Contour Env.
#define FILTER_CTRL_LFO             2    // Filter Fc control by LFO (vibrato))
#define FILTER_CTRL_EXPRESS         3    // Filter Fc control by Expression (CC2/CC11)
#define FILTER_CTRL_MODULN          4    // Filter Fc control by Modulation (CC1)


enum  Amplitude_Envelope_Phases
{
  ENV_IDLE = 0,      // Idle - Envelope off - zero output level
  ENV_ATTACK,        // Attack - linear ramp up to peak
  ENV_PEAK_HOLD,     // Peak Hold - constant output at max. level (.999)
  ENV_DECAY,         // Decay - exponential ramp down to sustain level
  ENV_SUSTAIN,       // Sustain - constant output at a set level
  ENV_RELEASE,       // Release - exponential ramp down to zero level
};

enum  Contour_Envelope_Phases
{
  CONTOUR_ENV_IDLE = 0,  // Idle - set envelope start level (for note on))
  CONTOUR_ENV_DELAY,     // Delay - delay before contour ramp
  CONTOUR_ENV_RAMP,      // Ramp - linear transition to hold level
  CONTOUR_ENV_HOLD,      // Hold - maintain constant level (until note off)
  CONTOUR_ENV_FINISH,    // Finish - fast transition to start level (50ms)
};


// Data structure for active patch (m_Patch) and pre-defined patches in flash:
//
typedef  struct  synth_patch_param_table
{
  uint16  PatchNumber;            // 1..999
  char    PatchName[22];          // 20 chars max. (+NUL)
  // Oscillators, Pitch Bend and Vibrato
  uint8   Osc1WaveTable;          // 0..250
  uint8   Osc2WaveTable;          // 0..250
  int16   Osc2Detune;             // +/-4800 cents
  uint8   LFO_Freq_x10;           // 1..250 -> 0.1 ~ 25 Hz
  uint8   LFO_FM_Depth;           // 0..200 cents, or 0..99 % [see Note 1]
  uint16  VibratoRamp_ms;         // 1..10k ms (delay & ramp-up time)
  // Wave Mixer & Contour Envelope
  uint8   MixerControl;           // 0:Fixed, 1:Contour, 2:LFO, 3:Exprn, 4:Modn
  uint8   MixerOsc2Level;         // 0..100 %
  uint8   ContourStartLevel;      // 0..100 %
  uint16  ContourDelay_ms;        // 1..10k ms
  uint16  ContourRamp_ms;         // 1..10k ms
  uint8   ContourHoldLevel;       // 0..100 %
  // Noise Modulator & Bi-quad Variable Filter
  uint8   NoiseMode;              // 0:Off, 1:Noise only, 2:Add wave, 3:Mix wave (+4:Pitched)
  uint8   NoiseLevelCtrl;         // 0:Off, 1:Fixed, 2:Amp.Env, 3:Exprn, 4:Modn
  uint8   FilterControl;          // 0:Fixed, 1:Contour, 2:Env+, 3:Env-, 4:LFO, 5:Modn
  uint16  FilterResonance;        // 0..9999 (0: bypass filter)
  uint8   FilterFrequency;        // 0..108 (MIDI note # - 12)
  uint8   FilterNoteTrack;        // 0:Off, 1:On (FF is offset from Fo)
  // Amplitude Envelope and Output Level Control
  uint16  AmpldEnvAttack_ms;      // 1..10k ms
  uint16  AmpldEnvPeak_ms;        // 0..10k ms
  uint16  AmpldEnvDecay_ms;       // 1..10k ms
  uint16  AmpldEnvRelease_ms;     // 1..10k ms
  uint8   AmpldEnvSustain;        // 0..100 % (square-law curve ?)
  uint8   AudioLevelAdjust;       // 25..250 %

} PatchParamTable_t;

// Note 1:  If the LFO is used for filter freq. mod'n, Vibrato Depth is the mod'n index (%)

// Descriptor used to access wave-tables defined in flash PM
typedef struct Flash_Wave_Table_Descriptor
{
  uint16  Size;          // Table size, samples
  float   FreqDiv;       // Osc Freq Divider
  int16  *Address;       // Address of wave-table data in flash

} FlashWaveTable_t;


extern  const  PatchParamTable_t  g_PatchProgram[];       // Array of pre-defined synth patches
extern  const  FlashWaveTable_t   g_FlashWaveTableDef[];  // Array of flash-based wave-tables

extern  const  int16   g_sinewave[];
extern  const  int16   g_sawtooth_wave[];
extern  const  uint16  g_base2exp[];

extern  volatile uint16   v_Mix2Level;
extern  volatile fixed_t  v_OutputLevel;

//extern  EepromBlock0_t  g_Config;     // structure holding synth config data


// Functions defined in "remi_3_synth.c"
// `````````````````````````````````````
void   SynthAudioInit();
short  SynthPatchSelect(int patchID);
void   SynthPrepare();
void   SynthNoteOn(uint8 note, uint8 vel);
void   SynthNoteChange(uint8 note);
void   SynthNoteOff();
void   SynthPitchBend(int data14);
void   SynthExpression(unsigned data14);
void   SynthModulation(unsigned data14);
void   SynthVibratoModeSet(unsigned mode);
void   SynthPitchBendModeSet(unsigned mode);
void   SynthReverbLevelSet(unsigned level_pc);
void   SynthReverbAttenSet(unsigned atten_pc);

void   WaveTableSelect(uint8 osc_num, uint8 wave_id);
void   SynthProcess();
void   AmpldEnvelopeShaper();
void   AudioLevelController();
void   ContourEnvelopeShaper();
void   OscFreqModulation();
void   OscMixRatioModulation();
void   NoiseLevelControl();
void   FilterFrequencyControl();
void   LowFrequencyOscillator();
void   VibratoRampGenerator();

PatchParamTable_t  *GetActivePatchTable();
int      GetActivePatchID();
int      GetPatchTableIndex(unsigned patchNumber);
fixed_t  GetExpressionLevel(void);
fixed_t  GetModulationLevel(void);
fixed_t  Base2Exp(fixed_t xval);
fixed_t  ScurveTransform(unsigned point);

// Functions defined in "remi_teensy_data.c"
// `````````````````````````````````````````
int    GetNumberOfPatchesDefined();
int    GetHighestWaveTableID();

#endif // REMI_TEENSY_SYNTH_H
