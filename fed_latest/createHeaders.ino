void createHeaders(){
  // if logfile is empty write headers
  if (logfile.size() == 0){
    logfile.println("time,animal,pellets,motorTurns,battery,delay");
  }
  logfile.flush();
}
