// This is the header file for the Sumo Robot Library for Arduino 
// by #NoName and #NoFear (Ciobanu Laurentiu and Tenea Mihai)
// If you have any problems please contact us at:
// aplharoboticsteam@gmail.com or at ciobanulaur@gmail.com
// Syntax of library is shown and described in the software 
// examples that are attached to this library
// Good luck with your sumo robot!


#ifndef SumoRobot_h
#define SumoRobot_h

#include <Arduino.h>
#include <string.h>

class SumoRobot{
	public:
		SumoRobot(char name);
		void Begin();
		void Stop();
		void irSetup(int vect[]);
		bool ir(int n);
		void ir(bool isv[]);
		void ultraSetup(int ec, int tr, int md);
		bool ultraRead(int &retv);
		void initSumo(char intType, int vect[]);
		void setMotors(int m1, int m2);
  };
  
  
#endif