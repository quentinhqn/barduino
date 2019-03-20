#include <Servo.h>
Servo servo1;

#include <SoftwareSerial.h>
#define RX 6
#define TX 11
char data;
SoftwareSerial Blue(RX,TX);


#include <NewPing.h>
float cm1=0;
float cm2=0;



//Moteur stylé
int ENA = 3;
int IN1 = 4;
int IN2 = 14;
//Moteur rouge
int ENB = 5;
int IN3 = 9;
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

void deplacer(int);

float positionXplat();
float positionYplat();
void deplacerX(int);
void deplacerY(int);
void moteurX(bool);
void moteurY(bool);
void dosage(int );

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

  posBoutX[0]=46;
  posBoutX[1]=42;
  posBoutX[2]=35;
  posBoutX[3]=23;
  posBoutX[4]=17;
  posBoutX[5]=8;
  posBoutX[6]=5;

  //cocktail 1 bouteilles 7,2,3,4
  cocktail[0]=7;
  cocktail[1]=2;
  cocktail[2]=3;
  cocktail[3]=4;
  //cocktail 2 bouteilles 4,6,5
  cocktail[4]=3;
  cocktail[5]=2;
  cocktail[6]=5;
  cocktail[7]=0;
  //cocktail 3 bouteilles 2,5,6,3
  cocktail[8]=2;
  cocktail[9]=5;
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
  doses[7]=0;
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
    Serial.println("le1");
    }
  if (data=='B'){
    choix_Cock=2;
    Serial.println("le2");
    }
  if (data=='C'){
    choix_Cock=3;
    Serial.println("le3");
    }
  if(data=='D'){
    Serial.println("mauvaise commande");
      }
    }
  


  if (choix_Cock != 0){
    for (int compt_Ingr=0; compt_Ingr<4; compt_Ingr++){
      bouteille=(choix_Cock-1)*4+compt_Ingr;
      if(cocktail[bouteille] != 0){
      deplacer(cocktail[bouteille]);
      delay(500);
      deplacer(cocktail[bouteille]);
      //deplacerX(cocktail[bouteille]);
      //deplacerY(cocktail[bouteille]);
      Serial.println("ok");
      dosage(doses[bouteille]);}
    }
    choix_Cock=0;
    Serial.println("Le cocktail est fini");
    delay(10000);
  }

  
}
}

  


void deplacerX(int bouteille){
  bool a=false;
  posXrech=posBoutX[bouteille-1];
  while(a==false){
  double posXplat = positionXplat();
  if(posXrech<posXplat){
    moteurX(false);
  }
  else if(posXrech >posXplat){
    moteurX(true);
  }
  else if(posXrech==posXplat){
    a=true;
    analogWrite(ENA, 0);
  }
  }
}


void deplacerY(int bouteille){
  bool b=false;
  if (bouteille==1 or bouteille==3 or bouteille==5 or bouteille==7){
    posYrech=Y1;
  }
  else{
    posYrech=Y2;
  }
  while(b==false){
  double posYplat = positionYplat();
  if(posYrech<posYplat){
    moteurY(true);
  }
  else if(posYrech >posYplat){
    moteurY(false);
  }
  else if(posYrech==posYplat){
    b=true;
    analogWrite(ENB, 0);
  }
  }
}

void deplacer(int bouteille){
  bool b=false;
  if (bouteille==1 or bouteille==3 or bouteille==5 or bouteille==7){
    posYrech=Y1;
  }
  else{
    posYrech=Y2;
  }
  bool c=false;
  bool a=false;
  posXrech=posBoutX[bouteille-1];
  while(c==false){
  double posXplat = positionXplat();
  if (a==false){
  if(posXrech<posXplat){
    moteurX(false);
  }
  else if(posXrech >posXplat){
    moteurX(true);
  }
  else if(posXrech==posXplat){
    a=true;
    analogWrite(ENA, 0);
  }
  }
  if (b==false){
  double posYplat = positionYplat();
  if(posYrech<posYplat){
    moteurY(true);
  }
  else if(posYrech >posYplat){
    moteurY(false);
  }
  else if(posYrech==posYplat){
    b=true;
    analogWrite(ENB, 0);
  }
  }
  if (a==true){
    if (b==true){
      c=true;
    }
  }
  }
}

//direction=true, vers la droite
//direction=false, vers la gauche
void moteurX(bool direction){
  if (direction==true){
    
  Serial.println("la");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 150);}
  
  if (direction==false){
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
  analogWrite(ENA, 150);}
}

//direction=true, vers l'arrière
//direction=false, vers l'avant
void moteurY(bool direction){
  if (direction==false){
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  analogWrite(ENB, 150);}
  
  if (direction==true){
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
    analogWrite(ENB, 150);}
}

//verse un certain nombre de doses dans le verre
void dosage(int doses){
  Serial.print("on verse ");
  Serial.print(doses);
  Serial.println(" doses");
  servo1.attach(10);
  for(int i=0; i<doses; i++){
    servo1.write(90);
    //servo1.detach();
    delay(5000);
    //servo1.attach(3);
    servo1.write(0);
    //servo1.detach();
    delay(5000);
    //servo1.attach(3);
  }
  
  servo1.detach();
}


//actualise la position du plateau en x et en y
float positionYplat(){
  bool posOK=false;
  double x=0;
  while(posOK==false){
  NewPing sonar1(2,8,500);
  delay(100);
  x = sonar1.ping_cm();
  Serial.print("POSITION Y = ");
  Serial.println(x);
  if (x!=0){
    if (x<100){
    posOK=true;}
    }
  }
  return x;
}

float positionXplat(){
  bool posOK=false;
  double x=0;
  while(posOK==false){
  NewPing sonar1(13,12,500);
  delay(100);
  x = sonar1.ping_cm();
  
  Serial.print("POSITION X = ");
  Serial.println(x);
  if (x!=0){
    if (x<100){
    posOK=true;}
    }
  }
  return x;
}
