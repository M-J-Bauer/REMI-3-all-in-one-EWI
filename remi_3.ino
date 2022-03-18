/*
   FileName:    remi_3.ino

   Overview:    Main source file for REMI_3 "All-in-One" EWI

   Processor:   Freescale MK20DX256 ARM Cortex M4  (F_CPU = 72 MHz)

   Platform:    Teensy 3.2 microcontroller dev board

   Toolchain:   Arduino IDE with Teensyduino support package

   Originated:  Nov. 2021, M.J.Bauer [www.mjbauer.biz]
*/
#include <EEPROM.h>   // Teensy EEPROM support
#include <Wire.h>     // For IIC (I2C, TWI) library
#include "remi_3.h"   // App-specific def's

// --------------  Global data  --------------------------------------------------------
//
EepromBlock_t  g_Config;      // structure holding configuration param's

// Array of touch readings corresponding to touch-pad pins (for diagnostics only):
uint16  touchReadings[12];

// --------------  Operational variables  ----------------------
//
static  bool    USB_powered;
static  bool    MIDI_enabled;
static  bool    DiagnosticModeEnabled;
static  bool    DisplayEnabled;
static  bool    ShutdownFlag;
static  bool    LowBatteryFlag;
static  bool    ButtonHitFlag;
static  uint8   LastDisplayItem;
static  uint8   SpeakerEnabled;

static  short   OctaveShift;  // multiple of 12 semitones
static  short   NoteTranspose;
static  uint32  ButtonPressTime_ms;
static  uint32  UserInactiveTimer_sec;
static  uint16  StartupErrorCode;
static  uint16  TouchPadStates;
static  uint8   NoteOnOffState;
static  uint32  TimeSinceLastNoteOff_ms;

static  uint16  PressureSensorReading;
static  uint16  PressureQuiescent;
static  uint16  PressureThresholdNoteOn;
static  uint16  PressureThresholdNoteOff;
static  uint16  ModulationSensorReading;
static  uint16  PitchBendSensorReading;
static  uint16  PitchBendZeroLevel;
static  uint16  BatteryVoltage_mV;
static  uint16  TouchPadScanTime_ms;  // (diagnostic usage only)

//=================================================================================================

void  setup(void)
{
  analogReadRes(12);            // set analogRead() resolution to 12 bits
  analogWriteRes(12);           // set DAC resolution to 12 bits
  //Wire1.setSCL(29);           // set IIC(1) SCL = pin 29 (SCL1) [redundant]
  //Wire1.setSDA(30);           // set IIC(1) SDA = pin 30 (SDA1) [redundant]
  Wire1.begin();                // set IIC(1) as master device
  Wire1.setClock(400*1000);     // set IIC(1) clock rate to 400kHz

  // Low-level I/O macros defined in "remi_3.h" ...
  BATT_LED_CONFIG();            
  HEARTBEAT_LED_CONFIG();
  USB_VBUS_DET_CONFIG();
  SET_BUTTON_CONFIG();
  SPKR_CTRL_CONFIG();
  HEADPHONE_DET_CONFIG();
  TESTPOINT_CONFIG();
  HEARTBEAT_LED_ON();
  BATT_LED_OFF();

  // Diagnostic Mode is activated by holding the 'SET' button pressed during power-up.
  if (SET_BUTTON_PRESSED) DiagnosticModeEnabled = TRUE;

  CheckPowerSource();  // Keep battery ON if no USB_VBUS power
  delay(100);
  if (!USB_powered) BATT_LED_ON();  // Indicate power is on

  if (CheckConfigData() == FALSE)  // Read Config data from EEPROM
  {
    StartupErrorCode |= ERROR_EEPROM_DATA_CHECK;
    DefaultConfigData();
  }

  if (CalibrateSensors() == FALSE)  // Calibrate pressure sensor, etc
  {
    StartupErrorCode |= ERROR_CALIBRATING_SENSOR;
  }

  // Restore synth settings to Preset last selected and start synth engine
  RemiSynthAudioInit();
  PresetSelect(g_Config.PresetLastSelected);
  RemiSynthReverbLevelSet(g_Config.ReverbMix_pc);
  RemiSynthVibratoModeSet(g_Config.VibratoMode);

  OLED_Display_Init();
  delay(100);   // for OLED on-board power to stabilize
  Disp_ClearScreen();
  DisplayStartupScreen();
  delay(1000);
  if (StartupErrorCode)
  {
    DisplayStartupError();
    delay(2000);
  }
  delay(1000);  // wait to view start-up/error screen
  Disp_ClearScreen();
  OLED_Display_Sleep();
  DisplayEnabled = FALSE;
  LastDisplayItem = DISPLAY_UNDEF;
  SPEAKER_ENABLE();  // Done after POR delay to avoid audio "pop"
  SpeakerEnabled = 1;  // (while headphone plug not inserted)
}


// Main background loop -- called continuously
//
void  loop(void)
{
  static  uint32  taskIntervalStart_TouchSense;
  static  uint32  taskPeriodStart1ms;
  static  uint32  taskPeriodStart5ms;
  static  uint32  taskPeriodStart50ms;
  static  uint8   ledFlashTimer;
  static  uint8   taskTimer250ms;

  // A *minimum* time interval of 50 microseconds is interposed between successive
  // calls to the TouchPad Monitor routine.  The interval may be longer than 50us,
  // depending on other tasks' execution times.
  if ((micros() - taskIntervalStart_TouchSense) >= 50)
  {
    taskIntervalStart_TouchSense = micros();
    TouchPad_Monitor();
  }

  if ((micros() - taskPeriodStart1ms) >= 1000)  // Do 1ms (1000us) periodic task
  {
    taskPeriodStart1ms = micros();
    RemiSynthProcess();
  }

  if ((millis() - taskPeriodStart5ms) >= 5)  // Do 5ms periodic tasks...
  {
    taskPeriodStart5ms = millis();
    ButtonScan();
    PressureSensorReading = analogRead(BREATH_SENSOR_PIN);
    if (!DiagnosticModeEnabled) NoteOnOffStateTask();
  }

  if ((millis() - taskPeriodStart50ms) >= 50)  // Do 50ms periodic tasks...
  {
    taskPeriodStart50ms = millis();
    ModulationSensorReading = analogRead(MODN_PAD_PIN);
    if (TouchPadStates != 0) UserInactiveTimer_sec = 0;  // Reset UI time-out
    
//  PitchBendAutoZero();  // TODO   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (!DiagnosticModeEnabled) 
    {
      Player_UI_Service();
      DisplayUpdate();
    }

    if (++taskTimer250ms >= 5)  // Do 250ms periodic tasks...
    {
      taskTimer250ms = 0;
      CheckPowerSource();
      CheckHeadphonePlug();
      if (DiagnosticModeEnabled) DiagnosticService();
    }

    HEARTBEAT_LED_OFF();
    if (LowBatteryFlag) BATT_LED_OFF();  // Pulse duty = 50ms
    
    if (++ledFlashTimer >= 40)  // Every 2 seconds...
    {
      ledFlashTimer = 0;
      HEARTBEAT_LED_ON();  // LED period = 2 sec. (Duty = 50ms)
      if (!USB_powered && LowBatteryFlag) BATT_LED_ON(); 
      UserInactiveTimer_sec += 2;
    }
  }

  if (MIDI_enabled)  { usbMIDI.read(); }  // Read and discard MIDI IN messages

  if (ButtonPressTime_ms > 5000) ShutdownFlag = TRUE;  // Force shut-down
}


/*
  Function performs initialization and calibration of player controls and sensors.
  Called once at power-on/reset and when user requests sensor recalibration.
*/
bool  CalibrateSensors()
{
  static uint32 startupTime;
  static uint16 lastReading;
  bool   status = TRUE;

  // Measure the pressure sensor signal level
  PressureSensorReading = analogRead(BREATH_SENSOR_PIN);
  lastReading = PressureSensorReading;
  startupTime = millis();
  // Take several readings;  apply 1st-order IIR filter
  while ((millis() - startupTime) < 200)
  {
    if ((millis() % 5) == 0)  // every 5 ms ...
    {
      PressureSensorReading -= lastReading / 4;
      PressureSensorReading += analogRead(BREATH_SENSOR_PIN) / 4;
      lastReading = PressureSensorReading;
    }
  }
  // Determine the quiescent pressure level and note on/off thresholds
  PressureQuiescent = PressureSensorReading;
  PressureThresholdNoteOn = PressureQuiescent + 32;
  PressureThresholdNoteOff = PressureQuiescent + 24;
  if (PressureQuiescent < 60 || PressureQuiescent > 1200)  // sensor fault
    status = FALSE;

  return status;
}


