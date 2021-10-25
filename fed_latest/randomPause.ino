void randomPause(){

  // gets the current hour
  unsigned long epoch = rtc.getEpoch();
  // random array is reseted at 24 hours every day
  if (second(epoch) % 1 == 0){
    int tmp[13];
    for (int i = 0; i < randomHoursSize; i++){
      int idx = random(0, 12);
      while(tmp[idx] == -1){
        idx = random(0, 12);
      }
      hourArray[i] = HH[idx];
      Serial.println(hourArray[i]);
      tmp[idx] = -1;
    }
  }
  
  int hourArray[] = {10, 30};
  float results[2];
  int matchedTimes = 0;
  
  for(int i = 0; i < 2; i++){
    if(second(epoch)== hourArray[i]){
      results[i] = 1;
    }
    else{
      results[i] = 0;
    }
    matchedTimes = matchedTimes + results[i];
  }
  //Serial.println(matchedTimes);
  
  if (matchedTimes == 1){
    Serial.println("Pausing pellet delivery...");
    pauseDelivery = true;
  }
  else{
    Serial.println("Delivering pellets");
    pauseDelivery = false;
  }
}
