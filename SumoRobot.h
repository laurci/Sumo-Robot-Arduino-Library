#ifndef SumoRobot_h
#define SumoRobot_h

#include <Arduino.h>
#include <string.h>

extern "C" {
    typedef void (*robotCallbackFunction)(void);
}

class SumoRobot{
	public:
		SumoRobot(robotCallbackFunction newFunction);
		SumoRobot(robotCallbackFunction newFunction, int start_pin);
		void Begin();
		void Stop();
		void irSetup(int vect[]);
		bool ir(int n);
		void ir(boolean isv[]);
		void ultraSetup(int ec, int tr, int md);
		bool ultraRead(int &retv);
		void initSumo(char intType, int vect[]);
		void setMotors(int m1, int m2);
		void irAnalogSetup(int vect[]);
		void irAnalogRead(int n, int &val);
		void irAnalogRead(int vect[]);
	
	private:
		void actionOn();
  };
  
  
#endif