void  CheckPowerSource()
{
  int  battRawADC;
  int  threshold_mV = 2700;  // low-voltage warning threshold (Alkaline)

  battRawADC = analogRead(VBATT_PIN);
  BatteryVoltage_mV = (3300 * battRawADC) / 4096;

  if (USB_VBUS_DETECTED)  // running on USB VBUS power
  {
    USB_powered = TRUE;
    MIDI_enabled = TRUE;
    BATT_LED_OFF();
    BATT_EN_NEGATE();  // switch off battery power supply
    LowBatteryFlag = FALSE;
    ShutdownFlag = FALSE;
  }
  else  // USB VBUS not detected...
  {
    if (ShutdownFlag || USB_powered)  // VBUS high on last check (USB just disconnected)
    {
      BATT_EN_NEGATE();  // shut down
      delay(5000);
    }
    else  // running on battery power
    {
      USB_powered = FALSE;
      MIDI_enabled = FALSE;
      BATT_EN_ASSERT();  // battery DC-DC converter enabled
      if (!LowBatteryFlag) BATT_LED_SET_DUTY(5);  // 5% duty => battery OK
    }
    // Check battery voltage;  if low, set low-voltage warning flag  
    if (g_Config.BatteryType != 0) threshold_mV = 2200;  // NiMH (2 x 1.2V nominal)
    else threshold_mV = 2700;  // Alkaline (2 x 1.5V nominal)
    if (BatteryVoltage_mV < threshold_mV) LowBatteryFlag = TRUE;
    threshold_mV = (threshold_mV * 90) / 100;  // 90% of low-voltage warning -> shut down
    if (BatteryVoltage_mV < threshold_mV) ShutdownFlag = TRUE;
  }
  // Check auto-shutdown timer (only when battery-powered)
  if (!DiagnosticModeEnabled && !USB_powered 
  && (UserInactiveTimer_sec > AUTO_SHUTDOWN_TIMEOUT))
  {
    BATT_LED_OFF();
    BATT_EN_NEGATE();  // Switch off battery power supply
    delay(5000);
  }
  // Check sensibility of battery type (config. param.)
  if (g_Config.BatteryType != 0 && BatteryVoltage_mV > 2700)
  {
    // Voltage too high for NiMH -- change config setting to Alkaline (0)
    g_Config.BatteryType = 0;
    StoreConfigData();
  }
}


void   CheckHeadphonePlug()
{
  static bool previouslyPluggedIn;  // True if h/phone plug detected on last call
  static bool initDone;

  if (!initDone)  // once off initialization
  {
    previouslyPluggedIn = HEADPHONE_PLUGGED_IN;
    initDone = TRUE;
    return;
  }
  // If headphone plug is inserted, mute the internal speaker;
  // else if headphone plug removed (event) detected, restore last state of speaker.
  if (HEADPHONE_PLUGGED_IN) SPEAKER_DISABLE();
  else if (previouslyPluggedIn && !HEADPHONE_PLUGGED_IN) // 'unplugged' event
  {
    if (SpeakerEnabled) SPEAKER_ENABLE();
    else  SPEAKER_DISABLE();
  }
  previouslyPluggedIn = HEADPHONE_PLUGGED_IN;  // update plug status
}


/*````````````````````````````````````````````````````````````````````````````````````````````````
  Task to read touch-pad signal levels, hence to determine binary (on/off) states.
  Readings are updated as fast as possible. The time taken to read each touch-pad varies
  according to the applied capacitance, i.e. whether touched or not.

  Global variable 'TouchPadStates' holds the de-glitched logic states of the touch-pads.
      bit:   9    8    7    6    5    4    3    2    1    0
      pad:  OCT+ OCT- LH1  LH2  LH3  LH4  RH1  RH2  RH3  RH4

  A time-out is imposed on the wait time to read each input, because if a pad is touched,
  the effective capacitance to ground may be quite high (> 1000pF) resulting in excessive
  time to determine the precise value. If the time taken waiting for a touch reading is
  higher than 2ms (40 calls), it is assumed that the corresponding pad is touched.
*/
void  TouchPad_Monitor()
{
  // Array of 10 touch-pad inputs (pin numbers) to be read...
  // in the order: LH4, RH4, RH3, RH2, RH1, LH3, LH2, LH1, OCT-, OCT+
  static const uint8  touchPadPins[] = { 19, 18, 17, 16, 15, 33, 1, 0, 22, 23 };

  static bool    initialized;
  static short   pindex;  // index into array, touchPadPins[]
  static uint32  timeoutCount;  // call count (per pad)
  static uint32  scanStartTime; // for diagnostics only
  static uint32  stableReadingCount;
  static uint16  padStatesLastCycle;
  static uint16  padStatesThisCycle;
  int    touchReading = 0;
  
  if (!initialized)   // one-time initialization at startup
  {
    touchSenseInit(touchPadPins[0]);
    pindex = 0;
    timeoutCount = 0;
    scanStartTime = millis();
    initialized = TRUE;
    return;
  }

  if (TOUCH_SENSE_DONE || ++timeoutCount >= 40)
  {
    if (timeoutCount >= 40)
    {
      touchReading = touchSenseRead();  // discard reading
      SET_BIT(padStatesThisCycle, pindex);
      touchReadings[pindex] = 9999;  // capped value
    }
    else
    {
      touchReading = touchSenseRead();
      touchReadings[pindex] = touchReading;
      if (touchReading >= TOUCH_SENSE_THRESHOLD)
        SET_BIT(padStatesThisCycle, pindex);
      else  CLEAR_BIT(padStatesThisCycle, pindex);
    }

    if (++pindex >= NUMBER_OF_TOUCH_INPUTS) // next pin/pad
    {
      pindex = 0;  // Start new reading cycle and apply de-glitch filter
      if (padStatesThisCycle == padStatesLastCycle) stableReadingCount++;
      else  stableReadingCount = 0;
      if (stableReadingCount >= 3) TouchPadStates = padStatesLastCycle; // update
      padStatesLastCycle = padStatesThisCycle;
      TouchPadScanTime_ms = millis() - scanStartTime;  // (diagnostic use only)
      scanStartTime = millis();
    }
    touchSenseInit(touchPadPins[pindex]);
    timeoutCount = 0;
  }
}


