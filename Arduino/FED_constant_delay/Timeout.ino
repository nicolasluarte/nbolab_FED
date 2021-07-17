void Timeout () {
  // create array with possible delays, if you want a probability distributions copy the number
  int DELAYS[] = {15, 15};
  
  if (TimeoutReady == true) {
    int index = random(sizeof(DELAYS) / sizeof(DELAYS[0]));
    delayPick = DELAYS[index];
    for (int k = 0; k < delayPick; k++) {
      delay (1000);
      display.clearDisplay();
      display.setCursor(10, 40);
      display.setTextSize(2);
      display.println("Timeout:");
      display.setCursor(10, 82);
      display.print(delayPick - k);
      display.print(" sec");
      display.refresh();
    }
    TimeoutReady=false;
  }
}
