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
  // below are the times when a long delay is delivered
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

void displayRandomFeed(int result) {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(40, 50);
  display.setTextSize(4);
  char msg[30];
  sprintf(msg,"Random feed: %02d", result);
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
