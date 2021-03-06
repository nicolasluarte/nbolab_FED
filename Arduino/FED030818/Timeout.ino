void Timeout () {
  if (TimeoutReady == true) {
    for (int k = 0; k < timeout; k++) {
      delay (1000);
      display.clearDisplay();
      display.setCursor(10, 40);
      display.setTextSize(2);
      display.println("Timeout:");
      display.setCursor(10, 82);
      display.print(timeout - k);
      display.print(" sec");
      display.refresh();
    }
    TimeoutReady=false;
  }
}
