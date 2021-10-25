void queryPI(){
  if (digitalRead(PELLET_WELL) == LOW) {
    pellet = true;
    // only write if data has not been logged
    if (!dataLog){
      pelletCount++;
      blockDisplay = false;
      writeData();
      // resets motor count so this data is
      // related to every pellet delivery
      motorTurns = 0;
    }
  }
  else{
    pellet = false;
    // resest the bool so when pellet si delivered
    // data is written again
    dataLog = false;
  }
}
