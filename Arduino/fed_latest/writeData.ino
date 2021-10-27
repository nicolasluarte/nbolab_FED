void writeData(){
  sprintf(data, "%02d,%02d,%02d,%02d,%02d,%02d", rtc.getEpoch(), config.animal, pelletCount, motorTurns, battery, fedDelay);
  Serial.println(data);
  dataLog = true;
}
