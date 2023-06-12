/*******************************************************************
*
*  DESCRIPTION: Atomic Model RadarController
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 06/08/2009
*******************************************************************/

#ifndef __RADARCONTROLLER_H
#define __RADARCONTROLLER_H

/** include files **/
#include "atomic.h"     // class Atomic

/** declarations **/
class RadarController : public Atomic
{
public:
	RadarController( const std::string &name = "RadarController" ); //Default constructor
	virtual std::string className() const {  return "RadarController" ;}
	~RadarController();

protected:

	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &radar_in1, &radar_in2, &radar_in3;
	Port &radar_out1, &radar_out2, &radar_out3;
	Time radarTime, turnTime;
	int degree1;
	enum State{
		Idle,	//wait input from Movement controller
		Pr_Wrk,		//radar Controller prepare to work
		Trn_Right,	//ask motor1 to turn right
		Trn_Left,		//ask motor1 to turn left
		Ask_Stp,		//ask motor1 and MC to stop
		Wait,       // radar waiting
		Send_MC};			//ask MC to stop
	State state;
};	// class RadarController

#endif   //__RADARCONTROLLER_H
