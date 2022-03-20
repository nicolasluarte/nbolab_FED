void writeData(){
  sprintf(data, "%02d,%02d,%02d,%02d,%02d,%02d,%02d", rtc.getEpoch(), config.animal, pelletCount, motorTurns, batt, fedDelay, config.protocol);
  Serial.println(data);
  logfile.println(data);
  logfile.flush();
  dataLog = true;
}