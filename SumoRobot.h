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