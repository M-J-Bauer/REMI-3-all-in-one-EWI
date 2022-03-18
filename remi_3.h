/****************************************************************************************

   FileName:   remi_3.h

   File contains build options and particular def's for the project.
   See also: "remi_system_def.h"

   =======================================================================================
*/
#ifndef _REMI_3_H
#define _REMI_3_H

// =======================================================================================
//                       FIRMWARE VERSION NUMBER AND BUILD OPTIONS
//
#define BUILD_VER_MAJOR   1
#define BUILD_VER_MINOR   1
#define BUILD_VER_DEBUG   0
//
// =======================================================================================

#include "remi_system_def.h"
#include "remi_teensy_synth.h"
#include "oled_display_lib.h"

#define AUTO_SHUTDOWN_TIMEOUT     120      // seconds with no user activity
#define NUMBER_OF_TOUCH_INPUTS     10      // Maximum 12
#define TOUCH_SENSE_THRESHOLD    2000      // 2500 == 50pF;  Sense time: 0.25ms per 33pF
#define MODULATION_MAXIMUM       4095      // ADC counts  <<<<<<<<<<<<<<<<<<<<<<<  TBD  <<<<<<<<<<<<
#define MODULATION_DEADBAND      1000      // ADC counts  <<<<<<<<<<<<<<<<<<<<<<<  TBD  <<<<<<<<<<<<

#define ANALOG_FULL_SCALE        4095      // for ADC resolution of 12 bits
#define NOTE_ON_VELOCITY_DELAY     10      // Delay (ms) from note trigger to get velocity
#define MIDI_EXPRN_CC               2      // 2:Breath-pressure, 7:Channel-volume, 11:Expression
#define MIDI_MODN_MSG_INTERVAL     30      // unit = ms

#define ERROR_EEPROM_DATA_CHECK    (1<<0)    // bit0 of error code
#define ERROR_CALIBRATING_SENSOR   (1<<1)    // bit1 of error code


// Teensy MCU pin assignments
#define VBATT_PIN                  A0
#define BREATH_SENSOR_PIN          A6
#define MODN_PAD_PIN               A7
#define BATT_LED_PIN               3   // PWM (variable intensity)
#define VBUS_DET_PIN               4   // active High
#define SET_BUTTON_PIN             5   // active LOW (when pressed)
#define SPKR_EN_PIN                6   // active High
#define BATT_EN_PIN                7   // active LOW (battery sw. on)
#define PHON_DET_PIN               8   // active High
#define TESTPOINT_PIN              12
#define TEENSY_LED_PIN             13  
 
// Macros to perform low-level I/O operations
#define BATT_LED_CONFIG()          analogWriteFrequency(BATT_LED_PIN, 2197.265)  // PWM freq. Hz
#define BATT_LED_ON()              analogWrite(BATT_LED_PIN, 4096)  // PWM max. duty (12 bits)
#define BATT_LED_OFF()             analogWrite(BATT_LED_PIN, 0)
#define BATT_LED_SET_DUTY(d)       analogWrite(BATT_LED_PIN, (4096*d)/100)  // 0 < d < 100 %
#define USB_VBUS_DET_CONFIG()      pinMode(VBUS_DET_PIN, INPUT)
#define USB_VBUS_DETECTED          (digitalRead(VBUS_DET_PIN) != 0)
#define SET_BUTTON_CONFIG()        pinMode(SET_BUTTON_PIN, INPUT)
#define SET_BUTTON_PRESSED         (digitalRead(SET_BUTTON_PIN) == 0)
#define SPKR_CTRL_CONFIG()         pinMode(SPKR_EN_PIN, OUTPUT)
#define SPEAKER_ENABLE()           digitalWrite(SPKR_EN_PIN, 1)
#define SPEAKER_DISABLE()          digitalWrite(SPKR_EN_PIN, 0)
#define BATT_EN_ASSERT()           {pinMode(BATT_EN_PIN, OUTPUT); digitalWrite(BATT_EN_PIN, 0);}
#define BATT_EN_NEGATE()           pinMode(BATT_EN_PIN, INPUT) 
#define HEADPHONE_DET_CONFIG()     pinMode(PHON_DET_PIN, INPUT)
#define HEADPHONE_PLUGGED_IN       (digitalRead(PHON_DET_PIN) != 0)
#define TESTPOINT_CONFIG()         pinMode(TESTPOINT_PIN, OUTPUT)  
#define TESTPOINT_SET_HIGH()       digitalWrite(TESTPOINT_PIN, 1)
#define TESTPOINT_SET_LOW()        digitalWrite(TESTPOINT_PIN, 0)
#define HEARTBEAT_LED_CONFIG()     pinMode(TEENSY_LED_PIN, OUTPUT)
#define HEARTBEAT_LED_ON()         digitalWrite(TEENSY_LED_PIN, 1)
#define HEARTBEAT_LED_OFF()        digitalWrite(TEENSY_LED_PIN, 0)
#define TOUCH_SENSE_DONE           ((TSI0_GENCS & TSI_GENCS_SCNIP) == 0)

