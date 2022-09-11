void sdSetup(){
  if (SD.begin(4)){
    displaySDSuccess();
    delay(1000);
  }
  else{
	  while(true){
	    displaySDError();
	    delay(1000);
	  }
  }
}
