#include <Servo.h>
Servo servo1;


#include <SoftwareSerial.h>
#define RX 10
#define TX 11
char data;
SoftwareSerial Blue(RX,TX);


#include <NewPing.h>
float cm1=0;
float cm2=0;


//Différentes variables
//Distance entre 2 bouteilles en longueur MOTEUR A
int lo = 500;
//Distance entre 2 bouteilles en largeur MOTEUR B
int la = 500;
//La vitesse des moteurs
int vA = 100;
int vB = 100;
/**
 * Jusqu'ici on peut modifier
 */


//Moteur stylé
int ENA = 9;
int IN1 = 4;
int IN2 = 14;
//Moteur rouge
int ENB = 5;
int IN3 = 6;
int IN4 = 7;


//2ème essai
int choix_Cock = 0;
bool OK_prepa = false;
int cocktail[12];
int doses[12];
int bouteille = 0;
float posXplat = 0;
float posYplat = 0;
int posXrech = 0;
int posYrech = 0;
int posBoutX[7];
int Y1=13;
int Y2=2;




void position_plat(double , double );
void dosage(int );
void deplacer(int , double , double);

void setup() {



  NewPing sonar1(8,2,500);
  NewPing sonar2(13,12,500);

  
  Blue.begin(9600);
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

  posBoutX[0]=42;
  posBoutX[1]=37;
  posBoutX[2]=31;
  posBoutX[3]=24;
  posBoutX[4]=16;
  posBoutX[5]=8;
  posBoutX[6]=3;

  //cocktail 1 bouteilles 1,2,3,4
  cocktail[0]=1;
  cocktail[1]=2;
  cocktail[2]=3;
  cocktail[3]=4;
  //cocktail 2 bouteilles 1,2,5
  cocktail[4]=3;
  cocktail[5]=2;
  cocktail[6]=5;
  cocktail[7]=0;
  //cocktail 3 bouteilles 2,7,6,3
  cocktail[8]=2;
  cocktail[9]=7;
  cocktail[10]=6;
  cocktail[11]=3;

//nombre de doses associé à la bouteille de cocktail[] de même indexation
  doses[0]=1;
  doses[1]=4;
  doses[2]=2;
  doses[3]=4;
  doses[4]=1;
  doses[5]=3;
  doses[6]=3;
  doses[7]=4;
  doses[8]=2;
  doses[9]=2;
  doses[10]=1;
  doses[11]=1;
  }

void loop() {

  if (choix_Cock==0){
    while(Blue.available()){
    delay(100);
    //Serial.print(char(Blue.read()));
    delay(100);
    data=Blue.read();
    delay(100);
    Serial.print(data);
  if (data=='A'){
    choix_Cock=1;
    }
  if (data=='B'){
    choix_Cock=2;
    Serial.println("c bon");
    }
  if (data=='C'){
    choix_Cock=3;
    }
  if(data=='D'){
    choix_Cock=4;
      }
    }
  }


  if (choix_Cock != 0){
    for (int compt_Ingr=0; compt_Ingr<4; compt_Ingr++){
      bouteille=(choix_Cock-1)*4+compt_Ingr;
      deplacer(cocktail[bouteille], posXplat, posYplat);
      dosage(doses[bouteille]);
      Serial.println(doses[bouteille]);
    }
    choix_Cock=0;
  }

  
}

void deplacer(int bouteille, double posXplat, double posYplat){
  int distA=0;
  int distB=0;
  bool posOK = false;
  posXrech=posBoutX[bouteille-1];
  if (bouteille==1 or bouteille==3 or bouteille==5 or bouteille==7){
    posYrech=Y1;
  }
  else{
    posYrech=Y2;
  }
  position_plat(posXplat, posYplat);
  if (posXrech-posXplat<0){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
  }
  else{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
  }
  if (posYrech-posYplat<0){
    digitalWrite(IN4,HIGH);
    digitalWrite(IN3,LOW);
  }
  else{
    digitalWrite(IN4,LOW);
    digitalWrite(IN3,HIGH);
  }
  if (bouteille==0){
    posOK == true;
  }
  while (posOK == false){
    position_plat(posXplat, posYplat);
    distA=posXrech-posXplat;
    if (distA<0){
      distA=-distA;
    }
    distB=posYrech-posYplat;
    if (distB<0){
      distB=-distB;
    }
    if (distA>255){
    distA=255;
    }
    if (distB>255){
      distB=255;
    }
    if (distA<15){
      distA=15;
    }
    if (distB<15){
      distB=15;
    }
    if (distA<2 and distB<2){
      posOK=true;
      distA=0;
      distB=0;
    }
    analogWrite(ENA,distA);
    analogWrite(ENB,distB);
  }
}
//verse un certain nombre de doses dans le verre
void dosage(int doses){
  
  servo1.attach(3);
  for(int i=0; i<doses; i++){
    servo1.write(90);
    delay(5000);
    servo1.write(0);
    delay(5000);
  }
  
  servo1.detach();
}


//actualise la position du plateau en x et en y
void position_plat(double posXplat, double posYplat){
  NewPing sonar1(8,2,500);
  delay(100);
  NewPing sonar2(13,12,500);
  delay(100);
  double x = sonar1.ping_cm();
  double y = sonar2.ping_cm();
  
  if (x!=0){
    posXplat = x;
    Serial.print("cm1=");
    Serial.println(posXplat);
    }
  if (y!=0){
    posYplat = y;
    Serial.print("cm2=");
    Serial.println(posYplat);
    }
    
}
