void logdata() {
  if (logReady == true) {
    logReady = false;
    DisplaySDLogging();

    Blink(GREEN_LED, 25, 3);
    Blink(RED_LED, 25, 2);        // quick blinks on each LED shows we're logging data

    CurrentCycleCount += 1;       //  Increment samples in current uSD flush cycle
    CurrentFileCount += 1;        //  Increment samples in current file
    WriteToSD();

    //  Code to limit the number of power hungry writes to the uSD
    //  Don't sync too often - requires 2048 bytes of I/O to SD card. 512 bytes of I/O if using Fat16 library
    //  But this code forces it to sync at a fixd interval, i.e. once per hour etc depending on what is set
    if ( CurrentCycleCount >= SamplesPerCycle ) {
      logfile.flush();
      CurrentCycleCount = 0;
    }

    // Code to increment files limiting number of lines in each hence size, close the open file first.
    if ( CurrentFileCount >= SamplesPerFile ) {
      if (logfile.isOpen()) {
        logfile.close();
      }
      CreateFile();
      CurrentFileCount = 0;
    }
  }
}

// Create new file on uSD incrementing file name as required
void CreateFile()
{
  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect)) {
    error(2);
  }

  // Name filename in format F###_MMDDYYNN, where MM is month, DD is day, YY is year, and NN is an incrementing number for the number of files initialized each day
//  strcpy(filename, "FED_____________.CSV");  // placeholder filename
//  getFilename(filename);

//  logfile = SD.open(filename, FILE_WRITE);
//  if ( ! logfile ) {
//    error(3);
//  }
//  else {
//    DisplaySd();
//  }
//    logfile.open(filename, O_CREAT | O_WRITE | O_APPEND);
//  if(logfile.open("data5.csv", O_CREAT | O_WRITE | O_APPEND)) {
//    logfile.print("TEST");
//    logfile.println();
//    logfile.close();
//    delay(1000);
//  }
}

// Write data header to file of uSD.
void writeHeader() {
//  logfile.println("MM:DD:YYYY hh:mm:ss, Mouse, PelletCount, MotorTurns, BatteryVoltage");
}

// Print data and time followed by pellet count and motorturns to SD card
void WriteToSD() {
  logfile.print(rtc.getMonth());
  logfile.print("/");
  logfile.print(rtc.getDay());
  logfile.print("/");
  logfile.print(rtc.getYear() + 2000);
  logfile.print(" ");
  logfile.print(rtc.getHours());
  logfile.print(":");
  if (rtc.getMinutes() < 10)
    logfile.print('0');      // Trick to add leading zero for formatting
  logfile.print(rtc.getMinutes());
  logfile.print(":");
  if (rtc.getSeconds() < 10)
    logfile.print('0');      // Trick to add leading zero for formatting
  logfile.print(rtc.getSeconds());
  logfile.print(",");
  logfile.print(FED); // Print FED name
  logfile.print(",");
  logfile.print(PelletCount); // Print pellet counts
  logfile.print(",");
  logfile.print((numJamClears*10)+numMotorTurns); // Print the number of attempts to dispense a pellet, including through jam clears
  numMotorTurns = 0; //reset numMotorTurns  
  numJamClears=0; // reset numJamClears
  logfile.print(",");
  logfile.println(measuredvbat); // Print battery voltage
  logfile.print(",");
  logfile.println(delayPick);
}

void error(uint8_t errno) {
  DisplaySDError();
  while (1) {
    uint8_t i;
    for (i = 0; i < errno; i++) {
      Blink(GREEN_LED, 25, 2);
      Blink(RED_LED, 25, 2);
    }
    for (i = errno; i < 10; i++) {
      delay(100);
    }
  }
}
//void getFilename(char *filename) {
//  filename[3] = FED / 100 + '0';
//  filename[4] = FED / 10 + '0';
//  filename[5] = FED % 10 + '0';
//  filename[7] = months / 10 + '0';
//  filename[8] = months % 10 + '0';
//  filename[9] = days / 10 + '0';
//  filename[10] = days % 10 + '0';
//  filename[11] = years / 10 + '0';
//  filename[12] = years % 10 + '0';
//  filename[16] = '.';
//  filename[17] = 'C';
//  filename[18] = 'S';
//  filename[19] = 'V';
//  for (uint8_t i = 0; i < 100; i++) {
//    filename[14] = '0' + i / 10;
//    filename[15] = '0' + i % 10;
//    // create if does not exist, do not open existing, write, sync after write
//    if (! SD.exists(filename)) {
//      break;
//    }
//  }
//  return;
//}

  void getFilename(char *filename) {
    filename[0] = '2';
    filename[1] = '0';
    filename[2] = '0';
    filename[3] = '0';
    filename[4] = '0';
    filename[5] = '0';
    filename[6] = '0';
    filename[7] = '0';
    filename[8] = '.';
    filename[9] = 'C';
    filename[10] = 'S';
    filename[11] = 'V';
    return;
  }