/*````````````````````````````````````````````````````````````````````````````````````````````````
   Function:    Find MIDI note number from key/fingering pattern,
                adjusted by the "Octave Shift" and "Note Transpose" operational variables.

   Entry arg:   (uint16) fingerPattern = Touch-pad electrode bits, incl. octave pads.

   Return val:  (uint8) MIDI note number between 23 (B0) and 108 (C8).

   ````````````````````````````````````````````````````````````````````````````````````````
   Touch-pad configuration on REMI 3:

                         |    octave   | ----------- s e m i t o n e ----------- |  #  |
      Finger position -> | OCT+ | OCT- | LH1 | LH2 | LH3 | RH1 | RH2 | RH3 | RH4 | LH4 |
      Touch pads bit  -> |  9   |  8   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |

   ````````````````````````````````````````````````````````````````````````````````````````
*/
uint8  NoteNumberFromKeyPattern(uint16 fingerPattern)
{
  // Array gives MIDI note number from finger pattern, without LH4 and octave selection.
  static  uint8  baseNoteNumberLUT[] =
  {
    // RH1..RH4 finger pattern (4 LS bits of table index) =
    // 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
        37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37, // LH = 000
        48,  48,  48,  48,  48,  48,  48,  48,  47,  46,  46,  46,  45,  44,  44,  44, // LH = 001
        36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36, // LH = 010
        43,  42,  42,  42,  42,  42,  42,  42,  41,  41,  41,  41,  40,  39,  38,  36, // LH = 011
        35,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34, // LH = 100
        34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34, // LH = 101
        33,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32, // LH = 110
        31,  30,  30,  30,  30,  30,  30,  30,  29,  29,  29,  29,  28,  27,  26,  24  // LH = 111
  };

  uint8   noteNumber;  // return value
  uint8   baseNote, octave, padLH4;
  uint8   octavePads, top7Fingers;
  short   transposedNote;

  octavePads = (fingerPattern >> 8) & 3;
  if (octavePads == 2) octave = 2;        // Upper pad => highest octave
  else if (octavePads == 3) octave = 1;   // Both pads => middle octave
  else  octave = 0;                       // Bottom pad => lowest octave

  top7Fingers = (fingerPattern >> 1) & 0x7F;   // Drop LH4 and strip octave pads
  padLH4 = fingerPattern & 1;
  baseNote = baseNoteNumberLUT[top7Fingers];   // Note number before octave applied
  noteNumber = baseNote + (octave * 12) + 24;  // Normal range is 48 (C3) to 96 (C7)

  // Check notes which must be sharpened if LH4 is touched (C and F only)
  if (baseNote == 24 || baseNote == 29 || baseNote == 36 ||  baseNote == 41 || baseNote == 48)
  {
    if (padLH4) noteNumber++;  // Sharpen the note
  }
  // Adjust noteNumber according to player 'octave shift' and 'note transpose' settings
  transposedNote = (short) noteNumber + OctaveShift;    // +/- 0..24 semitones
  if (transposedNote >= 12 && transposedNote <= 96) noteNumber = transposedNote;
  transposedNote = (short) noteNumber + NoteTranspose;  // +/- 0..12 semitones
  if (transposedNote >= 12 && transposedNote <= 96) noteNumber = transposedNote;

  return  noteNumber;
}


/*````````````````````````````````````````````````````````````````````````````````````````````````
   Function:  NoteOnOffStateTask()

   Background task (state machine) executed every 5 milliseconds.

   The function monitors data acquired by the touch-pad sensor routine, looking for
   any change in status that signals an "event", e.g. Note-On, Note-Off, Note-Change,
   and sends MIDI commands accordingly.

   The task also sends MIDI Expression (Pressure), Modulation and Pitch-Bend messages
   at the time intervals configured.
*/
void  NoteOnOffStateTask()
{
  static  uint32  stateTimer_ms;
  static  uint32  controllerUpdateTimer_ms;
  static  uint8   noteNumPlaying;
  static  uint8   velocity;
 
  uint16  pressure_14b, modulation_14b;
  uint8   pressure_Hi, modulation_Hi;
  int16   pitch_bend_14b;
  uint8   midiChan = g_Config.MidiOutChannel;
  uint8   noteNumber = NoteNumberFromKeyPattern(TouchPadStates);
  uint8   top3Fingers = (TouchPadStates >> 5) & 7;  // Isolate LH1, LH2 & LH3 pads
  uint8   octavePads  = (TouchPadStates >> 8) & 3;  // Isolate OCT+ & OCT- pads
  bool    isValidNote = (octavePads != 0) && (top3Fingers != 0);
  bool    doSendNoteOn = FALSE;
 
  switch (NoteOnOffState)
  {
    case NOTE_OFF_IDLE:
      {
        // A new note is triggered when the pressure sensor signal rises above the
        // NoteOnPressureThreshold (raw ADC count).
        if (isValidNote && (PressureSensorReading >= PressureThresholdNoteOn))
        {
          if (DisplayEnabled)  // Blank the OLED display while note playing
          {
            OLED_Display_Sleep();
            DisplayEnabled = FALSE;
          }
          if (SpeakerEnabled && !HEADPHONE_PLUGGED_IN) SPEAKER_ENABLE();
          stateTimer_ms = 0;    // start delay for velocity acquisition
          NoteOnOffState = NOTE_ON_PENDING;
        }
        
        controllerUpdateTimer_ms = 0;
        TimeSinceLastNoteOff_ms += 5;
        break;
      }
    case NOTE_ON_PENDING:
      {
        TimeSinceLastNoteOff_ms = 0;
        controllerUpdateTimer_ms = 0;

        if (!g_Config.VelocitySenseEnabled)  // use fixed velocity value
        {
          velocity = 64;
          doSendNoteOn = TRUE;
        }
        else if (stateTimer_ms >= NOTE_ON_VELOCITY_DELAY)  // ready to acquire velocity
        {
          pressure_14b = GetBreathPressureLevel();  // change since note trigger
          velocity = pressure_14b >> 7;
          doSendNoteOn = TRUE;
        }
        // else... Don't send Note-On;  remain in this state.

        if (doSendNoteOn)
        {
          RemiSynthNoteOn(noteNumber, velocity);
          if (MIDI_enabled) usbMIDI.sendNoteOn(noteNumber, velocity, midiChan);
          noteNumPlaying = noteNumber;
          NoteOnOffState = NOTE_ON_PLAYING;
        }
        break;
      }
    case NOTE_ON_PLAYING:
      {
        // A Note-off is sent when the pressure sensor signal falls below the Note-Off
        // pressure threshold.
        if (PressureSensorReading < PressureThresholdNoteOff)
        {
          RemiSynthNoteOff();
          if (MIDI_enabled) usbMIDI.sendNoteOff(noteNumPlaying, 0, midiChan);
          NoteOnOffState = NOTE_OFF_IDLE;
          break;
        }

        // Look for a change in fingering pattern with any valid note selected;
        // this signals a "Legato" note change.  Remain in this state.
        if (isValidNote && (noteNumber != noteNumPlaying))
        {
          RemiSynthNoteOn(noteNumber, velocity);
          if (MIDI_enabled && g_Config.MidiLegatoModeEnabled)
          {
            usbMIDI.sendNoteOn(noteNumber, velocity, midiChan);  // New note ON
            usbMIDI.sendNoteOff(noteNumPlaying, 0, midiChan);  // Old note OFF
          }
          else if (MIDI_enabled)
          {
            usbMIDI.sendNoteOff(noteNumPlaying, 0, midiChan);  // Old note OFF
            usbMIDI.sendNoteOn(noteNumber, velocity, midiChan);  // New note ON
          }
          noteNumPlaying = noteNumber;  // update
        }

        pressure_14b = GetBreathPressureLevel();
        pressure_Hi = pressure_14b >> 7;
        modulation_14b = GetModulationPadForce();
        modulation_Hi = modulation_14b >> 7;
        pitch_bend_14b = GetPitchBendData();

        // Update synth expression (pressure), modulation and pitch-bend signals
        RemiSynthExpression(pressure_14b);
        RemiSynthModulation(modulation_14b);
        RemiSynthPitchBend(pitch_bend_14b);

        // Send MIDI expression (breath pressure) message on CC02 (every 5ms)
        if (MIDI_enabled) usbMIDI.sendControlChange(MIDI_EXPRN_CC, pressure_Hi, midiChan);

        // Send other MIDI control-change messages (when pending)
        if (MIDI_enabled && controllerUpdateTimer_ms >= MIDI_MODN_MSG_INTERVAL)
        {
          usbMIDI.sendControlChange(1, modulation_Hi, midiChan);
          usbMIDI.sendPitchBend(pitch_bend_14b, midiChan);
          controllerUpdateTimer_ms = 0;
        }
        controllerUpdateTimer_ms += 5;
        break;
      }
    default:
      NoteOnOffState = NOTE_OFF_IDLE;
      break;
  }  // end switch
  stateTimer_ms += 5;
}


/*
   Function:     Select an Instrument Preset.

   Entry args:   preset = PRESET number (0..7)
                 NB: The user interface displays preset 0 as preset number 8.
*/
void  PresetSelect(uint8 preset)
{
  preset = preset & 7;  // preset index must be 0..7

  // Load and activate the REMI synth patch assigned to this Preset...
  RemiSynthPatchSelect(g_Config.PresetPatchNum[preset]);

  g_Config.PresetLastSelected = preset;  // Save this Preset for next power-on
  StoreConfigData();
}


