#include<Servo.h>
Servo servo1;

void setup() {
  servo1.attach(3);
  pinMode(3,OUTPUT);
}

void loop() {
  servo1.write(00);
  delay(1000);
  servo1.write(90);
  delay(1000);

}
