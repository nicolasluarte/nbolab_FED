/********************************************************
  Include these libraries
********************************************************/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <RTCZero.h>
#include <SPI.h>
#include <SdFat.h>
SdFat SD;             //Quick way to make SdFat work with standard SD.h sketches
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <Fonts/FreeSans9pt7b.h>
#include <TimeLib.h> //include the Arduino Time library
#include <stdio.h>  // include the C++ standard IO library

/********************************************************
  Create RTCZero object
********************************************************/


/********************************************************
  Feather pins being used
********************************************************/
#define RED_LED 13
#define GREEN_LED 8
#define PELLET_WELL A1
#define VBATPIN A7
#define cardSelect 4
#define BNC_OUT 6

/********************************************************
  Initialize variables for FED code to use
********************************************************/
int numMotorTurns = 0;
int numJamClears = 0;
int TurnsBeforeJammed = 10;
int PelletCount = 0;
bool OutofFood = false;
bool PelletAvailable = false;
bool PelletJam = false;
bool CountReady = false;
bool TimeoutReady = false;
bool logReady = false;
float measuredvbat = 1.00;
float batteryalarm = 3.55;
bool OutReady = true;
int timeout = 15; //timeout between pellets in seconds
int delayPick;

/********************************************************
  Setup Sharp Memory Display
********************************************************/
#define SHARP_SCK  10
#define SHARP_MOSI 11
#define SHARP_SS   12
#define BLACK 0
#define WHITE 1
Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 144, 168);
int minorHalfSize;

/********************************************************
  Setup SD Card
********************************************************/
#define SampleIntMin 00 // RTC - Sample interval in minutes
#define SampleIntSec 10 // RTC - Sample interval in seconds
#define SamplesPerCycle 1  // Number of samples to buffer before uSD card flush is called. 
#define SamplesPerFile 1440 // 1 per minute = 1440 per day = 10080 per week and ¬380Kb file (assumes 38bytes per sample)
RTCZero rtc;
File logfile;         // Create file object
//char filename[15];    // Array for file name data logged to named in setup
unsigned int CurrentCycleCount;  // Num of smaples in current cycle, before uSD flush call
unsigned int CurrentFileCount;   // Num of samples in current file

/********************************************************
  Setup stepper objects
********************************************************/
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(513 , 2);

/********************************************************
  Setup date and time variables
********************************************************/
// initialize variables (these will be overwritten so doesn't really matter what they are)
byte months = 1;
byte days = 1;
byte years = 1;
byte hours = 1;
byte minutes = 1;
byte seconds = 1;

char s_month[5];
int tmonth, tday, tyear, thour, tminute, tsecond;
static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
