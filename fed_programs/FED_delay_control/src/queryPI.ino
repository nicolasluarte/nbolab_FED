void queryPI(){
	// attempt multiple sensor readings
	for (int i = 0; i < 5; i++){
		detector = digitalRead(PELLET_WELL);	
		if (detector == LOW){
			break;
			}
		delay(50);
		}
  if (detector == LOW) {
    pellet = true;
    // only write if data has not been logged
    if (!dataLog){
      pelletCount++;
      blockDisplay = false;
      writeData();
      // resets motor count so this data is
      // related to every pellet delivery
      motorTurns = 0;
      pelletJam = false; // pellet delivered so jam is solved
      numClears = 0; // related to pellet
    }
  }
  else{
    pellet = false;
    // reset the bool so when pellet is delivered
    // data is written again
    dataLog = false;
  }
}
