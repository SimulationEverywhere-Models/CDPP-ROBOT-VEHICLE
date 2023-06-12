/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sonar2
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*  DATE: 07/08/2009
*******************************************************************/

/** include files **/
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "Sonar2.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Sonar2
* Description: constructor
********************************************************************/
Sonar2::Sonar2( const std::string &name ) : Atomic( name )
, sonar2_in1( addInputPort( "sonar2_in1" ) )
, sonar2_in2( addInputPort( "sonar2_in2" ) )
, sonar2_out1( addOutputPort( "sonar2_out1" ) )
, sonar2Time (00,00,00,01)
, sonar2Time1 (00,00,00,50)
{
	std::string timepreparation( MainSimulator::Instance().getParameter( description(), "sonar2processingTime" ) ) ;
	std::string timepreparation1( MainSimulator::Instance().getParameter( description(), "sonar2objectTime" ) ) ;
//test
	if (timepreparation !="") sonar2Time = timepreparation;
	if (timepreparation1 !="") sonar2Time1 = timepreparation1;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"sonar2Time="<<sonar2Time<<"\n";
	cout<<"sonar2Time1="<<sonar2Time1<<"\n";
}

/*******************************************************************
* Function Name: Sonar2::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Sonar2::initFunction()
{

	state = Idle;		// waiting
	return *this ;
}
/*******************************************************************
* Function Name: Sonar2::externalFunction()
* Description: External Function Sonar2
********************************************************************/
Model &Sonar2::externalFunction( const ExternalMessage &msg )
{
	if ( state == Idle && msg.port() == sonar2_in1)
		{
				ackNum = static_cast <int> (msg.value());
				if (ackNum == 1)
				{
					state  = Dtcting;
					passivate();
				}
				else if (ackNum == 2)
				{
					state  = Mtching;
					passivate();
				}
			}
	else if (state == Dtcting && msg.port() == sonar2_in2)
			{
				distance = msg.value();
				if (distance <= 10)
				{
					state = Msg_MC;
					holdIn(Atomic::active, sonar2Time);
				}
				else if (distance > 10)
				{
					passivate ();	
				}
			}
   else if(state == Mtching && msg.port() == sonar2_in2)
			{
				distance = msg.value();
				if (distance <= 50)
				{
					state = Send_Out;
					holdIn(Atomic::active, sonar2Time1);
				}
				else if (distance > 50)
				{
					passivate ();	
				}
			}
	return *this;
}

/*******************************************************************
* Function Name: Sonar2::internalFunction()
* Description: Internal Function Sonar2
********************************************************************/
Model &Sonar2::internalFunction( const InternalMessage & )
{

	if (state == Msg_MC)
	{
		state=Idle;
		passivate();
	}
	else if (state == Send_Out)
	{
		state=Idle;
		passivate();
	}
		return *this;
}

/*******************************************************************
* Function Name: Sonar2::outputFunction()
* Description: Output function Sonar2 - writes info about time and events
********************************************************************/
Model &Sonar2::outputFunction( const InternalMessage &msg )
{
	if (state == Msg_MC){
		sendOutput( msg.time(), sonar2_out1, 1) ;//something founded
	}
 	else if (state == Send_Out){
		sendOutput( msg.time(), sonar2_out1, 2) ;
	}
	return *this ;
}

Sonar2::~Sonar2()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
