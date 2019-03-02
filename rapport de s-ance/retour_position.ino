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



double i=0;
double j=0;
void setup() {
  Serial.begin(9600);

}

void loop() {
  
  analogWrite(ENA,50);
  digitalWrite(TRIG1,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG1,LOW);
    i=pulseIn(ECHO1,HIGH);

    digitalWrite(TRIG2,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG2,LOW);
    j=pulseIn(ECHO2,HIGH);
  Serial.println(i);
  Serial.println(j);

}
