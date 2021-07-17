/********************************************************
  Feed function.  This turns the stepper forward and backwards to dispense a pellet, checking in between dispenses.
********************************************************/
void Feed()  {
  DisplayDispense();
  //Move pellet disk forward
  if (digitalRead (PELLET_WELL) == HIGH) {
    delay (500); //simple debounce
    if (digitalRead (PELLET_WELL) == HIGH) {
      if (OutReady == true) {
        Blink(BNC_OUT, 200, 1);
        OutReady = false;
      }
      CountReady = true;
//      for (int i = 0; i < 51 + random(0, 10); i++) {
//        if (digitalRead (PELLET_WELL) == HIGH) {
//          myMotor->step(1, BACKWARD, DOUBLE);
//        }
      	for (int i = 0; i < 20 + random(0, 10); i++){
		if(digitalRead(PELLET_WELL) === HIGH) {
			myMotor->step(7, BACKWARD, DOUBLE);
			myMotor->step(14, FORWARD, DOUBLE);
			delay(50);
		}
	}
      }
      myMotor->release();
    }
  }
  numMotorTurns++;
  delay (500);
  //Move pellet disk backwards a variable amount between 20 and 40
  if (digitalRead (PELLET_WELL) == HIGH) {
    for (int i = 0; i < 10 + random(0, 10); i++) {
      if (digitalRead (PELLET_WELL) == HIGH) {
        myMotor->step(1, FORWARD, DOUBLE);
      }
    }
    myMotor->release();
    delay(500);
  }
  if (numMotorTurns > TurnsBeforeJammed) {
    PelletJam = true;
  }
}

/********************************************************
    ClearJam makes large movements if the Feed function fails to dispense, to try to dislodge a pellet jam.
  ********************************************************/
void ClearJam() {
  numJamClears++;
  numMotorTurns = 0;
  PelletJam = false;
  DisplayJamClear();
  if (digitalRead (PELLET_WELL) == HIGH) {
    delay (500); //simple debounce
    if (digitalRead (PELLET_WELL) == HIGH) {
      for (int i = 0; i < 41 + random(0, 50); i++) {
        if (digitalRead (PELLET_WELL) == HIGH) {
          myMotor->step(i, FORWARD, DOUBLE);
        }
      }
    }
    myMotor->release();
  }
  if (digitalRead (PELLET_WELL) == HIGH) {
    delay (500); //simple debounce
    if (digitalRead (PELLET_WELL) == HIGH) {
      for (int i = 0; i < 41 + random(0, 50); i++) {
        if (digitalRead (PELLET_WELL) == HIGH) {
          myMotor->step(i, BACKWARD, DOUBLE);
        }
      }
      myMotor->release();
      numMotorTurns = 0;
    }
  }
}

