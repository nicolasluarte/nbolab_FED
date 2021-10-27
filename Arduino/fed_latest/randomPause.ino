void randomPause(){

  // gets the current hour
  unsigned long epoch = rtc.getEpoch();

  // check if current hour matches any hour in the array
  for (int i = 0; i < blockSize; i++){
    if (minute(epoch) == config.blocks[i]){
      blockMatch[i] = 1;
    }
    else{
      blockMatch[i] = 0;
    }
  }
  for (int i = 0; i < blockSize; i++){
    arraySum = arraySum + blockMatch[i];
  }
  if (arraySum > 0){
    blockDelivery = true;
  }
  else{
    blockDelivery = false;
  }
  arraySum = 0;

}
