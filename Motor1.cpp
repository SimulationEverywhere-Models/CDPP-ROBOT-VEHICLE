/*******************************************************************
*
*  DESCRIPTION: Atomic Model Motor1
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*  DATE: 27/07/2009
*******************************************************************/

/** include files **/
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "Motor1.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Motor1
* Description: constructor
********************************************************************/
Motor1::Motor1( const std::string &name ) : Atomic( name )
, motor1_in1( addInputPort( "motor1_in1" ) )
, motor1_out1( addOutputPort( "motor1_out1" ) )
, motor1Time (00,00,10,00)
{
	std::string timepreparation( MainSimulator::Instance().getParameter( description(), "stoppreparationTime" ) ) ;
//test
	if (timepreparation !="") motor1Time = timepreparation;
	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"motor1Time="<<motor1Time<<"\n";
}

/*******************************************************************
* Function Name: Motor1::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Motor1::initFunction()
{

	state = Stp;		// stop
	return *this ;
}
/*******************************************************************
* Function Name: motor1::externalFunction()
* Description: External Function Motor1
********************************************************************/
Model &Motor1::externalFunction( const ExternalMessage &msg )
{

	if (msg.port() == motor1_in1)
		{
		ackNum = static_cast <int> (msg.value());
		if(state == Stp)
		{
				if (ackNum == 1)
				{
					state  = Pr_Trn_R;
					holdIn(Atomic::active, motor1Time);
				}
				else if (ackNum == 2)
						{
							state  = Pr_Trn_L;
							holdIn(Atomic::active, motor1Time);
						}
		}
		else if(state == Trn_R)
		{
			if(ackNum == 2)
			{
				state = Pr_Trn_L;
				holdIn(Atomic::active, motor1Time);
			}
			else if(ackNum == 0)
			{
				state = Pr_Stp;
				holdIn(Atomic::active, motor1Time);
			}
		}
		else if(state==Trn_L)
		{
					if(ackNum == 1)
					{
						state = Pr_Trn_R;
						holdIn(Atomic::active, motor1Time);
					}
					else if(ackNum == 0)
					{
						state = Pr_Stp;
					    holdIn(Atomic::active, motor1Time);
					}
		}
		}
		return *this;
}

/*******************************************************************
* Function Name: Motor1::internalFunction()
* Description: Internal Function Motor1
********************************************************************/
Model &Motor1::internalFunction( const InternalMessage & )
{


	switch (state){
				case Pr_Trn_R:
					state = Trn_R;
					passivate();
					break;

				case Pr_Trn_L:
					state = Trn_L;
				  passivate();
					break;

				case Pr_Stp:
					state = Stp;
				    passivate();
					break;
	}
		return *this;
}

/*******************************************************************
* Function Name: Motor1::outputFunction()
* Description: Output function Motor1 - writes info about time and events
********************************************************************/
Model &Motor1::outputFunction( const InternalMessage &msg )
{
	if (state == Pr_Trn_L){
		sendOutput( msg.time(), motor1_out1, 2) ;//turning left
	}
	else if (state == Pr_Trn_R){
		sendOutput( msg.time(), motor1_out1, 1) ;// turning right

	}
	else if(state==Pr_Stp){
		sendOutput( msg.time(), motor1_out1, 0) ;//stopping

	}
	return *this ;
}

Motor1::~Motor1()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
