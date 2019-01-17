/***************************************************************************

    file                 : robot_base.cpp
    created              : Mon 13 Feb 11:40:23 GMT 2017
    copyright            : (C) 2002 Author

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

#include "States.h"
#include "Operations.h"


static tTrack	*curTrack;

static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s); 
static void newrace(int index, tCarElt* car, tSituation *s); 
static void drive(int index, tCarElt* car, tSituation *s); 
static void endrace(int index, tCarElt *car, tSituation *s);
static void shutdown(int index);
static int  InitFuncPt(int index, void *pt); 


/* 
 * Module entry point  
 */ 
extern "C" int 
VasilePetrut(tModInfo *modInfo)
{
    memset(modInfo, 0, 10*sizeof(tModInfo));

    modInfo->name    = strdup("VasilePetrut");		/* name of the module (short) */
    modInfo->desc    = strdup("");	/* description of the module (can be long) */
    modInfo->fctInit = InitFuncPt;		/* init function */
    modInfo->gfId    = ROB_IDENT;		/* supported framework version */
    modInfo->index   = 1;

    return 0; 
} 

/* Module interface initialization. */
static int 
InitFuncPt(int index, void *pt) 
{ 
    tRobotItf *itf  = (tRobotItf *)pt; 

    itf->rbNewTrack = initTrack; /* Give the robot the track view called */ 
				 /* for every track change or new race */ 
    itf->rbNewRace  = newrace; 	 /* Start a new race */
    itf->rbDrive    = drive;	 /* Drive during race */
    itf->rbPitCmd   = NULL;
    itf->rbEndRace  = endrace;	 /* End of the current race */
    itf->rbShutdown = shutdown;	 /* Called before the module is unloaded */
    itf->index      = index; 	 /* Index used if multiple interfaces */
    return 0; 
} 

/* Called for every track change or new race. */
static void  
initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s) 
{ 
    curTrack = track;
    *carParmHandle = NULL; 
} 

/* Start a new race. */
static void  
newrace(int index, tCarElt* car, tSituation *s) 
{ 
} 
States* StatesController = new States();
Operations* operations = new Operations();

/* Drive during race. */
static void  
drive(int index, tCarElt* car, tSituation *s) 
{ 
	memset((void *)&car->ctrl, 0, sizeof(tCarCtrl));
	// See States.cpp
	car->ctrl.gear = 1;

	if (operations->getSpeedLimit(car->_trkPos.seg) > car->_speed_x && StatesController->currentState != States::State::Accelerate)
	{
		StatesController->currentState = States::State::Accelerate;
		//Stop braking
		car->ctrl.brakeCmd = 0;
	}
	else if (operations->Brake(car))
	{
		StatesController->currentState = States::State::Brake;
		//Stop accelerating
		car->ctrl.accelCmd = 0;
	}
	else if (operations->isOffTrack(car))
	{
		StatesController->currentState = States::State::Stuck;
	}
	else
	{
		StatesController->currentState = States::State::Steering;
	}


	if (StatesController->currentState == States::State::Accelerate)
	{
		StatesController->AcceleratingState(car, operations->getSpeedLimit(car->_trkPos.seg));
	}
	else if (StatesController->currentState == States::State::Brake)
	{
		StatesController->BrakingState(car);
	}
	else if (StatesController->currentState == States::State::Stuck)
	{
		StatesController->StuckState(car);
	}
	else
	{
		StatesController->SteeringState(car);
	}
}

/* End of the current race */
static void
endrace(int index, tCarElt *car, tSituation *s)
{
}

/* Called before the module is unloaded */
static void
shutdown(int index)
{
}

