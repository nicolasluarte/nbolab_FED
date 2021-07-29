/********************************************************
  Start Up Commands
********************************************************/

void StartUpCommands () {
  Serial.begin(115200);

  /********************************************************
    These commands are associated with the low power sleep states
  ********************************************************/
  //SYSCTRL->VREG.bit.RUNSTDBY = 1;
  SYSCTRL->DFLLCTRL.bit.RUNSTDBY = 1;
  USBDevice.detach();
  for (byte i = 0; i <= 20; i++) {
    pinMode(i, INPUT_PULLDOWN);
  }

  /********************************************************
     These commands set the time on the FED to the current computer time - unfortunately FED needs to be reflashed to update the time

   ********************************************************/
  rtc.begin(); // initialize RTC

  // Set the time and date. Change this to your current date and time.
  // setTime(16,19,00,12,3,2016);    //values in the order hr,min,sec,day,month,year

  // Let's be lazy and let the compiler set the current date and time for us.
  // This will be a few seconds off due to the time it takes to compile the
  // .ino file and upload the app. But pretty close.

  // __DATE__ is a C++ preprocessor string with the current date in it.
  // It will look something like 'Mar  13  2016'.
  // So we need to pull those values out and convert the month string to a number.
  sscanf(__DATE__, "%s %d %d", s_month, &tday, &tyear);

  // Similarly, __TIME__ will look something like '09:34:17' so get those numbers.
  sscanf(__TIME__, "%d:%d:%d", &thour, &tminute, &tsecond);

  // Find the position of this month's string inside month_names, do a little
  // pointer subtraction arithmetic to get the offset, and divide the
  // result by 3 since the month names are 3 chars long.
  tmonth = (strstr(month_names, s_month) - month_names) / 3;

  months = tmonth + 1;  // The RTC library expects months to be 1 - 12.
  days = tday;
  years = tyear - 2000; // The RTC library expects years to be from 2000.
  hours = thour;
  minutes = tminute;
  seconds = tsecond;

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(days, months, years);


  /********************************************************
    Setting digital pin modes
  ********************************************************/
  pinMode(PELLET_WELL, INPUT_PULLDOWN);
  pinMode (RED_LED, OUTPUT);
  pinMode (GREEN_LED, OUTPUT);
  attachInterrupt(PELLET_WELL, wake, RISING);
  /********************************************************
    Start, clear, and setup the Sharp Memory display
  ********************************************************/
  display.begin();
  display.clearDisplay();
  minorHalfSize = min(display.width(), display.height()) / 2;
  StartUpDisplay ();

  /********************************************************
    SD Card setup function
  ********************************************************/
//  CreateFile();
//  writeHeader();

  /********************************************************
    Set up stepper
  ********************************************************/
  AFMS.begin(1000);  // create with the default frequency 1.6KHz
  myMotor->setSpeed(100);

}
