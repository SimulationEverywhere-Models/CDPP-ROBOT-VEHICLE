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

/** include files **/
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "RadarController.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: RadarController
* Description: constructor
********************************************************************/
RadarController::RadarController( const std::string &name ) : Atomic( name )
, radar_in1( addInputPort( "radar_in1" ) )
, radar_in2( addInputPort( "radar_in2" ) )
, radar_in3( addInputPort( "radar_in3" ) )
, radar_out1( addOutputPort( "radar_out1" ) )
, radar_out2( addOutputPort( "radar_out2" ) )
, radar_out3( addOutputPort( "radar_out3" ) )
, radarTime (00,00,10,00)
, turnTime (00,00,03,00)

{
	std::string timemessage( MainSimulator::Instance().getParameter( description(), "radarprocessingTime" ) ) ;
	std::string timeturn( MainSimulator::Instance().getParameter( description(), "turnprocessingTime" ) ) ;

//test
	if (timemessage !="") radarTime = timemessage;
	if (timeturn !="") turnTime = timeturn;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"radarTime="<<radarTime<<"\n";
	cout<<"turnTime="<<turnTime<<"\n";

}

/*******************************************************************
* Function Name: RadarController::initFunction()
* Description: Initialization Function
********************************************************************/
Model &RadarController::initFunction()
{

	state = Idle;		// detecting
	return *this ;
}
/*******************************************************************
* Function Name: RadarController::externalFunction()
* Description: External Function RadarController
********************************************************************/
Model &RadarController::externalFunction( const ExternalMessage &msg )
{

	if (state == Idle && msg.port().asString() == "radar_in1"){//radar
		if(msg.value()==1){
			state = Pr_Wrk;
			holdIn( Atomic::active, radarTime );
			} //
		}
	else if ((state == Trn_Right || state == Trn_Left) && msg.port() == radar_in2){
			if(msg.value() ==1){
				state = Ask_Stp;
				holdIn( Atomic::active, radarTime ); //motor1 and MC stop
			}
		}
	else if (state == Wait && msg.port().asString() == "radar_in3"){
				degree1 = msg.value();
				state = Send_MC;
				holdIn( Atomic::active, radarTime );

		}
		return *this;
}

/*******************************************************************
* Function Name: RadarController::internalFunction()
* Description: Internal Function RadarController
********************************************************************/
Model &RadarController::internalFunction( const InternalMessage & )
{

	switch (state){
			case Pr_Wrk:
				state = Trn_Right;
				 holdIn( Atomic::active, turnTime );
				break;

			case Trn_Right:
				state = Trn_Left;
			    holdIn( Atomic::active, turnTime ); //now wait to complete backward move
				break;

			case Trn_Left:
				state = Trn_Right;
			    holdIn( Atomic::active, turnTime ); //now wait to complete backward move
				break;

			case Ask_Stp:
				state = Wait;
				passivate();
				break;

			case Send_MC:
				state = Idle;
				passivate();
				break;
		}
		return *this;
}

/*******************************************************************
* Function Name: RadarController::outputFunction()
* Description: Output function RadarController - writes info about time and events
********************************************************************/
Model &RadarController::outputFunction( const InternalMessage &msg )
{
	switch (state){
			case Pr_Wrk:
		    	//std::cout << "Working" << std::endl;
				sendOutput( msg.time(), radar_out1, 1) ;//working

				break;

			case Trn_Right:
				sendOutput( msg.time(), radar_out1, 2) ;//Turn right
				break;

			case Trn_Left:
			    sendOutput( msg.time(), radar_out1, 1) ;//Turn Left
				break;

			case Ask_Stp:
				sendOutput( msg.time(), radar_out1, 0) ;// Motor1 Stop
				sendOutput( msg.time(), radar_out2, 1) ;// send 0 to MC for Stop
				sendOutput( msg.time(), radar_out3, 1) ;//working
				break;
			case Send_MC:
			   // std::cout << "ask MC Turn" << std::endl;
				sendOutput( msg.time(), radar_out2, degree1) ;//Waiting
				break;
		};
	return *this ;
}

RadarController::~RadarController()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
