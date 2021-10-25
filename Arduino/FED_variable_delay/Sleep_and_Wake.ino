/********************************************************
   FUNCTION IS CALLED WHEN PELLET_WELL_PIN IS INTERRUPTED
   AND TURNS THE RED LED ON WHENEVER DEVICE IS AWAKE
 *****************************************************/
void wake() {
  digitalWrite (RED_LED, HIGH);  //RED LED is on when device is awake
}

/********************************************************
   FUNCTION FOR PUTTING THE ADALOGGER TO SLEEP
 *****************************************************/
void sleep () {
  myMotor->release();
  digitalWrite (RED_LED, LOW);
  if (digitalRead(PELLET_WELL) == LOW ) {
    delay (1000);
    if (digitalRead(PELLET_WELL) == LOW ) {
      rtc.standbyMode();
      weird ();
    }
  }
}
