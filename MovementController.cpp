/*******************************************************************
*
*  DESCRIPTION: Atomic Model MovementController
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 07/08/2009
*******************************************************************/

/** include files **/
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "MovementController.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: MovementController
* Description: constructor
********************************************************************/
MovementController::MovementController( const std::string &name ) : Atomic( name )
, move_in1( addInputPort( "move_in1" ) )
, move_in2( addInputPort( "move_in2" ) )
, move_in3( addInputPort( "move_in3" ) )
, move_in4( addInputPort( "move_in4" ) )
, move_out1( addOutputPort( "move_out1" ) )
, move_out2( addOutputPort( "move_out2" ) )
, move_out3( addOutputPort( "move_out3" ) )
, move_out4( addOutputPort( "move_out4" ) )
, move_out5( addOutputPort( "move_out5" ) )
, moveTime (00,00,10,00)
{
	std::string movepreparation( MainSimulator::Instance().getParameter( description(), "mcprocessingTime" ) ) ;

	//test
	if (movepreparation !="") moveTime = movepreparation;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"moveTime="<<moveTime<<"\n";

}

/*******************************************************************
* Function Name: MovementController::initFunction()
* Description: Initialization Function
********************************************************************/
Model &MovementController::initFunction()
{

	state = Stp;		// waiting event
	return *this ;
}
/*******************************************************************
* Function Name: MovementController::externalFunction()
* Description: External Function MovementController
********************************************************************/
Model &MovementController::externalFunction( const ExternalMessage &msg )
{

	if (msg.port() == move_in1){
		if(state == Stp && msg.value()==1){
			state = Pr_Move_Fwd;
			holdIn( Atomic::active, moveTime );
			}
		}
	else if(msg.port() == move_in2){
		if (state == Moving_Fwd && msg.value() ==1){
				state = MC_Stp;
				holdIn( Atomic::active, moveTime );
			}
		else if (state == Wait_Rdar){
			     degree1 = msg.value();
//				cout<<"Movement got degree from radar: "<<degree1<<"\n";
				state = Pr_Recv;
				holdIn( Atomic::active, moveTime );
			}
	}
	else if(msg.port() == move_in3){
		if (state == Rcv_Deg){
			degree2= msg.value();
			state = Pr_Trn;
			holdIn( Atomic::active, moveTime );
//			cout<<"Movement got degree from compass2: "<<degree2<<"\n";
			}
	}

	else if (msg.port() == move_in4){
		if(state == Move_Fwd && msg.value()==1){
			state = Pr_Stp;
			holdIn( Atomic::active, moveTime );
			} //
		else if (state == Turn && msg.value()==2){
				state = Ask_Move_Fwd;
				holdIn( Atomic::active, moveTime );
			}
		}
		return *this;
}

/*******************************************************************
* Function Name: MovementController::internalFunction()
* Description: Internal Function MovementController
********************************************************************/
Model &MovementController::internalFunction( const InternalMessage & )
{

	switch (state){
			case Pr_Move_Fwd:
				state = Moving_Fwd;
				passivate();
				break;

			case MC_Stp:
				state = Wait_Rdar;
				passivate();
				break;

			case Pr_Recv:
				state = Rcv_Deg;
			    passivate();
				break;

			case Pr_Trn:
				state = Turn;
			    passivate();
				break;

			case Ask_Move_Fwd:
				state = Move_Fwd;
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
* Function Name: MovementController::outputFunction()
* Description: Output function MovementController - writes info about time and events
********************************************************************/
Model &MovementController::outputFunction( const InternalMessage &msg )
{

			if (state==Pr_Move_Fwd)
			{
				sendOutput( msg.time(), move_out1, 1) ;
				sendOutput( msg.time(), move_out2, 1) ;
				sendOutput( msg.time(), move_out3, 1) ;
			}


			else if(state== MC_Stp)
			{
				sendOutput( msg.time(), move_out2, 0) ;
				sendOutput( msg.time(), move_out3, 0) ;
			}

			else if (state==Pr_Recv)
			{
				sendOutput( msg.time(), move_out4, 1000) ;
			}

			else if (state== Pr_Trn)
			{
				sendOutput( msg.time(), move_out5,2);
				if(abs(degree2-degree1) >= 90)
				{
					if(degree2-degree1>0)
					{
						sendOutput( msg.time(), move_out2,1);
						sendOutput( msg.time(), move_out3,2);
					}
					else if(degree2-degree1<0)
					{
						sendOutput( msg.time(), move_out2,2);
						sendOutput( msg.time(), move_out3,1);
					}
			   }
				else if(abs(degree2-degree1)< 90)
				{
					if(degree2-degree1>0)
					{
						sendOutput( msg.time(), move_out2,2);
						sendOutput( msg.time(), move_out3,1);
					}
				else if(degree2-degree1<0)
					{
						sendOutput( msg.time(), move_out2,1);
						sendOutput( msg.time(), move_out3,2);
					}
				}
			}

			else if (state==Ask_Move_Fwd)
			{
				sendOutput( msg.time(), move_out2, 1) ;// motor2 move forward
				sendOutput( msg.time(), move_out3, 1) ;// motor3  move forward
				sendOutput( msg.time(), move_out5, 1) ;// sensor2  detecting
			}
			else if (state== Pr_Stp)
			{
				sendOutput( msg.time(), move_out2, 0) ;
				sendOutput( msg.time(), move_out3, 0) ;
			}
	return *this ;
}

MovementController::~MovementController()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
