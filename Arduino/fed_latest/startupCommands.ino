void startupCommands(){
  // PI setup
  pinMode(PELLET_WELL, INPUT_PULLDOWN);
  pinMode (RED_LED, OUTPUT);
  pinMode (GREEN_LED, OUTPUT);
  attachInterrupt(PELLET_WELL, wake, RISING);
  // motor setup
  AFMS.begin(1000);  // create with the default frequency 1.6KHz
  myMotor->setSpeed(100);
}

void wake() {
  digitalWrite (RED_LED, HIGH);  //RED LED is on when device is awake
}
