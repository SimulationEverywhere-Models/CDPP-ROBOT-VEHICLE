/*******************************************************************
*
*  DESCRIPTION: Atomic Model Motor3
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*  DATE: 07/07/2009
*******************************************************************/

/** include files **/
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "Motor3.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Motor3
* Description: constructor
********************************************************************/
Motor3::Motor3( const std::string &name ) : Atomic( name )
, motor3_in1( addInputPort( "motor3_in1" ) )
, motor3_out1( addOutputPort( "motor3_out1" ) )
, motor3Time (00,00,10,00)
{
	std::string timepreparation( MainSimulator::Instance().getParameter( description(), "motor3processingTime" ) ) ;
//test
	if (timepreparation !="") motor3Time = timepreparation;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"motor3Time="<<motor3Time<<"\n";
}

/*******************************************************************
* Function Name: motor3::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Motor3::initFunction()
{

	state = Stp;		// stop
	return *this ;
}
/*******************************************************************
* Function Name: motor3::externalFunction()
* Description: External Function Motor3
********************************************************************/
Model &Motor3::externalFunction( const ExternalMessage &msg )
{

	if (msg.port() == motor3_in1)
		{
		ackNum = static_cast <int> (msg.value());
			if (state == Stp)
			{
				if (ackNum == 1)
				{
					state  = Pr_Move_Fwd;
					holdIn(Atomic::active, motor3Time);
				}
				else if (ackNum==2)
				{
					state = Pr_Move_Bck;
					holdIn(Atomic::active, motor3Time);
				}

			}
			else if (state == Move_Bck)
				{
				   if (ackNum == 0)
						{
							state  = Pr_Stp;
							holdIn(Atomic::active, motor3Time);
						}
				   else if(ackNum == 1)
					{
						state  = Pr_Move_Fwd;
						holdIn(Atomic::active, motor3Time);
					}

				}
			else if(state == Move_Fwd)
			{
				if (ackNum==0)
				{
					state=Pr_Stp;
					holdIn(Atomic::active, motor3Time);
				}
			}
		}
		return *this;
}

/*******************************************************************
* Function Name: Motor3::internalFunction()
* Description: Internal Function Motor3
********************************************************************/
Model &Motor3::internalFunction( const InternalMessage & )
{


	if (state==Pr_Move_Fwd){
		state=Move_Fwd;
		passivate();
	}
	else if(state==Pr_Move_Bck){
		state=Move_Bck;
		passivate();
	}
	else if(state==Pr_Stp){
		state=Stp;
		passivate();
	}
		return *this;
}

/*******************************************************************
* Function Name: Motor3::outputFunction()
* Description: Output function Motor3 - writes info about time and events
********************************************************************/
Model &Motor3::outputFunction( const InternalMessage &msg )
{
	if (state == Pr_Move_Fwd){
		sendOutput( msg.time(), motor3_out1, 1) ;//moving forward
	}
	else if (state == Pr_Move_Bck){
		sendOutput( msg.time(), motor3_out1, 2) ;//moving backward

	}
	else if (state == Pr_Stp){
		sendOutput( msg.time(), motor3_out1, 0) ;//moving backward

	}
	return *this ;
}

Motor3::~Motor3()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