/*````````````````````````````````````````````````````````````````````````````````````````````````
   Player User Interface (UI) service routine.
   Periodic Background task executed every 50 milliseconds.

   The Player UI comprises the 'SET' button, OLED graphics display (128 x 64 px)
   and the 10 touch-pads.  The touch-pads select a "menu" item for view/setting.

   Refer to "REMI 3 User Guide" for details of operation.
*/
void   Player_UI_Service()
{
  static uint8 reverbStep[] = { 0, 5, 10, 15, 20, 25, 35, 50 };
  int  idx;
  //uint8   channel = g_Config.MidiOutChannel;
  short   preset = g_Config.PresetLastSelected;

  if (NoteOnOffState != NOTE_OFF_IDLE)  return;  // A note is playing now
  if (DiagnosticModeEnabled) return;  // Diag. mode is a conflicting UI

  if (ButtonHitFlag)
  {
    ButtonHitFlag = 0;
    UserInactiveTimer_sec = 0;  // Reset UI time-out

    if (TouchPadStates == 0)
    {
      OLED_Display_Wake();
      DisplayEnabled = TRUE;
      LastDisplayItem = DISPLAY_UNDEF;  // trigger idle/menu screen
      SPEAKER_DISABLE();  // mute speaker (OLED IIC bus activity causes audio noise)
    }
    else if (TouchPadStates == (OCT_UP + OCT_DN)) OctaveShift = 0;  // clear octave shift
    else if (TouchPadStates == OCT_UP)
    {
      if (OctaveShift <= 12) OctaveShift += 12;  // shift up 12 semitones
    }
    else if (TouchPadStates == OCT_DN)
    {
      if (OctaveShift >= -12) OctaveShift -= 12;  // shift down 12 semitones
    }
    else if (TouchPadStates == (LH1 + LH2)) NoteTranspose = 0;  // clear transpose
    else if (TouchPadStates == LH1)
    {
      if (NoteTranspose < 11) NoteTranspose++;  // shift up 1 semitone
    }
    else if (TouchPadStates == LH2)
    {
      if (NoteTranspose > 1) NoteTranspose--;  // shift down 1 semitone
    }
    else if (TouchPadStates == RH1)
    {
      if (++preset > 7)  preset = 0;   // Increment Preset
      PresetSelect(preset);            // Save and activate 
    }
    else if (TouchPadStates == RH2)
    {
      if (--preset < 0)  preset = 7;   // Decrement Preset
      PresetSelect(preset);            // Save and activate 
    }
    else if (TouchPadStates == LH4)
    {
      // Set vibrato mode -- Scroll thru modes 0-1-2-0 (OFF, Mod.Pad, Auto)
      if (g_Config.VibratoMode == 0) g_Config.VibratoMode = 1;
      else if (g_Config.VibratoMode == 1) g_Config.VibratoMode = 2;
      else  g_Config.VibratoMode = 0;   // OFF
      StoreConfigData();
      RemiSynthVibratoModeSet(g_Config.VibratoMode);
    }
    else if (TouchPadStates == LH3) 
    {
        // Set Pitch Bend -- Toggle on/off (Other synth PB modes not supported)
      g_Config.PitchBendEnabled = !g_Config.PitchBendEnabled;
      StoreConfigData();
        if (g_Config.PitchBendEnabled) RemiSynthPitchBendModeSet(1);
        else  RemiSynthPitchBendModeSet(0);
    }   
    else if (TouchPadStates == RH3)
    {
      // Set reverb level (scroll up thru 8 fixed steps)
      for (idx = 0; idx < sizeof(reverbStep); idx++)
      {
        if (g_Config.ReverbMix_pc == reverbStep[idx]) break;
      }
      if (++idx >= sizeof(reverbStep)) idx = 0;
      g_Config.ReverbMix_pc = reverbStep[idx];
      StoreConfigData();
      RemiSynthReverbLevelSet(g_Config.ReverbMix_pc);
    }
    else if (TouchPadStates == RH4 && !HEADPHONE_PLUGGED_IN) 
    {
      SpeakerEnabled = !SpeakerEnabled;  // toggle state
      if (SpeakerEnabled) SPEAKER_ENABLE();  // update SPKR_EN output
      else SPEAKER_DISABLE();
    }
    else if (TouchPadStates == (LH3 + LH4))
    {
      g_Config.MidiLegatoModeEnabled = !g_Config.MidiLegatoModeEnabled;  
      StoreConfigData();
    }
    else if (TouchPadStates == (RH3 + RH4))
    {
      g_Config.BatteryType ^= 1;   // Toggle... 0: Alkaline, 1:NiMH
      StoreConfigData();
    }
    else if (TouchPadStates == (LH3 + RH1))
    {
      g_Config.PressureFullScale = PressureSensorReading; 
      StoreConfigData();
    }
    else if (TouchPadStates == (LH4 + RH4)) ShutdownFlag = TRUE;
    
  } // end if (ButtonHitFlag())
}

/*
   Routine to update the graphical OLED display during normal operating mode.
   Background task called at 50 millisecond intervals.

   The display is normally blanked out;  it is activated by any touch-pad(s) touched;
   also for a fixed time during start-up and shut-down (on battery power).

   While activated, the display shows the "menu" item selected by the touch-pad(s) that
   are currently touched, if any, with the current value of the respective parameter
   or operational variable. It also shows what will happen if the PRE/SET button is hit.
*/
void  DisplayUpdate()
{
  uint8 displayItem;
  bool isNewScreen = FALSE;

  if (NoteOnOffState != NOTE_OFF_IDLE)  return;  // A note is playing now

  if (UserInactiveTimer_sec >= 5)  // Time-out... no UI activity
  {
    Disp_ClearScreen();
    OLED_Display_Sleep();
    DisplayEnabled = FALSE;
//  LastDisplayItem = DISPLAY_UNDEF;
    if (SpeakerEnabled && !HEADPHONE_PLUGGED_IN) SPEAKER_ENABLE();
  }

  if (TouchPadStates == 0) displayItem = DISPLAY_PROMPT;
  else if (TouchPadStates == OCT_UP || TouchPadStates == OCT_DN)
    displayItem = DISPLAY_OCTAVE;
  else if (TouchPadStates == (LH1 + LH2)
  || TouchPadStates == LH1 || TouchPadStates == LH2)
    displayItem = DISPLAY_TRANSPOSE;
  else if (TouchPadStates == (RH1 + RH2)
  || TouchPadStates == RH1 || TouchPadStates == RH2)
    displayItem = DISPLAY_PRESET;
  else if (TouchPadStates == LH3)  displayItem = DISPLAY_PITCHBEND;
  else if (TouchPadStates == LH4)  displayItem = DISPLAY_VIBRATO;
  else if (TouchPadStates == RH3)  displayItem = DISPLAY_REVERB;
  else if (TouchPadStates == RH4)  displayItem = DISPLAY_SPEAKER;
  else if (TouchPadStates == (LH3 + LH4))  displayItem = DISPLAY_LEGATO;
  else if (TouchPadStates == (RH3 + RH4))  displayItem = DISPLAY_BATTERY;
  else if (TouchPadStates == (LH4 + RH4))  displayItem = DISPLAY_SHUTDOWN;
  else if (TouchPadStates == (LH3 + RH3))  displayItem = DISPLAY_SYSINFO;
  else if (TouchPadStates == (LH3 + RH1))  displayItem = DISPLAY_PRESSURE;
  else  displayItem = DISPLAY_IDLE;  // No valid touch-pad combo selected

  if (displayItem != LastDisplayItem)
  {
    Disp_ClearScreen();  // prepare new screen
    Disp_PosXY(0, 13);
    Disp_DrawLineHoriz(128);
    LastDisplayItem = displayItem;
    isNewScreen = TRUE;
  }
/*
  if ((displayItem != DISPLAY_IDLE) && !DisplayEnabled)
  {
    OLED_Display_Wake();
    DisplayEnabled = TRUE;
    SPEAKER_DISABLE();
  }
*/
  switch (displayItem)
  {
    case DISPLAY_PROMPT:
      DisplayPrompt(isNewScreen);
      break;
    case DISPLAY_OCTAVE:
      DisplayOctaveShift(isNewScreen);
      break;
    case DISPLAY_TRANSPOSE:
      DisplayTranspose(isNewScreen);
      break;
    case DISPLAY_PRESET:
      DisplayPreset(isNewScreen);
      break;
    case DISPLAY_VIBRATO:
      DisplayVibrato(isNewScreen);
      break;
    case DISPLAY_REVERB:
      DisplayReverb(isNewScreen);
      break;
    case DISPLAY_SPEAKER:
      DisplaySpeaker(isNewScreen);
      break;
    case DISPLAY_BATTERY:
      DisplayBattery(isNewScreen);
      break;
    case DISPLAY_SHUTDOWN:
      DisplayShutdown(isNewScreen);
      break;
    case DISPLAY_SYSINFO:
      DisplaySystemInfo(isNewScreen);
      break;
    case DISPLAY_PRESSURE:
      DisplayPressure(isNewScreen);
      break;
    default:  break;
  } // end switch
}


