void sdSetup(){
  if (SD.begin(4)){
    displaySDSuccess();
    delay(1000);
  }
  else{
    displaySDError();
    delay(1000);
  }
}
