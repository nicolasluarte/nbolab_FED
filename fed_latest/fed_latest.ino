// all relevant setting are here
#include "headers.h"

int FED;

// read json config file
struct Config {
  char protocol[64];
  int animal;
};

// direction of the configuration file
const char *configurationFile = "/config.txt";
// struct to save all the configuration
Config config;     

void setup() {
  startupCommands();
  rtc.begin();
  Wire.begin();
  // start display
  display.begin();
  display.clearDisplay();
  minorHalfSize = min(display.width(), display.height()) / 2;
  

  // this is to wait for the serial port to connect
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  
  // Start the SD card and check if succesful
  sdSetup();

  // Read configuration file
  Serial.println("Loading FED configuration file...");
  loadConfiguration(configurationFile, config);
  printFile(configurationFile);
 

  // Create the logfile
  sprintf(FEDLog, "%02d.csv", config.animal);
  logfile = SD.open(FEDLog, FILE_WRITE);
}

void loop() {
  createHeaders();
  if (!blockDisplay){
    displayExperimentInfo();
  }
  checkForPellet();
  feed();
  //randomPause();
  delay(1000);
}
