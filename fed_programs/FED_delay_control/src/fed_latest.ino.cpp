# 1 "/tmp/tmpr5r2yf_5"
#include <Arduino.h>
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/fed_latest.ino"

#include "headers.h"

int FED;


struct Config {
  char protocol[64];
  int animal;
  int longDelay;
  int longDelayCounter;
  int deliveryDelay[10];
};


const char *configurationFile = "/config.txt";

Config config;
void setup();
void loop();
void checkForPellet();
void createHeaders();
void displayExperimentInfo();
void displaySDSuccess();
void displaySDError();
void displayFeed();
void displayDelay(int count);
void displayJam();
void feed();
void clearJam();
void getFeedingDelay();
void loadConfiguration(const char *filename, Config &config);
void printFile(const char *filename);
void queryPI();
void readBatteryLevel();
void sdSetup();
void shuffleArray(int * array, int size);
void startupCommands();
void wake();
void writeData();
#line 20 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/fed_latest.ino"
void setup() {
  startupCommands();
  rtc.begin();

  Wire.begin();

  display.begin();
  display.clearDisplay();
  minorHalfSize = min(display.width(), display.height()) / 2;



  Serial.begin(9600);






  sdSetup();


  Serial.println("Loading FED configuration file...");
  loadConfiguration(configurationFile, config);
  printFile(configurationFile);
  Serial.println(blockSize);



  sprintf(FEDLog, "%02d.csv", config.animal);
  logfile = SD.open(FEDLog, FILE_WRITE);


}

void loop() {
  createHeaders();
  readBatteryLevel();
  if (!blockDisplay) {
    displayExperimentInfo();
  }
  if (!blockDelivery) {
    checkForPellet();
    feed();
    if (pelletJam){
      clearJam();
    }
  }
  delay(1000);


}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/checkForPellet.ino"
void checkForPellet() {
  queryPI();
  if (pellet) {
    delay(500);
    delayLogic = true;
  }
  else {
    if (delayLogic == true) {
      getFeedingDelay();
      for (int i = 0; i < fedDelay; i++) {
        displayDelay(fedDelay - i);
        delayLogic = false;
        delay(1000);
      }
    }
  }
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/createHeaders.ino"
void createHeaders(){

  if (logfile.size() == 0){
    logfile.println("time,animal,pellets,motorTurns,battery,delay,protocol");
  }
  logfile.flush();
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/displayFunctions.ino"
void displayExperimentInfo() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(0, 10);
  display.setTextSize(2);
  char experimentalInfo[80];
  unsigned long epoch = rtc.getEpoch();
  sprintf(experimentalInfo,
  "Animal: %02d\n\Cond: %s\nTime: %02d:%02d:%02d\nPellets: %02d\nBattery: %d\nDelays: %d,%d,%d,%d,%d,%d",
  config.animal,
  config.protocol,
  hour(epoch),
  minute(epoch),
  second(epoch),
  pelletCount,
  batt,

  sampleHours[0],
  sampleHours[1],
  sampleHours[2],
  sampleHours[3],
  sampleHours[4],
  sampleHours[5]
  );
  display.println(experimentalInfo);

  display.refresh();
  blockDisplay = true;
}

void displaySDSuccess() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(0, 10);
  display.setTextSize(3);
  display.println("SD successful");

  display.refresh();
}

void displaySDError() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(0, 10);
  display.setTextSize(3);
  display.println("SD error");

  display.refresh();
}

void displayFeed() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(0, 10);
  display.setTextSize(3);
  display.println("Feeding...");

  display.refresh();
}

void displayDelay(int count) {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(40, 50);
  display.setTextSize(4);
  char msg[30];
  sprintf(msg,"Delay: %02d", count);
  display.println(msg);

  display.refresh();
}

void displayJam() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(40, 50);
  display.setTextSize(4);
  display.println("Clearing Jam");

  display.refresh();
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/feed.ino"
void feed() {
  if (!pellet) {
    displayFeed();
    for (int i = 0; i < 20 + random(0, 10); i++) {
      if (!pellet) {
        myMotor->step(25, FORWARD, DOUBLE);
        myMotor->step(50, BACKWARD, DOUBLE);
        delay(50);
        queryPI();
      }
    }
    myMotor->release();
  }
  motorTurns++;
  if (motorTurns > turnsBeforeClear){
    pelletJam = true;
  }
  else{
    pelletJam = false;
  }
}