void  DisplayStartupError()
{
  DisplayTextCentered12p(0, "Self-test Error");  // title bar
  Disp_PosXY(0, 13);
  Disp_DrawLineHoriz(128);
  Disp_SetFont(MONO_8_NORM);
    
  if (StartupErrorCode & ERROR_CALIBRATING_SENSOR)
  {
    Disp_PosXY(0, 16);
    Disp_PutText("Pressure sensor");
    Disp_PosXY(0, 26);
    Disp_PutText("  calibration.");
  }
  
  if (StartupErrorCode & ERROR_EEPROM_DATA_CHECK)
  {
    Disp_PosXY(0, 36);
    Disp_PutText("EEPROM defaulted.");
  }
}


void   DisplayStartupScreen()
{
  Disp_Mode(SET_PIXELS);
  Disp_SetFont(PROP_12_BOLD);
  Disp_PosXY(32, 0);
  Disp_PutText("Bauer");
  Disp_PosXY(12, 12);
  Disp_PutImage(remi_logo_85x30, 85, 30);
  Disp_SetFont(PROP_12_BOLD);
  Disp_PosXY(102, 22);
  Disp_PutText("3");
  Disp_SetFont(PROP_8_NORM);
  Disp_PosXY(32, 48);
  Disp_PutText("Initializing...");
}


void  DisplayPrompt(bool prep)
{
  if (prep)  // once only
  {
    DisplayTextCentered12p(0, "- Menu -");  // title bar

    Disp_SetFont(PROP_12_NORM);
    Disp_PosXY(0, 20);
    Disp_PutText("Select menu item");
    Disp_PosXY(0, 34);
    Disp_PutText("using touch pads");
  }
}


void  DisplayOctaveShift(bool prep)
{
  static int  lastValueShown;

  if (prep)  // prepare new screen
  {
    DisplayTextCentered12p(0, "Octave Shift");  // title bar
    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(84, 28);
    Disp_PutText("octave");
    lastValueShown = 999;  // bad value forces data refresh
  }
  // Update variable data, but only if it has changed...
  if (OctaveShift != lastValueShown)
  {
    Disp_PosXY(48, 18);
    Disp_ClearArea(32, 20);
    Disp_SetFont(PROP_24_NORM);
    if (OctaveShift > 0) Disp_PutChar('+');
    else if (OctaveShift == 0) Disp_PutChar(' ');
    Disp_PutDecimal(OctaveShift/12, 1);  // OctaveShift = semitones
    lastValueShown = OctaveShift;

    // Show 'SET' button action
    Disp_PosXY(16, 48);
    Disp_ClearArea(96, 16);
    if (TouchPadStates == OCT_UP && OctaveShift < 1)
        DisplayTextCenteredInBox(48, "Up (+1)");
    if (TouchPadStates == OCT_DN && OctaveShift > -1)
        DisplayTextCenteredInBox(48, "Down (-1)");
  }
}


void  DisplayTranspose(bool prep)
{
  static int  lastValueShown;
  static uint16 previousTouchPadStates;

  if (prep)  // prepare new screen
  {
    DisplayTextCentered12p(0, "Transpose");  // title bar
    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(84, 20);
    Disp_PutText("semi-");
    Disp_PosXY(84, 30);
    Disp_PutText("tone(s)");
    lastValueShown = 999;  // force data refresh
  }
  // Update variable data, but only if it has changed...
  if (NoteTranspose != lastValueShown || TouchPadStates != previousTouchPadStates)
  {
    Disp_PosXY(48, 18);
    Disp_ClearArea(30, 20);
    Disp_SetFont(PROP_24_NORM);

    if (NoteTranspose > 0) Disp_PutChar('+');
    if (NoteTranspose == 0) Disp_PutChar(' ');
    Disp_PutDecimal(NoteTranspose, 1);
    lastValueShown = NoteTranspose;

    // Show 'SET' button action
    Disp_PosXY(16, 48);
    Disp_ClearArea(96, 16);
    if (TouchPadStates == (LH1 + LH2) && NoteTranspose != 0)
        DisplayTextCenteredInBox(48, "Clear (0)");
    else if (TouchPadStates == LH1 && NoteTranspose < 12)
        DisplayTextCenteredInBox(48, "Up (+1)");
    else if (TouchPadStates == LH2 && NoteTranspose > -12)
        DisplayTextCenteredInBox(48, "Down (-1)");
  }
  previousTouchPadStates = TouchPadStates;
}


void  DisplayPreset(bool prep)
{
  static int  lastValueShown;
  static uint16 previousTouchPadStates;
  const char *patchName;
  int  idx;
  int  preset = g_Config.PresetLastSelected;
  int  patchID = g_Config.PresetPatchNum[preset];

  idx = GetPatchTableIndex(patchID);
  if (idx < 0) idx = 0;  // error 
  patchName = g_PatchProgram[idx].PatchName;

  if (prep)
  {
    DisplayTextCentered12p(0, "PRESET");  // title bar
    lastValueShown = 999;
  }
  // Update variable data, but only if it has changed...
  if (preset != lastValueShown  || TouchPadStates != previousTouchPadStates)
  {
    Disp_PosXY(58, 18);
    Disp_ClearArea(16, 20);
    Disp_SetFont(PROP_24_NORM);
    if (preset == 0) Disp_PutText("8"); // Preset 0 is displayed as '8'
    else  Disp_PutDecimal(preset, 1);
    lastValueShown = preset;

    Disp_PosXY(0, 48);
    Disp_ClearArea(128, 16);
    // If both pads RH1 & RH2 touched, show the preset patch name
    if (TouchPadStates == (RH1 + RH2))
    {
      Disp_PosXY(0, 50);
      Disp_SetFont(PROP_12_NORM);
      if (strlen(patchName) > 15)  Disp_PutText(patchName);
      else  DisplayTextCentered12p(50, patchName);
    }
    // Otherwise, show 'SET' button action
    if (TouchPadStates == RH1) DisplayTextCenteredInBox(48, "Up (+1)");
    if (TouchPadStates == RH2) DisplayTextCenteredInBox(48, "Down (-1)");
  }
  previousTouchPadStates = TouchPadStates;
}


void  DisplayVibrato(bool prep)
{
  static int  lastValueShown;
  int  vibMode = g_Config.VibratoMode;

  if (prep)
  {
    DisplayTextCentered12p(0, "Vibrato");  // title bar
    Disp_SetFont(MONO_8_NORM);
    Disp_PosXY(28, 18);
    Disp_PutText("Control Mode");
    // Show 'SET' button action (constant)
    DisplayTextCenteredInBox(48, "Change");
    lastValueShown = 999;
  }
  // Update variable data, but only if it has changed...
  if (vibMode != lastValueShown)
  {
    Disp_PosXY(32, 32);
    Disp_ClearArea(64, 12);
    Disp_SetFont(PROP_12_BOLD);
    if (vibMode == 0) Disp_PutText("  OFF  ");
    if (vibMode == 1) Disp_PutText("Mod.Pad");
    if (vibMode == 2) Disp_PutText(" Auto. ");
    lastValueShown = vibMode;
  }
}


