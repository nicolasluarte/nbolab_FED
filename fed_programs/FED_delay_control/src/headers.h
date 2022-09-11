// SD related libs
#include <SD.h>
#include <ArduinoJson.h>

// basic libs
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SharpMem.h>
#include <Fonts/FreeSans9pt7b.h>
#include <stdio.h>

// time related libs
#include <RTCZero.h>
#include <TimeLib.h>

// time related variables
int tmonth, tday, tyear, thour, tminute, tsecond;
char s_month[5];
static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
byte months = 1;
byte days = 1;
byte years = 1;
byte hours = 1;
byte minutes = 1;
byte seconds = 1;

// motor libs
#include <Adafruit_MotorShield.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(513 , 2);

// feather m0 pins
#define RED_LED 13
#define GREEN_LED 8
#define PELLET_WELL A1
#define VBATPIN A7
#define cardSelect 4
#define BNC_OUT 6

// Sharp memory display
#define SHARP_SCK  10
#define SHARP_MOSI 11
#define SHARP_SS   12
#define BLACK 0
#define WHITE 1
Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 144, 168);
int minorHalfSize;

// create objects
RTCZero rtc;
File logfile;
char timeStampString[30];
char FEDLog[30];
bool pauseDelivery = false;
// remove hours when FED is being maintained
int HH[] = {1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0};
int randomHoursSize = 6;
int hourArray[6];

// PI variables
bool pellet;

// pins
#define RED_LED 13
#define GREEN_LED 8
#define PELLET_WELL A1
#define VBATPIN A7
#define cardSelect 4
#define BNC_OUT 6

// write data
bool dataLog = false;
char data[60];
int pelletCount;
int motorTurns = 1;
int battery = 1;
int fedDelay = 1;

// feeding variables
int idx = 0; // this is only a init value it gets randomized
int feedingDelay;
bool delayLogic;
bool blockDisplay = false;
int blockSize;
int blockMatch[24];
bool blockDelivery;
int delaySize;
int arraySum = 0;
bool pelletJam = false;
int turnsBeforeClear = 1;
int numClears = 0;

// timing variables
int dayHours[] = {0, 1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int sampleHours[6];
bool shuffle = true; // should the array be shuffled?
bool match;
int lastShuffle;

// battery variables
#define VBATPIN A7
float measuredvbat = 1.00;
int batt;
