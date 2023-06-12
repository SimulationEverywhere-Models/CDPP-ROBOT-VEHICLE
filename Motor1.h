/*******************************************************************
*
*  DESCRIPTION: Atomic Model Motor1
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 27/07/2009
*
*******************************************************************/

#ifndef __MOTOR1_H
#define __MOTOR1_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "string.h"	// class String

/** declarations **/
class Motor1 : public Atomic
{
public:
	Motor1( const std::string &name = "Motor1" ); //Default constructor
	virtual std::string className() const {  return "Motor1" ;}
	~Motor1();


protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &motor1_in1;
	Port &motor1_out1;
	Time motor1Time;


//	int intDelay;
//	int extDelay;
	int ackNum; // value of port
	enum State{
			Stp,	//motor1 in stop
			Pr_Trn_L,		//prepare to turn left
			Pr_Trn_R,	//prepareto turn right
			Trn_L,		//turn left
			Trn_R,		//turn right
			Pr_Stp,       // prepare to stop
	};
		State state;
};	// class Motor1

#endif   //__MOTOR1_H
