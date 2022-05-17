void feed() {
  queryPI();
  if (!pellet) {
    displayFeed();
    for (int i = 0; i < 20 + random(0, 10); i++) {
      queryPI();
      if (!pellet) {
        //myMotor->step(15, FORWARD, DOUBLE);
        //myMotor->step(45, BACKWARD, DOUBLE);
        myMotor->step(7, BACKWARD, DOUBLE);
        myMotor->step(14, FORWARD, DOUBLE);
        delay(50);
      }
    }
    myMotor->release();
  }
  motorTurns++;
 if (!pellet){
   for (int i = 0; i < 10 + random(0, 10); i++) {
      queryPI();
      if (!pellet) {
        //myMotor->step(15, FORWARD, DOUBLE);
        //myMotor->step(45, BACKWARD, DOUBLE);
        myMotor->step(1, FORWARD, DOUBLE);
      }
    }
    myMotor->release();
  }

  if (motorTurns > turnsBeforeClear){
    pelletJam = true;
  }
  else{
    pelletJam = false;
  }
}

void clearJam(){
  queryPI();
  if (!pellet){
    for (int i = 0; i < 40 + random(0, 10); i++){
      myMotor->step(i, FORWARD, DOUBLE);
      queryPI();
      if (pellet){
        break; // if pellet was delivered after clearJam exit loop
      }
    }
  }
  delay(150);
  queryPI();
  if (!pellet){
    for (int i = 0; i < 40 + random(0, 10); i++){
      myMotor->step(i, BACKWARD, DOUBLE);
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
