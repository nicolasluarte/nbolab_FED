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
	delay(500);
	displayInt(blockCode);
	delay(500);
      }
    }
  }
}
