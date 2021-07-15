
int DELAY[] = {15, 45, 120, 240};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int index = random(sizeof(DELAY) / sizeof(DELAY[0]));
  int delayPick = DELAY[index];
  Serial.println(delayPick);
  delay(1000);

}
