void writeData(){
  sprintf(data, "%02d,%02d,%02d,%02d,%02d,%02d,%02d", rtc.getEpoch(), config.animal, pelletCount, motorTurns, battery, fedDelay, numClears);
  Serial.println(data);
  logfile.println(data);
  logfile.flush();
  dataLog = true;
}