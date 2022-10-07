void writeData(){
  sprintf(data, "%02d,%02d,%02d,%02d,%02d,%02d,%s", rtc.getEpoch(),
  config.animal, pelletCount, blockCode, batt, fedDelay, config.protocol);
  Serial.println(data);
  logfile.println(data);
  logfile.flush();
  dataLog = true;
}
