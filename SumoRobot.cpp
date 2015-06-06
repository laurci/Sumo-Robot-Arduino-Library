#include "SumoRobot.h"

bool twm;
int motvect[8];
int ecp, trp, trd;
int is[10];

SumoRobot::SumoRobot(char name){
	name = 'X';
}

void SumoRobot::Begin(){
	sei();
}

void SumoRobot::Stop(){
	cli();
	  while(1){
		  setMotors(0, 0);
		  delay(10);
	  }
}

void SumoRobot::irSetup(int vect[]){
 for(int i = 0; i < sizeof(vect); i++){
   pinMode(vect[i], INPUT);
   is[i] = vect[i];
  }
}

bool SumoRobot::ir(int n){
	return digitalRead(is[n - 1]);
}

void SumoRobot::ir(bool isv[]){
 for(int i = 0; i < sizeof(is); i++){
   isv[i] = digitalRead(is[i]); 
  }
}

void SumoRobot::ultraSetup(int ec, int tr, int md){
  ecp = ec;
  trp = tr;
  trd = md;
  pinMode(ecp, INPUT);
  pinMode(trp, OUTPUT);
}

bool SumoRobot::ultraRead(int &retv){
  digitalWrite(trp, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trp, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trp, LOW);
  long duration = pulseIn(ecp, HIGH);
  long distance = (duration/2) / 29.1;
  retv = distance;
  if(distance <= trd)
    return 1;
  else
    return 0;
}

void SumoRobot::initSumo(char intType, int vect[]){
	if(sizeof(vect) == 4){
    for(int i = 0; i <= 3; i++){
     motvect[i] = vect[i]; 
     pinMode(vect[i], OUTPUT);
    } 
     twm = true;
  }
  else if (sizeof(vect) == 6){
     for(int i = 0; i <= 5; i++){
     motvect[i] = vect[i];
     pinMode(vect[i], OUTPUT); 
    } 
     twm = false; 
  }
  
  if(intType == 'C'){
      OCR1A= 0x0138; 
      TCCR1B |=((1<<WGM12)|(1<<CS11)|(1<<CS10));   
      TIMSK1 |= (1<<OCIE1A);
  }
  else if(intType == 'A'){
      cli();
      TCCR1B |= (1<<WGM12);
      TIMSK1 |= (1<<OCIE1A);
      TCCR1B |= ((0<<CS12) | (1<<CS10));
      OCR1A = 0;
  }
  else if(intType == 'M'){
     TCCR1B |= _BV(CS11);
     TCCR1B |= _BV(WGM12);
     OCR1A = 10000;
     TIMSK1 |= _BV(OCIE1A);
  }
  else if(intType == 'N'){
    cli();
  }
}

void SumoRobot::setMotors(int m1, int m2){
	 if(twm){
     if(m1 >= 0 && m2 >= 0){
      analogWrite(motvect[0], m1);
      analogWrite(motvect[1], 0);
      analogWrite(motvect[2], m2);
      analogWrite(motvect[3], 0);  
     }
     if(m1 < 0 && m2 >= 0){
      analogWrite(motvect[0], 0);
      analogWrite(motvect[1], -m1);
      analogWrite(motvect[2], m2);
      analogWrite(motvect[3], 0);  
     }
     if(m1 >= 0 && m2 < 0){
      analogWrite(motvect[0], m1);
      analogWrite(motvect[1], 0);
      analogWrite(motvect[2], 0);
      analogWrite(motvect[3], -m2);  
     }
     if(m1 < 0 && m2 < 0){
      analogWrite(motvect[0], 0);
      analogWrite(motvect[1], -m1);
      analogWrite(motvect[2], 0);
      analogWrite(motvect[3], -m2);  
     }
   }
   else{
     if(m1 >= 0 && m2 >= 0){
      digitalWrite(motvect[0], 1);
      digitalWrite(motvect[1], 0);
      analogWrite(motvect[2], m1);
     
      digitalWrite(motvect[3], 1);
      digitalWrite(motvect[4], 0);
      analogWrite(motvect[5], m2); 
     }
     if(m1 < 0 && m2 >= 0){
      digitalWrite(motvect[0], 0);
      digitalWrite(motvect[1], 1);
      analogWrite(motvect[2], -m1);
     
      digitalWrite(motvect[3], 1);
      digitalWrite(motvect[4], 0);
      analogWrite(motvect[5], m2); 
     }
     if(m1 >= 0 && m2 < 0){
      digitalWrite(motvect[0], 1);
      digitalWrite(motvect[1], 0);
      analogWrite(motvect[2], m1);
     
      digitalWrite(motvect[3], 0);
      digitalWrite(motvect[4], 1);
      analogWrite(motvect[5], -m2); 
     }
     if(m1 < 0 && m2 < 0){
      digitalWrite(motvect[0], 0);
      digitalWrite(motvect[1], 1);
      analogWrite(motvect[2], -m1);
     
      digitalWrite(motvect[3], 0);
      digitalWrite(motvect[4], 1);
      analogWrite(motvect[5], -m2); 
     }
   }
}