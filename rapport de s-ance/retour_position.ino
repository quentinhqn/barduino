//capteur 1
int TRIG1=2;
int ECHO1=8;
//capteur 2
int TRIG2=12;
int ECHO2=13;

//Moteur stylé
int ENA = 9;
int IN1 = 4;
int IN2 = 14;
//Moteur rouge
int ENB = 5;
int IN3 = 6;
int IN4 = 7;
void setup() {
  Serial.begin(9600);

}

void loop() {
  
  analogWrite(ENA,50);
  Serial.println(ECHO1);
  Serial.println(ECHO2);

}
