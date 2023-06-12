/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sonar1
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
#include "Sonar1.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Sonar1
* Description: constructor
********************************************************************/
Sonar1::Sonar1( const std::string &name ) : Atomic( name )
, sonar1_in1( addInputPort( "sonar1_in1" ) )
, sonar1_out1( addOutputPort( "sonar1_out1" ) )
, sonar1Time (00,00,00,10)
{
	std::string timepreparation( MainSimulator::Instance().getParameter( description(), "sonar1processingTime" ) ) ;
//test
	if (timepreparation !="") sonar1Time = timepreparation;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"sonar1Time="<<sonar1Time<<"\n";
}

/*******************************************************************
* Function Name: Sonar1::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Sonar1::initFunction()
{

	state = Dtcting;		// detecting
	return *this ;
}
/*******************************************************************
* Function Name: Sonar1::externalFunction()
* Description: External Function Sonar1
********************************************************************/
Model &Sonar1::externalFunction( const ExternalMessage &msg )
{

	if (state == Dtcting && msg.port() == sonar1_in1 && msg.value()==1.0)
		{
					state  = Msg_Radar;
					holdIn(Atomic::active, sonar1Time);
		}
		return *this;
}

/*******************************************************************
* Function Name: Sonar1::internalFunction()
* Description: Internal Function Sonar1
********************************************************************/
Model &Sonar1::internalFunction( const InternalMessage & )
{
	if(state==1){
		state=Dtcting;
		passivate();
	}

		return *this;
}

/*******************************************************************
* Function Name: Sonar1::outputFunction()
* Description: Output function Sonar1 - writes info about time and events
********************************************************************/
Model &Sonar1::outputFunction( const InternalMessage &msg )
{
	if (state == Msg_Radar){
		sendOutput( msg.time(), sonar1_out1, 1) ;//something founded
	}
	return *this ;
}

Sonar1::~Sonar1()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
