/********************************************************
  Update Pellet count and Battery Voltage on screen
********************************************************/
void UpdateDisplay() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(18, 25);
  display.setTextSize(1);
  display.print("FED:");
  display.println(FED);
  display.setCursor(19, 25);
  display.print("FED:");
  display.println(FED);

  display.drawRoundRect (100, 10, 42, 20, 3, BLACK);
  display.drawRoundRect (141, 15, 6, 10, 2, BLACK);

  display.setCursor(15, 85);
  display.setTextSize(3);
  display.print(PelletCount);

  // Display battery voltage
  display.setTextSize(1);
  display.setCursor(10, 110);

  if (measuredvbat > 3.85) {
    display.fillRoundRect (104, 13, 7, 14, 1, BLACK);
    display.fillRoundRect (113, 13, 7, 14, 1, BLACK);
    display.fillRoundRect (122, 13, 7, 14, 1, BLACK);
    display.fillRoundRect (131, 13, 7, 14, 1, BLACK);
  }
  else if (measuredvbat > 3.7) {
    display.fillRoundRect (104, 13, 7, 14, 1, BLACK);
    display.fillRoundRect (113, 13, 7, 14, 1, BLACK);
    display.fillRoundRect (122, 13, 7, 14, 1, BLACK);
  }
  else if (measuredvbat > 3.55) {
    display.fillRoundRect (104, 13, 7, 14, 1, BLACK);
    display.fillRoundRect (113, 13, 7, 14, 1, BLACK);
  }
  else {
    display.fillRoundRect (104, 13, 7, 14, 1, BLACK);
  }

  //draw lines to divide data on screen
  display.drawFastHLine(15, 108, 135, BLACK);
  display.drawFastHLine(15, 109, 135, BLACK);

  // Display date and time at bottom of screen
  display.setCursor(15, 130);
  display.print(rtc.getMonth());
  display.print("/");
  display.print(rtc.getDay());
  display.print("/");
  display.print(rtc.getYear() + 2000);
  display.print("    ");
  display.print(rtc.getHours());
  display.print(":");
  if (rtc.getMinutes() < 10)
    display.print('0');      // Trick to add leading zero for formatting
  display.print(rtc.getMinutes());

  display.refresh();
}

/********************************************************
  Display SD Card error
********************************************************/
void DisplaySDError() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(20, 40);
  display.setTextSize(2);
  display.println(" Check");
  display.setCursor(10, 80);
  display.println("SD Card!");

  display.refresh();
}

/********************************************************
  Display logging data
********************************************************/
void DisplaySDLogging() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setTextSize(2);
  display.setCursor(20, 40);
  display.println("Writing");
  display.setCursor(20, 80);
  display.println("data...");

  display.refresh();
}

/********************************************************
  Display jam clear
********************************************************/
void DisplayJamClear() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(15, 40);
  display.setTextSize(2);
  display.println("Clearing");
  display.setCursor(15, 80);
  display.println("jam...");
  display.refresh();
}

/********************************************************
  Display Dispensing Pellet
********************************************************/
void DisplayDispense() {
  display.clearDisplay();
  display.setRotation(3);
  display.setTextColor(BLACK);

  display.setCursor(15, 40);
  display.setTextSize(2);
  display.println("Feeding..");
  display.setCursor(15, 80);
  display.println(numMotorTurns);
  display.refresh();
}

/********************************************************
  Startup Animation
********************************************************/
void StartUpDisplay () {
  display.setFont(&FreeSans9pt7b);
  display.setRotation(3);
  for (int pos = 120; pos > 30; pos -= 10) {
    display.setCursor(0, pos);
    display.setTextSize(2);
    display.setTextColor(BLACK);
    display.clearDisplay();
    display.println("  FED is");
    display.println("  starting");
    display.println("  up...");
    display.refresh();
    delay (10);
  }
}

/********************************************************
  Success
********************************************************/
//void DisplaySd () {
//  display.setFont(&FreeSans9pt7b);
//  display.setRotation(3);
//  for (int pos = 120; pos > 30; pos -= 10) {
//    display.setCursor(0, pos);
//    display.setTextSize(2);
//    display.setTextColor(BLACK);
//    display.clearDisplay();
//    display.println(csvFileName);
//    display.refresh();
//    delay (10);
//  }
//}

/********************************************************
  check filename
********************************************************/
//void filenameCheck () {
//  display.setFont(&FreeSans9pt7b);
//  display.setRotation(3);
//  for (int pos = 120; pos > 30; pos -= 10) {
//    display.setCursor(0, pos);
//    display.setTextSize(2);
//    display.setTextColor(BLACK);
//    display.clearDisplay();
//    display.println(filename);
//    display.refresh();
//    delay (10);
//  }
//}

/********************************************************
  weird stuff
********************************************************/
void weird () {
  display.setFont(&FreeSans9pt7b);
  display.setRotation(3);
  for (int pos = 120; pos > 30; pos -= 10) {
    display.setCursor(0, pos);
    display.setTextSize(2);
    display.setTextColor(BLACK);
    display.clearDisplay();
    display.println("");
    display.refresh();
  }
}
