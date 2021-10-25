void checkForPellet() {
  queryPI();
  Serial.println(pellet ? "PELLET" : "NO PELLET");
  if (pellet) {
    delay(500);
    delayLogic = true;
  }
  else {
    if (delayLogic == true) {
      getFeedingDelay();
      for (int i = 0; i < feedingDelay; i++) {
        displayDelay(feedingDelay - i);
        delayLogic = false;
        delay(1000);
      }
    }
  }
}
