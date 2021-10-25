/********************************************************
  Check if food is available.  If so return TRUE.  1 second de-bounce on this function.
********************************************************/
void CheckForPellet () {
  ReadBatteryLevel();
  PelletAvailable = false;
  if (digitalRead(PELLET_WELL) == LOW ) {
    delay (500);
    if (digitalRead(PELLET_WELL) == LOW ) {
      PelletAvailable = true;
      PelletJam = false;
      if (CountReady == true) {
        PelletCount++;
        CountReady = false;
        logReady = true;
        OutReady = true;
        TimeoutReady=true;
      }
      if (logReady == true) {
        logdata();
        logReady = false;
      }
      UpdateDisplay();
    }
  }
}
