/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sonar1
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 07/08/2009
*
*******************************************************************/

#ifndef __SONAR1_H
#define __SONAR1_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "string.h"	// class String

/** declarations **/
class Sonar1 : public Atomic
{
public:
	Sonar1( const std::string &name = "Sonar1" ); //Default constructor
	virtual std::string className() const {  return "Sonar1" ;}
	~Sonar1();


protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &sonar1_in1; Port &sonar1_out1;
	Time sonar1Time;


//	int intDelay;
//	int extDelay;
	int ackNum; // value of port
	enum State{         //to keep current state of the Sonar1
		Dtcting,      //waiting an input
		Msg_Radar       // something founded send output to radar
	};
	State state;

};	// class Sonar1

#endif   //__SONAR1_H
