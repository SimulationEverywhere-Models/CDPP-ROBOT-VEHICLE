/*******************************************************************
*
*  DESCRIPTION: Atomic Model movementController
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 07/08/2009
*******************************************************************/

#ifndef __MOVEMENTCONTROLLER_H
#define __MOVEMENTCONTROLLER_H

/** include files **/
#include "atomic.h"     // class Atomic

/** declarations **/
class MovementController : public Atomic
{
public:
	MovementController( const std::string &name = "MovementController" ); //Default constructor
	virtual std::string className() const {  return "MovementController" ;}
	~MovementController();

protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &move_in1, &move_in2, &move_in3, &move_in4;
	Port &move_out1, &move_out2, &move_out3, &move_out4, &move_out5;
	Time moveTime;
	int degree1, degree2;
	enum State{
		Stp,	//initial state :stop
		Pr_Move_Fwd,		//movement controller is on: state= prepare to move forward
		Moving_Fwd,  // vehicle move forward
		MC_Stp,    // motors stop 10s
		Wait_Rdar,    // waiting radar signal
		Pr_Recv,	//prepare to receive forward degree
		Rcv_Deg,		//wait receive forward degree
		Pr_Trn,			//ask motors to turn
		Turn,          // turning
		Ask_Move_Fwd,		//move forward when degree of compass2 == degree of compass1
		Move_Fwd,       // moving to object
		Pr_Stp,     // prepare to stop, 10s
		};
	State state;
};	// class MovementController

#endif   //__MOVEMENTCONTROLLER_H
