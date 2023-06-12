/*******************************************************************
*
*  DESCRIPTION: Atomic Model Motor2
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 07/07/2009
*
*******************************************************************/

#ifndef __MOTOR2_H
#define __MOTOR2_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "string.h"	// class String

/** declarations **/
class Motor2 : public Atomic
{
public:
	Motor2( const std::string &name = "Motor2" ); //Default constructor
	virtual std::string className() const {  return "Motor2" ;}
	~Motor2();


protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &motor2_in1;  Port &motor2_out1;
	Time motor2Time;


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

};	// class Motor2

#endif   //__MOTOR2_H
