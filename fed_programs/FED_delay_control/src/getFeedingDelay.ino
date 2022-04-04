void getFeedingDelay(){
  if (shuffle){
    shuffleArray(dayHours, 21);
    shuffle = false;
    lastShuffle = rtc.getEpoch();
    // select the first 6 from shuffled array
    for (int i = 0; i < 6; i++){
      sampleHours[i] = dayHours[i];
    }
  }

  // choose random delay
  // check if fed should send long delay
  for (int i = 0; i < config.longDelayCounter; i++){
    if(sampleHours[i] == hour(rtc.getEpoch())){
      sampleHours[i] = 99; // find a better way to drop this hour
      match = true;
      fedDelay = config.longDelay;
      break; // found a match
    }
    else{
      match = false;
      // Resets every day
      if (day(rtc.getEpoch()) != day(lastShuffle)){
        shuffle = true;
      }
    }
  }
  // if not within the shuffled hour choose a random delay
  if (!match){
    Serial.println("Random delay choosen");
    int r = (int)random(0, delaySize);
    fedDelay = config.deliveryDelay[r];
  }

}
