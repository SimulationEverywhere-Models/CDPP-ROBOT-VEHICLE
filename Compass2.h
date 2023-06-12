/*******************************************************************
*
*  DESCRIPTION: Atomic Model Compass2
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 11/08/2009
*
*******************************************************************/

#ifndef __COMPASS2_H
#define __COMPASS2_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "string.h"	// class String

/** declarations **/
class Compass2 : public Atomic
{
public:
	Compass2( const std::string &name = "Compass2" ); //Default constructor
	virtual std::string className() const {  return "Compass2" ;}
	~Compass2();


protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &compass2_in1, &compass2_in2;
	Port &compass2_out1;
	Time compass2Time;


//	int intDelay;
//	int extDelay;
	int ackNum, degree, degree1,degree2; // value of port
	enum State{         //to keep current state of the Compass1
			Stp,      //initial state
			Matching,    // turn when it receive degree of compass1 from MC
			Send_MC,// send message when degree of compass2 = degree compass1
			Dtcting,  // detecting the forward degree
			Send_Out  // send the forward degree
		};
		State state;

};	// class Compass2

#endif   //__COMPASS2_H
