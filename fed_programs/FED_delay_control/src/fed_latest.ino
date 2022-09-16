// all relevant setting are here
#include "headers.h"

int FED;

// read json config file
struct Config {
  char protocol[64];
  int animal;
  int longDelay;
  int longDelayCounter;
  int deliveryDelay[10];
  // this variable is written in microSD
  // if == 1, cointoss every hour in lights-off period
  // to deliver pellet or not
  int randomFeed;
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
  // if this is uncommentedcode will start only if serial monitor is opened
 // while (!Serial) {
 //   ;
 // }

  // Start the SD card and check if succesful
  sdSetup();

  // initialize random feeding hours
  randFeedHours();

  // Read configuration file
  Serial.println("Loading FED configuration file...");
  loadConfiguration(configurationFile, config);
  printFile(configurationFile);
  Serial.println(blockSize);


  // Create the logfile
  sprintf(FEDLog, "%02d.csv", config.animal);
  logfile = SD.open(FEDLog, FILE_WRITE);

  // read long delay info, stores variable values after reboot
}

void loop() {
  createHeaders();
  readBatteryLevel();
  if (!blockDisplay) {
    displayExperimentInfo();
  }
  if (!blockDelivery) {
    checkForPellet();
    if (deliver){
	    feed();
    }
    if (pelletJam){
      clearJam();
    }
    if (doSpin){
	    spin();
    }
  }
  delay(1000);

  // when delivery is blocked display should update once
}
