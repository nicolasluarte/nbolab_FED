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
				lastHour = hour(rtc.getEpoch());
				deliver = true;
				}
			}
		// within feeding hours, but randomly choosen no to feed
		// feedRandHours == 0
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

if (config.randomFeed == 0){
	for (int i = 0; i < 12; i++){
		if (feedHours[i] == hour(rtc.getEpoch())){
			deliver = true;
			break;
		}
		else{
			deliver = false;
		}
	}
}

// testing config, alway feed
if (config.randomFeed == 3){
	deliver = true;
}


for (int i = 0; i < 12; i++){
	if (feedHours[i] == hour(rtc.getEpoch()) && deliver == true){
	// blockCode 1 should only feed within the first half hour
		if (blockCode == 1){
		// check if we are still within the first half hour
			bool minBool = minute(rtc.getEpoch()) >= 30;
			if (minBool == 0){
				// sets delay
				int r = (int)random(0, delaySize);
				fedDelay = config.deliveryDelay[r];
			}
			// if we are in the second half hour feeding should
			// be interrupted
			else{
				deliver = false;
			}
		}
	// blockCode 2 should only feed within the second half hour
		else if (blockCode == 2){
			bool minBool = minute(rtc.getEpoch()) >= 30;
			if (minBool == 1){
				int r = (int)random(0, delaySize);
				fedDelay = config.deliveryDelay[r];
			}
			else{
				int currMin = minute(rtc.getEpoch());
				int calcDelay = (30 - currMin) * 60;
				fedDelay = calcDelay;
			}
		}
	// blockCode 0 is for control and is the starting default
		else if (blockCode == 0){
		// sets delay for control feds
			int r = (int)random(0, delaySize);
			fedDelay = config.deliveryDelay[r];
		}
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
