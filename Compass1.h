/*******************************************************************
*
*  DESCRIPTION: Atomic Model Compass1
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 11/08/2009
*
*******************************************************************/

#ifndef __COMPASS1_H
#define __COMPASS1_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "string.h"	// class String

/** declarations **/
class Compass1 : public Atomic
{
public:
	Compass1( const std::string &name = "Compass1" ); //Default constructor
	virtual std::string className() const {  return "Compass1" ;}
	~Compass1();


protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &compass1_in1, &compass1_in2;
	Port &compass1_out1;
	Time compass1Time;


//	int intDelay;
//	int extDelay;
	int ackNum;
	double degree1; // value of port
	enum State{         //to keep current state of the Compass1
			Idle,      //initial state
			Trning,    // turn when it receive input from event file
			Send_Out// send degree at radar controller when motor1 stop
		};
		State state;

};	// class Compass1

#endif   //__COMPASS1_H
