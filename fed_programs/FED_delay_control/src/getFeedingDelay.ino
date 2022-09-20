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
if (config.randomFeed == 1){
  for (int i = 0; i < 12; i++){
  	if (feedHours[i] == hour(rtc.getEpoch()) && hour(rtc.getEpoch()) !=
	lastHour){
		if (feedRandHours[i] == 1){
			// 0 first half hour
			// 1 second half hour
			bool minBool = minute(rtc.getEpoch()) >= 30;
			// if feed happens in the first half hour
			// then set deliver to true but block
			// this calculation for the whole hour
			// if feed happens in the second half hour
			// then no need for delay as lastHour condition
			// takes care of all
			if (feedRandMins[i] == minBool){
				blockCode = 1;
				deliver = true;
				lastHour = hour(rtc.getEpoch());
			}
			// here calculation is blocked with a simple delay
			else{
				blockCode = 2;
				// wait for next half hour
				int currMin = minute(rtc.getEpoch());
				int calcDelay = (30 - currMin) * 60000;
				lastHour = hour(rtc.getEpoch());
				displayInt(calcDelay/60000);
				delay(calcDelay);
				deliver = true;
				}
			}
		// within feeding hours, but randomly choosen no to feed
		else{
			blockCode = 3;
			deliver = false;
			lastHour = hour(rtc.getEpoch());
		}
	}
	}
	// if not within feeding hour do not feed
   if (hour(rtc.getEpoch()) != lastHour){
	   // reselect random feeding hours and halves
		randFeedHours();
		blockCode = 4;
		deliver = false;
		lastHour = hour(rtc.getEpoch());
		}
}


for (int i = 0; i < 12; i++){
	if (feedHours[i] == hour(rtc.getEpoch())){
		// sets delay for control
		int r = (int)random(0, delaySize);
		fedDelay = config.deliveryDelay[r];
		deliver = true;
	}
	else{
		deliver = false;
		blockCode = 5;
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
