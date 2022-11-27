void readBatteryLevel(){
    measuredvbat = analogRead(VBATPIN);
    measuredvbat *= 2;
    measuredvbat *= 3.3;
    measuredvbat /= 1024;
    if (measuredvbat > 3.85){
        batt = 4;
    }
    else if (measuredvbat > 3.7){
        batt = 3;
    }
    else if (measuredvbat > 3.55){
        batt = 2;
    }
    else{
        batt = 1;
    }
}
