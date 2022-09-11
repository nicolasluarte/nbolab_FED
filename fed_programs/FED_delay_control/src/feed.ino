//void feed() {
//  if (!pellet) {
//    displayFeed();
//    for (int i = 0; i < 20 + random(0, 10); i++) {
//      if (!pellet) {
//        //myMotor->step(25, FORWARD, DOUBLE);
//        //myMotor->step(50, BACKWARD, DOUBLE);
//	myMotor->step(7, BACKWARD, DOUBLE);
//        myMotor->step(14, FORWARD, DOUBLE);
//        delay(50);
//        queryPI();
//	delay(200);
//      }
//    }
//    myMotor->release();
//  }
//  motorTurns++;
//  if (motorTurns > turnsBeforeClear){
//    pelletJam = true;
//  }
//  else{
//    pelletJam = false;
//  }
//
//delay(500);
//
//// avoid pellet jam
//  if (!pellet){
//	myMotor->step(50, BACKWARD, DOUBLE);
//  }
//
//}
//

void spin(){
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


void feed() {
  if (!pellet) {
    displayFeed();
    for (int i = 0; i < 20 + random(0, 10); i++) {
      if (!pellet) {
        myMotor->step(50, FORWARD, DOUBLE);
        myMotor->step(25, BACKWARD, DOUBLE);
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
  if (motorTurns > 5){
    doSpin = true;
  }
  else{
    pelletJam = false;
    doSpin = false;
  }
}

void clearJam(){
  if (!pellet){
    for (int i = 0; i < 20 + random(0, 10); i++) {
      if (!pellet) {
        myMotor->step(50, BACKWARD, DOUBLE);
        myMotor->step(25, FORWARD, DOUBLE);
        delay(50);
        queryPI();
      }
    }
  }
  myMotor->release();
  numClears++;
  delay(500);
}