void clearJam(){
  if (!pellet){
    for (int i = 0; i < 41 + random(0, 50); i++){
      myMotor->step(i, FORWARD, DOUBLE);
      queryPI();
      if (pellet){
        break;
      }
    }
  }
  myMotor->release();
  numClears++;
  delay(500);
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/getFeedingDelay.ino"
void getFeedingDelay(){
  if (shuffle){
    shuffleArray(dayHours, 24);
    shuffle = false;
    lastShuffle = rtc.getEpoch();

    for (int i = 0; i < 6; i++){
      sampleHours[i] = dayHours[i];
    }
  }



  for (int i = 0; i < config.longDelayCounter; i++){
    if(sampleHours[i] == hour(rtc.getEpoch())){
      sampleHours[i] = 99;
      match = true;
      fedDelay = config.longDelay;
      break;
    }
    else{
      match = false;

      if (day(rtc.getEpoch()) != day(lastShuffle)){
        shuffle = true;
      }
    }
  }

  if (!match){
    Serial.println("Random delay choosen");
    int r = (int)random(0, delaySize);
    fedDelay = config.deliveryDelay[r];
  }

}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/loadConfiguration.ino"
void loadConfiguration(const char *filename, Config &config) {

  File file = SD.open(filename);




  StaticJsonDocument<1028> doc;


  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));


  config.animal = doc["animal"] | 111;
  strlcpy(config.protocol,
          doc["protocol"] | "default",
          sizeof(config.protocol));
  config.longDelay = doc["longDelay"] | 15;
  config.longDelayCounter = doc["longDelayCounter"] | 6;
  JsonArray deliveryArray = doc["deliveryDelay"].as<JsonArray>();

  int counter = 0;
  for (const auto& v : deliveryArray) {
    config.deliveryDelay[counter] = v.as<int>();
    counter++;
  }
  delaySize = counter;


doc["lastLongDelay"] = "prueba";


  file.close();
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/printFile.ino"

void printFile(const char *filename) {

  File file = SD.open(filename);
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }


  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();


  file.close();
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/queryPI.ino"
void queryPI(){
  if (digitalRead(PELLET_WELL) == LOW) {
    pellet = true;

    if (!dataLog){
      pelletCount++;
      blockDisplay = false;
      writeData();


      motorTurns = 0;
      pelletJam = false;
      numClears = 0;
    }
  }
  else{
    pellet = false;


    dataLog = false;
  }
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/readBatteryLevel.ino"
void readBatteryLevel(){
    measuredvbat = analogRead(VBATPIN);
    measuredvbat *= 2;
    measuredvbat *= 3.3;
    measuredvbat /= 1024;
    if (measuredvbat > 3.85){
        batt = 4;
    }
    else if (measuredvbat > 3.7){
        batt = 3;
    }
    else if (measuredvbat > 3.55){
        batt = 2;
    }
    else{
        batt = 1;
    }
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/sdSetup.ino"
void sdSetup(){
  if (SD.begin(4)){
    displaySDSuccess();
    delay(1000);
  }
  else{
    displaySDError();
    delay(1000);
  }
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/shuffleArray.ino"
void shuffleArray(int * array, int size)
{
  int last = 0;
  int temp = array[last];
  for (int i=0; i<size; i++)
  {
    int index = random(size);
    array[last] = array[index];
    last = index;
  }
  array[last] = temp;
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/startupCommands.ino"
void startupCommands(){

  pinMode(PELLET_WELL, INPUT_PULLDOWN);
  pinMode (RED_LED, OUTPUT);
  pinMode (GREEN_LED, OUTPUT);
  attachInterrupt(PELLET_WELL, wake, RISING);

  AFMS.begin(1000);
  myMotor->setSpeed(100);
}

void wake() {
  digitalWrite (RED_LED, HIGH);
}
# 1 "/home/nicoluarte/nbolab_FED/fed_programs/FED_delay_control/src/writeData.ino"
void writeData(){
  sprintf(data, "%02d,%02d,%02d,%02d,%02d,%02d,%s", rtc.getEpoch(), config.animal, pelletCount, motorTurns, batt, fedDelay, config.protocol);
  Serial.println(data);
  logfile.println(data);
  logfile.flush();
  dataLog = true;
}