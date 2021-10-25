void Timeout () {
  // create array with possible delays, if you want a probability distributions copy the number
  // int DELAYS[] = {15};
  int random_delay[] = {15, 60, 120, 180, 240, 300};
  int random_number = random(0, 5);
  delayPick = random_delay[random_number];
  
  if (TimeoutReady == true) {
    //int index = random(sizeof(DELAYS) / sizeof(DELAYS[0]));
    //delayPick = DELAYS[index];
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
