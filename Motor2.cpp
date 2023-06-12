/*******************************************************************
*
*  DESCRIPTION: Atomic Model Motor2
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
#include "Motor2.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Motor2
* Description: constructor
********************************************************************/
Motor2::Motor2( const std::string &name ) : Atomic( name )
, motor2_in1( addInputPort( "motor2_in1" ) )
, motor2_out1( addOutputPort( "motor2_out1" ) )
, motor2Time (00,00,10,00)
{
	std::string timepreparation( MainSimulator::Instance().getParameter( description(), "motor2processingTime" ) ) ;
//test
	if (timepreparation !="") motor2Time = timepreparation;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"motor2Time="<<motor2Time<<"\n";
}

/*******************************************************************
* Function Name: motor2::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Motor2::initFunction()
{

	state = Stp;		// stop
	return *this ;
}
/*******************************************************************
* Function Name: motor2::externalFunction()
* Description: External Function Motor2
********************************************************************/
Model &Motor2::externalFunction( const ExternalMessage &msg )
{

	if (msg.port() == motor2_in1)
		{
		ackNum = static_cast <int> (msg.value());
			if (state == Stp)
			{
				if (ackNum == 1)
				{
					state  = Pr_Move_Fwd;
					holdIn(Atomic::active, motor2Time);
				}
				else if (ackNum==2)
				{
					state = Pr_Move_Bck;
					holdIn(Atomic::active, motor2Time);
				}

			}
			else if (state == Move_Bck)
				{
				   if (ackNum == 0)
						{
							state  = Pr_Stp;
							holdIn(Atomic::active, motor2Time);
						}
				   else if(ackNum == 1)
					{
						state  = Pr_Move_Fwd;
						holdIn(Atomic::active, motor2Time);
					}

				}
			else if(state == Move_Fwd)
			{
				if (ackNum==0)
				{
					state=Pr_Stp;
					holdIn(Atomic::active, motor2Time);
				}
			}
		}
		return *this;
}

/*******************************************************************
* Function Name: Motor2::internalFunction()
* Description: Internal Function Motor2
********************************************************************/
Model &Motor2::internalFunction( const InternalMessage & )
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
* Function Name: Motor2::outputFunction()
* Description: Output function Motor2 - writes info about time and events
********************************************************************/
Model &Motor2::outputFunction( const InternalMessage &msg )
{
	if (state == Pr_Move_Fwd){
		sendOutput( msg.time(), motor2_out1, 1) ;//moving forward
	}
	else if (state == Pr_Move_Bck){
		sendOutput( msg.time(), motor2_out1, 2) ;//moving backward

	}
	else if (state == Pr_Stp){
		sendOutput( msg.time(), motor2_out1, 0) ;//moving backward

	}
	return *this ;
}

Motor2::~Motor2()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