void  DisplayReverb(bool prep)
{
  static int  lastValueShown;
  int  reverbMix = g_Config.ReverbMix_pc;

  if (prep)
  {
    DisplayTextCentered12p(0, "Reverb");  // title bar
    Disp_SetFont(MONO_8_NORM);
    Disp_PosXY(22, 18);
    Disp_PutText("Reverb Level");
    // Show 'SET' button action (constant)
    DisplayTextCenteredInBox(48, "Adjust");
    lastValueShown = 999;
  }
  // Update variable data, but only if it has changed...
  if (reverbMix != lastValueShown)
  {
    Disp_PosXY(48, 32);
    Disp_ClearArea(40, 12);
    Disp_SetFont(PROP_12_BOLD);
    Disp_PutDecimal(reverbMix, 2);
    Disp_SetFont(PROP_12_NORM);
    Disp_PutText(" %");
    lastValueShown = reverbMix;
  }
}


void  DisplaySpeaker(bool prep)
{
  static uint8  lastValueShown;

  if (prep)  // prepare new screen
  {
    DisplayTextCentered12p(0, "Speaker");  // title bar
    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(8, 18);
    Disp_PutText("The built-in speaker is");
    lastValueShown = 0xFF;  // force refresh
  }
  // Update variable data, but only if it has changed...
  if (SpeakerEnabled != lastValueShown)
  {
    Disp_SetFont(PROP_12_BOLD);
    Disp_PosXY(40, 32);
    Disp_ClearArea(50, 12);
    if (HEADPHONE_PLUGGED_IN) Disp_PutText("Muted");
    else if (SpeakerEnabled != 0) Disp_PutText("  On ");
    else if (SpeakerEnabled == 0) Disp_PutText("  Off");
    lastValueShown = SpeakerEnabled;  // may be 0, 1 or 0xFF

    // Show 'SET' button action (dependent on phones plug, etc)
    Disp_PosXY(16, 48);
    Disp_ClearArea(96, 16);
    if (HEADPHONE_PLUGGED_IN) DisplayTextCentered8p(50, "(Unplug H/phones?)");
    else if (SpeakerEnabled) DisplayTextCenteredInBox(48, "Turn Off");
    else DisplayTextCenteredInBox(48, "Turn On");
  }
}


void  DisplayBattery(bool prep)
{
  static uint8  lastValueShown;
  char  digit;

  if (prep)
  {
    DisplayTextCentered12p(0, "Battery");  // title bar
    // Show 'SET' button action (constant)
    DisplayTextCenteredInBox(48, "Set Type");
    lastValueShown = 255;
  }
  // Update variable data, but only if it has changed...
  if (g_Config.BatteryType != lastValueShown)
  {
    Disp_PosXY(0, 16);  // ???
    Disp_ClearArea(128, 32);  // ???

    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(0, 20);
    Disp_PutText("Status:  ");
    Disp_SetFont(MONO_8_NORM);
      if (LowBatteryFlag) Disp_PutText("LOW !");  
      else  Disp_PutText("Good");

    // Show battery voltage in format "#.##V" -- without using sprintf()
    Disp_SetFont(PROP_12_NORM);
    Disp_PosXY(90, 20);
    digit = '0' + (BatteryVoltage_mV / 1000) % 10;
    Disp_PutChar(digit);
    Disp_PutChar('.');
    digit = '0' + (BatteryVoltage_mV / 100) % 10;
    Disp_PutChar(digit);
    digit = '0' + (BatteryVoltage_mV / 10) % 10;
    Disp_PutChar(digit);
    Disp_PutChar('V');

    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(0, 32);
    Disp_PutText("Type:  ");
    Disp_SetFont(MONO_8_NORM);
    if (g_Config.BatteryType == 0) Disp_PutText("Alkaline");
    else  Disp_PutText("NiMH");

    lastValueShown = g_Config.BatteryType;
  }
}


void  DisplayShutdown(bool prep)
{
  if (!USB_powered && prep)  // once only
  {
    DisplayTextCentered12p(0, "Shutdown");  // title bar

    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(0, 20);
    Disp_PutText("Press `SET' button now");
    Disp_PosXY(0, 32);
    Disp_PutText("to switch off battery.");

    DisplayTextCenteredInBox(48, "Power Off");
  }
}


void  DisplaySystemInfo(bool prep)
{
  if (prep)  // once only
  {
    DisplayTextCentered12p(0, "About REMI 3");

    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(0, 16);
    Disp_PutText("...");  // reserved line (TBD)

    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(0, 26);
    Disp_PutText("Firmware version: ");
    Disp_SetFont(MONO_8_NORM);
    Disp_PutDecimal(BUILD_VER_MAJOR, 1);
    Disp_PutChar('.');
    Disp_PutDecimal(BUILD_VER_MINOR, 1);
    Disp_PutChar('.');
    Disp_PutDecimal(BUILD_VER_DEBUG, 1);

    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(0, 36);
    Disp_PutText("Design & software by ...");
    Disp_SetFont(MONO_8_NORM);
    Disp_PosXY(20, 46);
    Disp_PutText("Michael J Bauer");
    Disp_PosXY(26, 56);
    Disp_SetFont(PROP_8_NORM);
    Disp_PutText("www.mjbauer.biz");
  }
}


void  DisplayPressure(bool prep)
{
  static unsigned lastValueShown;
  char  numbuf[8];
  
  if (prep)  // once only
  {
    DisplayTextCentered12p(0, "Max.Pressure");  // title bar

    Disp_SetFont(PROP_8_NORM);
    Disp_PosXY(0, 28);
    Disp_PutText("Press SET button while");
    Disp_PosXY(0, 38);
    Disp_PutText("blowing full pressure.");

    DisplayTextCenteredInBox(48, "Set");
    lastValueShown = 9999;  // force display refresh
  }
  
  if (g_Config.PressureFullScale != lastValueShown)
  {
    Disp_PosXY(0, 16); 
    Disp_ClearArea(128, 10); 
    Disp_SetFont(MONO_8_NORM);
    Disp_PosXY(0, 16);
    Disp_PutText("Last setting: ");
    itoa(g_Config.PressureFullScale, numbuf, 10);
    Disp_PutText(numbuf);

    lastValueShown = g_Config.PressureFullScale;
  }
}


/*
  |  Routine to monitor 'SET' button state and to detect button hits.
  |  Background task called at 5ms intervals.
  |
  |  If a button hit is detected, ButtonHitFlag is set TRUE. Caller must clear flag.
  |  If the button is held pressed, the variable ButtonPressTime_ms will be non-zero.
  |  While the button is released, ButtonPressTime_ms will be zero.
*/
void  ButtonScan()
{
  static  uint32 buttonReleaseTime_ms;
  static  uint8  buttonStateLastScan;    // 0: Released, 1: Pressed
  static  uint8  buttonStateDeglitched;

  if (SET_BUTTON_PRESSED)
  {
    ButtonPressTime_ms += 5;
    buttonReleaseTime_ms = 0;
  }
  else  // Button released
  {
    buttonReleaseTime_ms += 5;
    ButtonPressTime_ms = 0;
  }

  // Apply de-glitch / de-bounce filter
  if (ButtonPressTime_ms > 45)  buttonStateDeglitched = 1;
  if (buttonReleaseTime_ms > 95)  buttonStateDeglitched = 0;

  if (buttonStateDeglitched != 0 && buttonStateLastScan == 0) 
    ButtonHitFlag = 1;

  buttonStateLastScan = buttonStateDeglitched;
}


/*`````````````````````````````````````````````````````````````````````````````````````````````````
 * Diagnostic Mode Service Routine.
 * ````````````````````````````````
 * Periodic background task executed only while "diagnostic mode" is active.
 * The function may be hacked for debug and testing purposes.
 */
