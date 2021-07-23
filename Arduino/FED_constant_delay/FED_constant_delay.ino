 // Change FED value to change the mouse number at the beginning of the filename.  This must remain an integer, no strings!
int FED = 1;


/********************************************************
  FED 2.00
  Written by Lex Kravitz and Mohamed Ali at the
  National Institute of Diabetes and Digestive and Kidney Diseases
  February, 2018

  FED is a Feeding Experimentation Device.  It is a pellet dispenser
  that logs the timestamp whenever a pellet is removed. These timestamps
  can be used to recreate feeding records over multiple days.

  FED2 is a redesign of the device developed by Nguyen at al and published in 2016:
  https://www.ncbi.nlm.nih.gov/pubmed/27060385

  This code includes code from:
  *** Adafruit, who made the Feather boards and associated code ***

  Cavemoa's excellent examples of datalogging with the Adalogger:
  https://github.com/cavemoa/Feather-M0-Adalogger

  Uses Arduino Time library http://playground.arduino.cc/code/time
  Maintained by Paul Stoffregen https://github.com/PaulStoffregen/Time

  Uses Arduino Zero RTC library https://www.arduino.cc/en/Reference/RTC
  Maintained by Arturo Guadalupi https://github.com/arduino-libraries/RTCZero

  FED is released under The MIT license:

  Copyright (c) 2008 Matias Korhonen

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
********************************************************/


/********************************************************
  Setup code
********************************************************/
#include "a_header.h" //See "a_header.h" for #defines and other constants 
String FILENAME;
bool headerFlag = true;

void setup() {
  StartUpCommands();
  if (SD.begin(4)) {
    DisplaySDSuccess();
    delay(1000);
  } else {
    DisplaySDError();
    delay(1000);
  }


 //sprintf(filename, "%02d%02d%02d%02d%02d%02dFED%02d.csv", rtc.getYear(), rtc.getMonth(), rtc.getDay(), rtc.getHours(), rtc.getMinutes(), rtc.getSeconds(), FED);
  String MONTH = String(rtc.getMonth());
  String DAY = String(rtc.getDay());
  String HOUR = String(rtc.getHours());
  String MICE = String(FED);
  String MIN = String(rtc.getMinutes());
  String DATE = MONTH + DAY + HOUR + MIN;
  String EXT = ".csv";
  FILENAME = DATE + MICE + EXT;
  logfile = SD.open(FILENAME, FILE_WRITE);
  myMotor->setSpeed(99999);
}


/********************************************************
  FED loop
********************************************************/
void loop() {
  // if (logfile.open(filename, O_CREAT | O_WRITE | O_APPEND)) {
  if (logfile) {
    if (headerFlag == true  ){
            logfile.println("MM:DD:YYYY hh:mm:ss, Mouse, PelletCount, MotorTurns, BatteryVoltage, Delay");
            headerFlag = false;
    }
    
    CheckForPellet ();


    if (PelletAvailable == true) {
      sleep();
    }
    else {
      Timeout();
      Feed();
    }
    if (PelletJam) {
      ClearJam();
    }
  }
}
