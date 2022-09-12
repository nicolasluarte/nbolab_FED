void getFeedingDelay(){
//  if (shuffle){
//    shuffleArray(dayHours, 21);
//    shuffle = false;
//    lastShuffle = rtc.getEpoch();
//    // select the first 6 from shuffled array
//    for (int i = 0; i < 6; i++){
//      sampleHours[i] = dayHours[i];
//    }
//  }

  // only feed if within the lights-off period
  // run through all feeding hours
  for (int i = 0; i < 11; i++){
  	if (feedHours[i] == hour(rtc.getEpoch()) && hour(rtc.getEpoch()) !=
	lastHour){
	// if protocol is experimental then
	// toss a coin to either deliver pellet or not
		if (randomFeed == 1){
			// randomize every time is called
			randomSeed(analogRead(0));
			int randNumber = random(1, 3);
			// if random number is one the no feed this hour
			if (randNumber == 1){
				feed = false;
				lastHour = hour(rtc.getEpoch());
				// not used but used to set a delay
				int r = (int)random(0, delaySize);
				fedDelay = config.deliveryDelay[r];
				}
			}
			// if random number is two then feed is ok
			else {
				feed = true;
				lastHour = hour(rtc.getEpoch());
				int r = (int)random(0, delaySize);
				fedDelay = config.deliveryDelay[r];
				}
	// if protocol is control randomFeed == 0, then feed is always
	// on within the feeding hour
		else{
		feed = true;
		int r = (int)random(0, delaySize);
		fedDelay = config.deliveryDelay[r];
		}
	}
	// if not within feeding hour do not feed
	else{
		feed = false;
		// not used but used to set a delay
		int r = (int)random(0, delaySize);
		fedDelay = config.deliveryDelay[r];
		}
	}

//  // choose random delay
//  // check if fed should send long delay
//  for (int i = 0; i < config.longDelayCounter; i++){
//    if(sampleHours[i] == hour(rtc.getEpoch())){
//      sampleHours[i] = 99; // find a better way to drop this hour
//      match = true;
//      fedDelay = config.longDelay;
//      break; // found a match
//    }
//    else{
//      match = false;
//      // Resets every day
//      if (day(rtc.getEpoch()) != day(lastShuffle)){
//        shuffle = true;
//      }
//    }
//  }
//  // if not within the shuffled hour choose a random delay
//  if (!match){
//    Serial.println("Random delay choosen");
//    int r = (int)random(0, delaySize);
//    fedDelay = config.deliveryDelay[r];
//  }

}
