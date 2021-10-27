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
}