void  DiagnosticService()
{
  static short diagnosticStep;
  static bool prepDone; 
  static bool doRefresh;  // True => refresh display (static content)

  if (!prepDone)  // One-time initialization
  {
    Disp_ClearScreen();
    Disp_SetFont(PROP_12_NORM);
    Disp_PosXY(0, 0); 
    Disp_PutText("Diagnostic mode");
    Disp_PosXY(0, 16); 
    if (StartupErrorCode)
    {
      Disp_PutText("Error code: ");
      Disp_PutHexByte((uint8)StartupErrorCode);
    }
    else  Disp_PutText("( No errors :)");
    Disp_PosXY(0, 32);
    Disp_PutText("VBUS.DET: ");
    if (USB_VBUS_DETECTED) Disp_PutText("High  ");
    else  Disp_PutText("Low  ");

    DisplayTextCenteredInBox(48, "Next");
    diagnosticStep = -1;  // until button hit
    doRefresh = TRUE;
    prepDone = TRUE;
  }

  if (diagnosticStep == 0)
  {
    // Show touch-pad readings
    if (doRefresh)
    {
      Disp_SetFont(PROP_12_NORM);
      Disp_PosXY(0, 0);  
      Disp_PutText("Pad states:");
      Disp_PosXY(0, 13); 
      Disp_PutText("LH4 read:");
      Disp_PosXY(0, 26); 
      Disp_PutText("OCT read:");
      Disp_PosXY(0, 39); 
      Disp_PutText("Scan time:");
      doRefresh = 0;
    }
    
    Disp_PosXY(88, 0);
    Disp_ClearArea(40, 12);
    Disp_PutDigit(TouchPadStates >> 8);
    Disp_PutHexByte(TouchPadStates & 0xFF);
    
    Disp_PosXY(80, 13);  
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(touchReadings[0], 1);
    
    Disp_PosXY(80, 26);  
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(touchReadings[9], 1);

    Disp_PosXY(80, 39);  
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(TouchPadScanTime_ms, 2);
    Disp_PutText("ms");
  }
  else if (diagnosticStep == 1)
  {
    // Show sensor readings (in raw ADC units)
    if (doRefresh)
    {
      Disp_SetFont(PROP_12_NORM);
      Disp_PosXY(0, 0);
      Disp_PutText("Pressure:");
      Disp_PosXY(0, 13);
      Disp_PutText("Quiescent:");
      Disp_PosXY(0, 26);
      Disp_PutText("Maximum: ");
      Disp_PosXY(0, 39);
      Disp_PutText("Modn Pad:");
      doRefresh = 0;
    }
    
    Disp_PosXY(80, 0);
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(PressureSensorReading, 4);
    
    Disp_PosXY(80, 13);
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(PressureQuiescent, 4);
    
    Disp_PosXY(80, 26);
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(g_Config.PressureFullScale, 4);
    
    Disp_PosXY(80, 39);
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(ModulationSensorReading, 4);
  }
  else if (diagnosticStep == 2) 
  {
    // Test sound synthesizer operation (without Note ON/OFF task)
    if (doRefresh)
    {
      Disp_PosXY(0, 0);
      Disp_PutText("Sound test...");
      RemiSynthPatchSelect(90);  // Select Test Patch (Osc1: sine wave;  Osc2: sawtooth)
      RemiSynthVibratoModeSet(0);  // Override Preset
      RemiSynthNoteOn(69, 64);  // Note ON, 69 = A4 (440Hz)
      doRefresh = 0;
    }
  }
  else if (diagnosticStep == 3)  // Last step -- Repeat from step 1 (when SET hit)
  {
    if (doRefresh)
    {
      RemiSynthNoteOff();  // finish last Step (synth sound test)
      PresetSelect(g_Config.PresetLastSelected);
      RemiSynthVibratoModeSet(g_Config.VibratoMode);
      
      Disp_PosXY(0, 0);
      Disp_PutText("UI timer:");
      Disp_PosXY(0, 13); 
      doRefresh = 0;
    }

    Disp_PosXY(80, 0);
    Disp_ClearArea(48, 12);
    Disp_PutDecimal(UserInactiveTimer_sec, 4);
  }
    
  if (ButtonHitFlag)
  {
    ButtonHitFlag = 0;
    if (++diagnosticStep >= 4) diagnosticStep = 0; // next step
    Disp_ClearScreen();  
    Disp_SetFont(PROP_12_NORM);
    Disp_PosXY(120, 52);  // bottom line, RHS corner
    Disp_PutDecimal(diagnosticStep, 1);
    doRefresh = TRUE;
  }
}


/*````````````````````````````````````````````````````````````````````````````````````````````````
   Function:      Determine 14-bit pressure value from the pressure sensor ADC reading.
                  May be used also to find MIDI velocity value from pressure.

   Note:          The function assumes a linear relationship between raw pressure reading
                  and MIDI pressure (or velocity) value. The external MIDI sound module
                  should apply an exponential transfer function between MIDI pressure and
                  audio output signal amplitude.
*/
uint16  GetBreathPressureLevel()
{
  int  level;
  uint16  rawSpan;  

  // Calculate pressure as a 14-bit quantity, range 0 to 16256 (127 x 128)
  rawSpan = g_Config.PressureFullScale - PressureQuiescent;  // unit = ADC counts
  level = (16256 * (int32)(PressureSensorReading - PressureQuiescent)) / rawSpan;

  if (level < 0) level = 0;
  if (level > 16256)  level = 16256;

  return (uint16) level;
}

/*````````````````````````````````````````````````````````````````````````````````````````````````
   Function:  GetModulationPadForce()

   Return value:  Unsigned integer in the range 0 ~ 16256 (14 bits)
                  representing the force applied to the Modulation Pad.

   Note:  MODULATION_MAXIMUM is the maximum value of ModulationSensorReading (ADC count).

   A "dead-band" is deliberately introduced at zero so that a minimum force needs
   to be applied to the sensor before a non-zero reading is obtained.
   A square-law transform is applied to the reading to compensate for non-linearity
   in the FSR-402 characteristic.
*/
uint16   GetModulationPadForce()
{
  int32    linearVal;    // uncompensated reading
  uint16   compVal;      // compensated for non-linearity and dead-band
  uint16   rawSpan;

  linearVal = ModulationSensorReading - MODULATION_DEADBAND;
  if (linearVal < 0) linearVal = 0;

  // Scale linearVal such that it spans the full range (0 ~ 16256)...
  rawSpan = MODULATION_MAXIMUM - MODULATION_DEADBAND;
  linearVal = (16256 * linearVal) / rawSpan;

  compVal = (linearVal * linearVal) / 16256;   // Apply square-law transform
  if (compVal > 16256)  compVal = 16256;       // Cap at 16256

  return  compVal;
}


/*
   Function:  GetPitchBendData()

   Return value:  Signed integer in the range +/- 8000 representing the displacement
                  of the Pitch-Bend lever while a note is playing or diagnostic mode
                  is active; otherwise zero (0).

   Note:  If a Note-On event is pending, i.e. if NoteOnOffState != NOTE_OFF_IDLE,
          then TimeSinceLastNoteOff_ms = 0.  The function cannot return a Pitch Bend
          value when there is no note playing (except while diagnostic mode is active)
          because the auto-zero routine is active in the note-off/idle state.

   *** TODO ***  
*/
int16  GetPitchBendData()
{
  int16   compVal = 0;  // no pitch bend (temp.)
  /*
    int32   linearVal;

    if (TimeSinceLastNoteOff_ms == 0)
    {
      // *** this is legacy nonsense from REMI mk2 synth! ***

      linearVal = 16000 * (int32)(PitchBendSensorReading - PitchBendZeroLevel);
      compVal = linearVal;   // Linear response
    }
  */
  return  compVal;
}


