/*******************************************************************
*
*  DESCRIPTION: Atomic Model Compass2
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
#include "Compass2.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Compass2
* Description: constructor
********************************************************************/
Compass2::Compass2( const std::string &name ) : Atomic( name )
, compass2_in1( addInputPort( "compass2_in1" ) )
, compass2_in2( addInputPort( "compass2_in2" ) )
, compass2_out1( addOutputPort( "compass2_out1" ) )
, compass2Time (00,00,00,10)
{
	std::string timepreparation( MainSimulator::Instance().getParameter( description(), "compass2processingTime" ) ) ;
//test
	if (timepreparation !="") compass2Time = timepreparation;

	cout<<"compass2Time="<<compass2Time<<"\n";
}

/*******************************************************************
* Function Name: Compass2::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Compass2::initFunction()
{

	state = Stp;		// stay here until you input from MC
	return *this ;
}


/*******************************************************************
* Function Name: Compass2::externalFunction()
* Description: External Function Compass2
********************************************************************/
Model &Compass2::externalFunction( const ExternalMessage &msg )
{

	if (msg.port() == compass2_in2)
		{
		if (state == Stp && msg.value()== 1000)
			{
					state  = Dtcting;
					passivate();
//				cout<<"compass2 got 1000 from movement \n";
		    }
		else if (state == Stp && msg.value() >= 0 && msg.value() <= 180)
		{
				degree1 = msg.value();
				state  = Matching;
				passivate();
//				cout<<"Compass2 got degree1 from movement: "<<degree1<<"\n";
		}
		}
	else if (msg.port() == compass2_in1)
		{
		if (state == Dtcting)
			{
			        degree=msg.value();
					state  = Send_Out;
					holdIn(Atomic::active, compass2Time);
			}
	   else if (state == Matching)
	   {
			   degree2=msg.value();
				cout<<"Compass2 maching degree: "<<degree2<<"\n";
		   if( degree2 >= (degree1 - 1) && degree2 <= (degree1 +1))
				{
					state  = Send_MC;
					holdIn(Atomic::active, compass2Time);
				}
		   else 
				{
					passivate();
				}
			}
		}
	return *this;
}

/*******************************************************************
* Function Name: Compass2::internalFunction()
* Description: Internal Function compass2
********************************************************************/
Model &Compass2::internalFunction( const InternalMessage & )
{
	if(state==Send_MC){
		state=Stp;
		passivate();
	}
	else if(state==Send_Out){
			state=Stp;
			passivate();
		}

		return *this;
}

/*******************************************************************
* Function Name: Compass2::outputFunction()
* Description: Output function Compass2 - writes info about time and events
********************************************************************/
Model &Compass2::outputFunction( const InternalMessage &msg )
{
	if (state == Send_Out){
			sendOutput( msg.time(), compass2_out1, degree) ;//send forward degree
	}
	if (state == Send_MC){
			sendOutput( msg.time(), compass2_out1, 1) ;//send degrees matching
		}
	return *this ;
}

Compass2::~Compass2()
{
}
