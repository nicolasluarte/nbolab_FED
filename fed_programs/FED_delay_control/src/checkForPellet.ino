void checkForPellet() {
  getFeedingDelay();
  queryPI();
  if (pellet) {
    delay(500);
    delayLogic = true;
  }
  else {
    if (delayLogic == true) {
      for (int i = 0; i < fedDelay; i++) {
	displayDelay(fedDelay - i);
	delayLogic = false;
	delay(1000);
      }
    }
  }
}
