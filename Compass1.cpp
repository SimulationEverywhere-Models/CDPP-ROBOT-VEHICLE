/*******************************************************************
*
*  DESCRIPTION: Atomic Model Compass1
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*  DATE: 11/08/2009
*******************************************************************/

/** include files **/
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "Compass1.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Compass1
* Description: constructor
********************************************************************/
Compass1::Compass1( const std::string &name ) : Atomic( name )
, compass1_in1( addInputPort( "compass1_in1" ) )
, compass1_in2( addInputPort( "compass1_in2" ) )
, compass1_out1( addOutputPort( "compass1_out1" ) )
, compass1Time (00,00,00,10)

{
	std::string timepreparation( MainSimulator::Instance().getParameter( description(), "compass1processingTime" ) ) ;
//test
	if (timepreparation !="") compass1Time = timepreparation;

	cout<<"compass1Time="<<compass1Time<<"\n";
}

/*******************************************************************
* Function Name: Compass1::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Compass1::initFunction()
{

	state = Idle;		// idle
	return *this ;
}
/*******************************************************************
* Function Name: Compass1::externalFunction()
* Description: External Function Compass1
********************************************************************/
Model &Compass1::externalFunction( const ExternalMessage &msg )
{

	if (msg.port() == compass1_in1)
		{
			if (state == Idle && msg.value()== 1)
			{
					state  = Trning;
					passivate();
		    }
		}
	else if (msg.port() == compass1_in2)
	{
			 if (state == Trning)
			{
				degree1 = msg.value();
					state  = Send_Out;
					holdIn(Atomic::active, compass1Time);
			}
		}
	return *this;
}

/*******************************************************************
* Function Name: Compass1::internalFunction()
* Description: Internal Function compass1
********************************************************************/
Model &Compass1::internalFunction( const InternalMessage & )
{
	if(state==Send_Out){
		state=Idle;
		passivate();
	}

		return *this;
}

/*******************************************************************
* Function Name: Compass1::outputFunction()
* Description: Output function Compass1 - writes info about time and events
********************************************************************/
Model &Compass1::outputFunction( const InternalMessage &msg )
{
	if (state == Send_Out){
		std::cout << "Radar degree: "<<degree1<<"\n";
		sendOutput( msg.time(), compass1_out1, degree1) ;//send the degree
	}
	return *this ;
}

Compass1::~Compass1()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
