/*******************************************************************
*
*  DESCRIPTION: Atomic Model Motor3
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 07/07/2009
*
*******************************************************************/

#ifndef __MOTOR3_H
#define __MOTOR3_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "string.h"	// class String

/** declarations **/
class Motor3 : public Atomic
{
public:
	Motor3( const std::string &name = "Motor3" ); //Default constructor
	virtual std::string className() const {  return "Motor3" ;}
	~Motor3();


protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &motor3_in1;  Port &motor3_out1;
	Time motor3Time;


//	int intDelay;
//	int extDelay;
	int ackNum; // value of port
	enum State{         //to keep current state of the Compass1
				Stp,      //initial state
				Pr_Move_Fwd,    // prepare to move forward
				Pr_Move_Bck,// prepare to move backward
				Move_Fwd,  // move forward
				Move_Bck,  //move backward
				Pr_Stp    // prepare to stop
			};
			State state;

};	// class Motor3

#endif   //__MOTOR3_H
