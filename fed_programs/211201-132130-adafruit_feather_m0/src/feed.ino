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
        break; // if pellet was delivered after clearJam exit loop
      }
    }
  }
  myMotor->release();
  numClears++;
  delay(500);
}
