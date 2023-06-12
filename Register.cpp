/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Dieynaba Alpha Tall
*
*  EMAIL: alphadieynaba@yahoo.fr
*
*
*  DATE: 02/08/2009
*
*******************************************************************/

#include <modeladm.h>
#include <mainsimu.h>

/* New libraries are copied after this line */
#include "Sonar1.h"
#include "Sonar2.h"
#include "Compass1.h"
#include "Compass2.h"
#include "RadarController.h"
#include "MovementController.h"
#include "Motor1.h"
#include "Motor2.h"
#include "Motor3.h"


void MainSimulator::registerNewAtomics()
{

//New models are regsitered after this line
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Sonar1>() , "Sonar1" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Sonar2>() , "Sonar2" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Compass1>() , "Compass1" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Compass2>() , "Compass2" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<RadarController>() , "RadarController" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<MovementController>() , "MovementController" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Motor1>() , "Motor1" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Motor2>() , "Motor2" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Motor3>() , "Motor3" ) ;

}
