#include <NewPing.h>
float cm1=0;
float cm2=0;

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
    //on configure en sorties
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  //pareil pour moteur rouge
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
//on dit au moteurs de ne pas tourner
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
//on donne la direction de départ du moteur stylé
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
//pareil pour moteur rouge
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void loop() {
  
  NewPing sonar1(8,2,500);
  delay(100);
  NewPing sonar2(13,12,500);
  delay(100);
  cm1 = sonar1.ping_cm();
  cm2 = sonar2.ping_cm();
  Serial.print("cm1=");
  Serial.println(cm1);
  Serial.print("cm2=");
  Serial.println(cm2);
  
  analogWrite(ENB,90);
  
 // analogWrite(ENA,90);

}
