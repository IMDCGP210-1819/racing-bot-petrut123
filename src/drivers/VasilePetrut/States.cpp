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




States::States()
{
}

States::~States()
{
}
//The driver tries to steer towards the middle of the track 
//Not very efficient when it comes to lap times but it's a safe option
void States::SteeringState(tCarElt* car)
{
	float angle;
	angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
	NORM_PI_PI(angle); 

	angle -= car->_trkPos.toMiddle / car->_trkPos.seg->width;

	car->ctrl.steer = angle / car->_steerLock;
}

void States::StuckState()
{
}

void States::BreakingState()
{
}
//When the driver enters this state it sets the amount of acceleration needed for the speed limit on the current segment and then gears up / down
void States::AcceleratingState(tCarElt* car, float maxSpeed)
{
	car->ctrl.accelCmd = maxSpeed / car->_wheelRadius(REAR_RGT) * car->_gearRatio[car->_gear + car->_gearOffset] / car->_enginerpmRedLine;

	if (car->_gear <= 0)
	{
		car->ctrl.gear = 1;
	}
	else if (car->_enginerpmRedLine / car->_gearRatio[car->_gear + car->_gearOffset] * car->_wheelRadius(REAR_RGT) < car->_speed_x) 
	{
		car->ctrl.gear = car->_gear + 1;
	}
	else if (car->_gear > 1 && car->_enginerpmRedLine / car->_gearRatio[car->_gear + car->_gearOffset - 1] * car->_wheelRadius(REAR_RGT) > car->_speed_x)
	{
		car->ctrl.gear = car->_gear - 1;
	}
}
