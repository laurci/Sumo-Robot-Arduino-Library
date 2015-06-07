/*This example shows a more advanced Sumo robot and shows more functions of SumoRobot library
Made by #noFear (Tenea Mihai). All the thanks go the founder of this great library - #noName (Ciobanu Laurentiu) :)
*/

#include <SumoRobot.h>

char n = 'D'; //the initial of robot's name
// will be useful in the next version of the lib.

char iMode = 'A';//The intrerrups and timer modes.
//The options are: C - Classic Mode
//                 A - Advanced Mode
//                 M - You are crazy man 
//                 N - Disable Intrerrupts

int motors[] = {3, 11, 5, 6}; // Motor control
//Pins in order, doesn't count if 3/motor (L298 Driver)
//or 2/motor (TB6612FGN Driver)

int irSensors[] = {A2, A3}; //ir digital sensors pins in order
boolean irValues[]; //this array will save ir digital sensors values (0 / 1)

int startPin = 13; //only for the start-stop sensor used mainly in international competitions

int echoPin = A0, trigPin = A1;
// /\ - pins for the ultrasonic distance sensor ex: HC-06

int max_dist = 40; //max distance for ultrasonic sensor
int act_dist; //this will store the distance from ultrasonic sensor

SumoRobot sumo(n);

void setup(){
  sumo.initSumo(iMode, motors); //init motors and intrerrupts
  sumo.irSetup(irSensors); //init ir digital sensors
  sumo.ultraSetup(echoPin, trigPin, max_dist); //init ultrasonic sensors
  sumo.Begin();//jump to loop and start the isr
  // you can use sumo.Stop(); to stop the robot ..
  //this is good if you need to use start modules
  //for international competitions
}

void loop(){} // in this example i'm not gonna' use the loop
//keep in mind that if you wanna' data communicate with both
//loop and isr you will need to declare global variables

ISR(TIMER1_COMPA_vect){
  // here will go your normal sumo altgorithm
  
  if(digitalRead(startPin) == 1){ // if the start-stop sensor brings HIGH, it means the robot must start and do its routine
  
    //ultraRead(int x) will return true if is a object
    //in the range of max_dist, otherwise will return false
    //as well the x value will store the distance in cm
    //to that object ... 
    if(sumo.ultraRead(act_dist)){ //if enemy is in front of you  
      sumo.setMotors(255, 255);//go at maximum speed to it
    }
    
    //if you wanna' know the state of all of your
    //ir sensors you can use the function ir(boolean irsv[])
    //the vector irsv[] will store all of your sensor data...
    ir(irValues);
    if(irValues[1] == 0){ //if the left sensor sees anything
      setMotors(-150,150); //the robot will turn to the left
    }
    else if(irValues[2] == 0){ //if the right sensor sees anything
      setMotors(150,-150); //the robot will turn to the right
    }
  }
  else{ //if the start-stop sensor brings LOW, the robot must stop
    sumo.Stop();
  }
  TIFR1 |= (1<<OCF1A);
}
//The function setMotors(x, y) :
// x is the speed of the left motor
// y is the speed of, you guessed, the right motor
// the maximum speed is 255
// a negative number means: go backwords