#define GLOBAL_INT_ENABLE()        interrupts()
#define GLOBAL_INT_DISABLE()       noInterrupts()

// Bitmasks for TouchPadStates
#define OCT_UP  (1<<9)   
#define OCT_DN  (1<<8)
#define LH1     (1<<7)
#define LH2     (1<<6)
#define LH3     (1<<5)
#define RH1     (1<<4)
#define RH2     (1<<3)
#define RH3     (1<<2)
#define RH4     (1<<1)
#define LH4     (1<<0) 

extern bitmap_t  remi_logo_85x30[];  // bitmap image data

enum  Values_for_Display_Menu_Item
{
  DISPLAY_IDLE = 0,
  DISPLAY_PROMPT,
  DISPLAY_OCTAVE,
  DISPLAY_TRANSPOSE,
  DISPLAY_PRESET,
  DISPLAY_VIBRATO,
  DISPLAY_REVERB,
  DISPLAY_LEGATO,     // todo
  DISPLAY_PITCHBEND,  // todo
  DISPLAY_SPEAKER,
  DISPLAY_BATTERY,
  DISPLAY_SHUTDOWN,
  DISPLAY_SYSINFO,
  DISPLAY_PRESSURE,
  DISPLAY_CHANNEL,    // todo
  DISPLAY_UNDEF
};

enum  NoteOnOff_Task_States
{
  NOTE_OFF_IDLE = 0,          // Waiting for Note-On trigger condition
  NOTE_ON_PENDING,            // Delay to get Note-on velocity (pressure change)
  NOTE_ON_PLAYING,            // Waiting for Note-off or Legato "note-change" event
};


// Configuration data -- Persistent parameters maintained in EEPROM
//
typedef struct Eeprom_block_structure
{
  uint32  checkDword;               // Constant used to check data integrity
  
  uint8   MidiOutChannel;           // MIDI OUT channel (1..16, default 1)
  bool    MidiLegatoModeEnabled;    // MIDI Legato Mode Enabled (0)
  bool    VelocitySenseEnabled;     // Velocity sensing enabled (0)
  bool    PitchBendEnabled;         // Pitch Bend control enabled (0)
  uint8   VibratoMode;              // Vibrato control mode (0, 1, 2,..)
  uint8   ReverbMix_pc;             // Reverb. wet/dry mix (1..100 %)
  uint8   BatteryType;              // Battery type, 0: Alkaline, 1:NiMH 
  uint8   PresetLastSelected;       // Preset last selected (index 0..7)
  uint16  PressureFullScale;        // Sensor ADC count at maximum pressure
  uint16  PresetPatchNum[10];       // Patch ID numbers for the 8 presets
  
  uint32  EndOfDataBlockCode;       // Last entry, used to test if format has changed

} EepromBlock_t;

extern  EepromBlock_t  g_Config;    // structure holding instrument config. data


// Functions defined in remi_3 main source file
// ````````````````````````````````````````````
bool   CalibrateSensors();
void   CheckPowerSource();
void   CheckHeadphonePlug();
void   TouchPad_Monitor();
void   PresetSelect(uint8);
void   NoteOnOffStateTask();

// Player User-Interface functions
// ```````````````````````````````
void   Player_UI_Service();
void   DisplayUpdate();
void   DisplayStartupError();
void   DisplayStartupScreen();
void   DisplayPrompt(bool prep);
void   DisplayOctaveShift(bool prep);
void   DisplayTranspose(bool prep);
void   DisplayPreset(bool prep);
void   DisplayVibrato(bool prep);
void   DisplayReverb(bool prep);
void   DisplayLegato(bool prep);  // todo
void   DisplayPitchBend(bool prep);  // todo
void   DisplaySpeaker(bool prep);
void   DisplayBattery(bool prep);
void   DisplayShutdown(bool prep);
void   DisplaySystemInfo(bool prep);
void   DisplayPressure(bool prep);
void   DisplayMidiChannel(bool prep);  // todo
void   ButtonScan();
void   DiagnosticService();

// Sensor reading functions
// ````````````````````````
uint16  GetNoteOnOffState();
uint16  GetTouchPadStates();
uint16  GetBreathPressureLevel();
uint16  GetModulationPadForce();
int16   GetPitchBendData();
void    PitchBendAutoZero();

// EEPROM data storage & retieval functions
// `````````````````````````````````````````
void  DefaultConfigData(void);
BOOL  CheckConfigData(void);
void  FetchConfigData(void);
void  StoreConfigData(void);

// Low-level Touch-sense support functions
// ```````````````````````````````````````
int    touchSenseInit(uint8_t pin);
bool   touchSenseDone();
int    touchSenseRead();

#endif // _REMI_3_H