/* Function:  PitchBendAutoZero() 
   Background task executed every 50 milliseconds.

   If at least 1 second has elapsed since the last Note-Off event and there has been no
   subsequent Note-On event, the function performs an "auto-zero" operation on the
   Pitch-Bend sensor reading.

   The last reading taken is used to set the Pitch-Bend zero level in preparation for the
   next note to be played. The task will be executed repetitively until the next Note-On.
*/
void  PitchBendAutoZero()
{
  if (TimeSinceLastNoteOff_ms > 1000)
  {
    // TODO:  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  }
}


//=================================================================================================
//             E E P R O M    D A T A    M A N A G E M E N T   F U N C T I O N S
//
/*`````````````````````````````````````````````````````````````````````````````````````````````````
   Function writes default values for player configuration data.
   These are "factory" defaults which are applied only in the event of erasure or
   corruption of EEPROM memory data, including firmware update.
*/
void  DefaultConfigData(void)
{
  //------------------------- PRESET:   8   1   2   3   4   5   6   7
  static uint8 defaultSynthPatch[]  = { 41, 10, 11, 21, 26, 48, 45, 46 };
  int  i;

  g_Config.checkDword = 0xFEEDFACE;
  g_Config.EndOfDataBlockCode = 0xE0DBC0DE;

  g_Config.MidiOutChannel = 1;
  g_Config.MidiLegatoModeEnabled = FALSE;
  g_Config.VelocitySenseEnabled = FALSE;
  g_Config.VibratoMode = 0;  // OFF
  g_Config.ReverbMix_pc = 10;
  g_Config.BatteryType = 0;  // Alkaline (3V)
  g_Config.PresetLastSelected = 1;
  g_Config.PressureFullScale = 4095;

  for (i = 0;  i < 8;  i++)
  {
    g_Config.PresetPatchNum[i] = defaultSynthPatch[i];
  }

  StoreConfigData();  // commit to EEPROM
}

/*
    Function checks the integrity of persistent data stored in EEPROM block 0.
    If the block is erased or the data is found to be corrupt, or if the structure size
    exceeds the block size (256 bytes), the function returns FALSE;  otherwise TRUE.
*/
BOOL  CheckConfigData(void)
{
  BOOL   result = TRUE;

  g_Config.checkDword = 0xFFFFFFFF;
  g_Config.EndOfDataBlockCode = 0xFFFFFFFF;

  FetchConfigData();

  if (g_Config.checkDword != 0xFEEDFACE) result = FALSE;
  if (g_Config.EndOfDataBlockCode != 0xE0DBC0DE) result = FALSE;

  return result;
}

/*
    Function copies data from EEPROM block #0 to a RAM buffer where persistent data
    can be accessed by the application.
*/
void  FetchConfigData()
{
  EepromReadData((uint8 *) &g_Config, 0, sizeof(g_Config));
}

/*
    Function copies data from a RAM buffer (holding current working
    values of persistent parameters) to the EEPROM block #0.
    <!> The size of the structure g_Config must not exceed 256 bytes.
*/
void  StoreConfigData()
{
  EepromWriteData((uint8 *) &g_Config, 0, sizeof(g_Config));
}


/*````````````````````````````````````````````````````````````````````````````````````````````````
  Function copies a specified number of bytes (byteCount) from an array (dataSource)
  in data memory to a block in EEPROM (blockNum), beginning at an address offset
  from the start of the EEPROM (addrOffset).
*/
void  EepromWriteData(uint8 *dataSource, short addrOffset, short byteCount)
{
  while (byteCount != 0)
  {
    EEPROM.write(addrOffset++, *dataSource++);
    byteCount--;
  }
}

/*
  Function copies a specified number of bytes (byteCount) from a block in EEPROM
  (blockNum) to an array (dataSource) in data memory, beginning at an address offset
  from the start of the EEPROM (addrOffset).
*/
void  EepromReadData(uint8 *dataDestin, short addrOffset, short byteCount)
{
  while (byteCount != 0)
  {
    *dataDestin++ = EEPROM.read(addrOffset++);
    byteCount--;
  }
}


//=================================================================================================
//
// Teensy 3.2 (MK20DX256) Touch Sense Support Functions -- Non-blocking!
//
// These settings give approx 0.02 pF sensitivity and 1200 pF range.
// Lower current, higher number of scans, and higher prescaler increase sensitivity,
// but the trade-off is longer measurement time and decreased range.
// Time to measure 33 pF is approx 0.25 ms
// Time to measure 1000 pF is approx 4.5 ms

#define CURRENT   2  // 0 to 15 - current to use, value is 2*(current+1)
#define NSCAN     9  // number of times to scan, 0 to 31, value is nscan+1
#define PRESCALE  2  // prescaler, 0 to 7 - value is 2^(prescaler+1)

static const uint8_t pin2tsi[] = {
  // 0    1    2    3    4    5    6    7    8    9
  9,   10,  255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255,  13,   0,   6,   8,   7,
  255, 255,  14,  15, 255,  12, 255, 255, 255, 255,
  255, 255,  11,   5
};

uint32_t  tsi_ch;  // TSI channel

// Function initiates touch sense routine on the specified Teensy 3.2 pin,
// but it DOES NOT WAIT for the result. Check using touchSenseDone().
//
int  touchSenseInit(uint8_t pin)
{
  tsi_ch = pin2tsi[pin];
  if (tsi_ch > 15) return FAIL;

  *portConfigRegister(pin) = PORT_PCR_MUX(0);

  SIM_SCGC5 |= SIM_SCGC5_TSI;
  TSI0_GENCS = 0;
  TSI0_PEN = (1 << tsi_ch);
  TSI0_SCANC = TSI_SCANC_REFCHRG(3) | TSI_SCANC_EXTCHRG(CURRENT);
  TSI0_GENCS = TSI_GENCS_NSCN(NSCAN) | TSI_GENCS_PS(PRESCALE) | TSI_GENCS_TSIEN | TSI_GENCS_SWTS;
  // delayMicroseconds(10);  // Task scheduler should handle this timing requirement
  return SUCCESS;
}


// Function checks touch sense status. If the routine has completed and a result is ready,
// the return value will be True (1), otherwise False (0). The function does not wait.
// Alternatively, use macro: TOUCH_SENSE_DONE
//
bool  touchSenseDone()
{
  if (TSI0_GENCS & TSI_GENCS_SCNIP) return 0;  // busy
  else  return 1;  // done
}


// Function returns the last reading available from the touch sense routine.
// Call touchSenseDone() first to check that a valid reading is ready.
//
int  touchSenseRead()
{
  return *((volatile uint16_t *)(&TSI0_CNTR1) + tsi_ch);
}


// REMI logo bitmap image definition:  width: 85, height: 30 pixels
//
bitmap_t  remi_logo_85x30[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
  0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x1F, 0xFF, 0xFF, 0xFF,
  0x1F, 0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xC0, 0x1F, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC,
  0x1F, 0xC0, 0x3F, 0xFF, 0xFF, 0xFC, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xE0, 0x3F, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xE0, 0x3F, 0xFC, 0x07, 0xC0, 0x00, 0xFF, 0x07, 0xC1, 0xF8, 0x3F, 0xE0, 0x3F, 0xF0,
  0x07, 0x80, 0x00, 0x7C, 0x00, 0x00, 0x78, 0x3F, 0xE0, 0x3F, 0xE0, 0x0F, 0x00, 0x00, 0x38, 0x00,
  0x00, 0x3E, 0x3F, 0xE0, 0x3F, 0xE1, 0xFE, 0x1F, 0xFE, 0x38, 0x78, 0x3C, 0x3E, 0x3F, 0xE0, 0x3F,
  0xC3, 0xFE, 0x3F, 0xFE, 0x38, 0xFC, 0x7E, 0x3E, 0x3F, 0xE0, 0x3F, 0xC7, 0xFE, 0x3F, 0xFC, 0x38,
  0xFC, 0x7E, 0x3E, 0x3F, 0xE0, 0x3F, 0xC7, 0xFE, 0x00, 0x00, 0x38, 0xFC, 0x7E, 0x3E, 0x3F, 0xE0,
  0x3F, 0xC7, 0xFE, 0x00, 0x00, 0x78, 0xFC, 0x7E, 0x3E, 0x3F, 0xE0, 0x3F, 0xC7, 0xFE, 0x00, 0x00,
  0xF8, 0xFC, 0x7E, 0x3E, 0x3F, 0xE0, 0x3F, 0xC7, 0xFE, 0x3F, 0xFF, 0xF8, 0xFC, 0x7E, 0x3E, 0x3F,
  0xE0, 0x3F, 0xC7, 0xFE, 0x1F, 0xFF, 0xF8, 0xFC, 0x7E, 0x3E, 0x3F, 0xE0, 0x3F, 0xC7, 0xFF, 0x00,
  0x07, 0xF8, 0xFC, 0x7E, 0x3E, 0x3F, 0xE0, 0x3F, 0xC7, 0xFF, 0x80, 0x07, 0xF8, 0xFC, 0x7E, 0x3E,
  0x3F, 0xE0, 0x3F, 0xC7, 0xFF, 0xC0, 0x07, 0xF8, 0xFC, 0x7E, 0x3E, 0x3F, 0xE0, 0x3F, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xC0, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x0F, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// end of file
