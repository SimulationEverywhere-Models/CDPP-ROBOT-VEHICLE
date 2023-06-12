/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sonar2
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 07/08/2009
*
*******************************************************************/

#ifndef __SONAR2_H
#define __SONAR2_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "string.h"	// class String

/** declarations **/
class Sonar2 : public Atomic
{
public:
	Sonar2( const std::string &name = "Sonar2" ); //Default constructor
	virtual std::string className() const {  return "Sonar2" ;}
	~Sonar2();


protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &sonar2_in1, &sonar2_in2;
	Port &sonar2_out1;
	Time sonar2Time, sonar2Time1;


//	int intDelay;
//	int extDelay;
	int ackNum, distance; // value of port
	enum State{         //to keep current state of the Sonar2
			Idle,
			Dtcting,      //begin detecting
			Msg_MC,       // if distance from vehicle is 10cm send message stop at movement controller
			Mtching,
			Send_Out
		};
		State state;
};	// class Sonar2

#endif   //__SONAR2_H
